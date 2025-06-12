
#include <assert.h>
#include <time.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <errno.h>
#include <signal.h>
#include <QDebug>
#include "kfifo.h"
#include "xdma_app_external.h"
#include <QDateTime>
#include <QQueue>
#include <QList>

QQueue<uchar*> rec_Queue;
QList<uchar*> rev_List;

#define FPGA_VERSION "0.1"

#define SDI_SEND_TEST

#define UART_SEND_TEST
#define UART_RECV_TEST

#ifdef UART_RECV_TEST
#define UART_RECV_LEN 64
#endif

#ifdef UART_SEND_TEST
#define UART_SEND_LEN 64
#endif

#define SYNC_MODULE_TEST

#define FRAME_BAUD      115200

#define UART_SEND_FILE  "uart_send.bin"

#define SHOW_INFO
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

#define PCIE_BAR0_SIZE (0x100000)

#define IMAGE_OFFSET 0x0
#define CHAR_OFFSET 0x10000
#define IRQ_OFFSET  0x50000
#define SYNC_OFFSET 0x20000
#define UART_OFFSET 0x40000
#define GPIO_OFFSET 0x60000

// character moudles
// central Crosshair display select register
#define CENTRAL_CROSS_SELECT_REG      (CHAR_OFFSET + 0x0)

// Cross center position register
// [15:0]: column coordinate
// [31:16]: row coordinate
#define CENTRAL_CROSS_POSITION_REG     (CHAR_OFFSET + 0x4)

// Cross length register
#define CENTRAL_CROSS_LENGTH_REG              (CHAR_OFFSET + 0x8)

// Target cross display select register
#define TARGET_CROSS_DISPLAY_SELECT_REG     (CHAR_OFFSET + 0xc)

// Target cross position registers (10 targets)
#define TARGET_CROSS_POSITION_OFFSET(n)  (0x0010 + ((n) * 0x04))
#define TARGET_CROSS_POSITION_REG(n)     (CHAR_OFFSET + TARGET_CROSS_POSITION_OFFSET(n))

// Target cross length registers (10 targets)
#define TARGET_CROSS_LENGTH_OFFSET(n)    (0x0038 + ((n) * 0x04))
#define TARGET_CROSS_LENGTH_REG(n)       (CHAR_OFFSET + TARGET_CROSS_LENGTH_OFFSET(n))

// Character data registers (upper part)
#define UPPER_CHAR_DATA_OFFSET(n)        (0x0060 + ((n) * 0x04))
#define UPPER_CHAR_DATA_REG(n)           (CHAR_OFFSET + UPPER_CHAR_DATA_OFFSET(n))

// Character data registers (lower part)
#define LOWER_CHAR_DATA_OFFSET(n)        (0x0100 + ((n) * 0x04))
#define LOWER_CHAR_DATA_REG(n)           (CHAR_OFFSET + LOWER_CHAR_DATA_OFFSET(n))

// Character start coordinate registers
#define UPPER_CHAR_START_COORD_REG       (CHAR_OFFSET + 0x1a0)
#define LOWER_CHAR_START_COORD_REG       (CHAR_OFFSET + 0x1a4)

// Character data complete register
#define CHAR_DATA_COMPLETE_REG           (CHAR_OFFSET + 0x200)

// Font size register
#define CHAR_SIZE_REG                    (CHAR_OFFSET + 204)
#define CHAR_HEIGHT_MAX                  64
#define CHAR_WIDTH_MAX                   64

// Character spacing register
#define CHAR_SPACING_REG                 (CHAR_OFFSET + 0x208)

/* IRQ module */
#define IRQ_ENABLE              (IRQ_OFFSET + 0x0)
#define IRQ_UP_CLEAR            (IRQ_OFFSET + 0x4)
#define IRQ_DOWN_CLEAR          (IRQ_OFFSET + 0x8)
#define IRQ_UP_STATUS           (IRQ_OFFSET + 0x4)
#define IRQ_DOWN_STATUS         (IRQ_OFFSET + 0x8)
#define IRQ_UP_FLAG             (IRQ_OFFSET + 0xc)
#define IRQ_DOWN_FLAG           (IRQ_OFFSET + 0x10)

/* Use 1 bits per SDI*/
//#define IRQ_SDI_MASK         0x1

///* uart module  */
//#define UART_BAUNDRATE(n)      (UART_OFFSET + ((n) * 0x4))
//#define UART_DATA(n)           (UART_OFFSET + 0x8 + ((n) * 0x4))
//#define UART_FIFO_COUNT(n)     (UART_OFFSET + 0x10 + ((n) * 0x4))
//#define UART_SEND_FIFO_STATUS         (UART_OFFSET + 0x18)

/* uart module 7 ge chuankou de pianyi */
#define UART_BAUNDRATE(n)             (UART_OFFSET + ((n) * 0x4))
#define UART_DATA(n)                  (UART_OFFSET + 0x1c + ((n) * 0x4))
#define UART_FIFO_COUNT(n)            (UART_OFFSET + 0x38 + ((n) * 0x4))
#define UART_SEND_FIFO_STATUS         (UART_OFFSET + 0x54)

#define UART_MAX_DATA_LEN   1024
#define UART_PORT_NUM       2

/* uart 2KB */
#define UART_KFIFO_SIZE 0x800

/* 125Mhz */
#define FPGA_CLOCK  125000000

/* image module */
#define CAMERALINK_PING_START_REG          (IMAGE_OFFSET + 0x0)
#define CAMERALINK_PING_END_REG            (IMAGE_OFFSET + 0x4)
#define CAMERALINK_PONG_START_REG          (IMAGE_OFFSET + 0x8)
#define CAMERALINK_PONG_END_REG            (IMAGE_OFFSET + 0xc)
#define SDI_PING_START_REG                 (IMAGE_OFFSET + 0x10)
#define SDI_PING_END_REG                   (IMAGE_OFFSET + 0x14)
#define SDI_PONG_START_REG                 (IMAGE_OFFSET + 0x18)
#define SDI_PONG_END_REG                   (IMAGE_OFFSET + 0x1c)
#define SDI_PING_WRITE_DONE_REG            (IMAGE_OFFSET + 0x20)
#define SDI_PONG_WRITE_DONE_REG            (IMAGE_OFFSET + 0x24)
#define CAMERALINK_IMAGE_SIZE_REG          (IMAGE_OFFSET + 0x28)
#define SDI_IMAGE_SIZE_REG                 (IMAGE_OFFSET + 0x2c)
#define CAMERALINK_MODE_REG                (IMAGE_OFFSET + 0x30)
/*
 * bit[15:0]: col
 * bit[31:16]: row
 * */
#define CAMERALINK_IMAGE_FORMAT_REG        (IMAGE_OFFSET + 0x34)
/*
 * bit[15:0]: taps
 * bit[31:16]:bits
 * */
#define CAMERALINK_PARAM_REG               (IMAGE_OFFSET + 0x38)


#define CAMERALINK_BASE_MODE    0x0
#define CAMERALINK_FULL_MODE    0x2

QDateTime lastirq_time = QDateTime::currentDateTime();
QDateTime time1 = QDateTime::currentDateTime();
QDateTime time2 = QDateTime::currentDateTime();
/*
 * software
 *
 * */
int sdi_send_flag = 0;
/**
* bit[0]: ping interrupt flag
* bit[1]: pong interrupt flag
*/
int sdi_send_done = 3;

/**
*  recv:
*     cameralink0:
*          ping:0x0-image_size
*          pong:0x800000-(0x800000+image_size)

*  send:
*     sdi0:
*          ping:0x08000000-(0x08000000+image_size)
*          pong:0x08800000-(0x01800000+image_size)
*/

#define CAMERALINK_PING_START_ADDR 0x0
#define CAMERALINK_PING_END_ADDR (CAMERALINK_PING_START_ADDR + CAMERALINK_IMAGE_SIZE)
#define CAMERALINK_PONG_START_ADDR 0x1000000
#define CAMERALINK_PONG_END_ADDR (CAMERALINK_PONG_START_ADDR + CAMERALINK_IMAGE_SIZE)
#define SDI_PING_START_ADDR 0x08000000
#define SDI_PING_END_ADDR (SDI_PING_START_ADDR + SDI_IMAGE_SIZE)
#define SDI_PONG_START_ADDR 0x09000000
#define SDI_PONG_END_ADDR (SDI_PONG_START_ADDR + SDI_IMAGE_SIZE)

/* sync module */
#define SYNC_IN             (SYNC_OFFSET + 0x0)
#define SYNC_OUT            (SYNC_OFFSET + 0x4)
#define SYNC_FREQ_OUT       (SYNC_OFFSET + 0x8)
#define SYNC_DUTY_OUT       (SYNC_OFFSET + 0xc)

/* GPIO module */
#define GPIO_REG        (GPIO_OFFSET + 0x0)
#define CAMERALINK_PORT_ENABLE  0x2
#define SDI_PORT_ENABLE         0x4
#define SYNC_PORT_ENABLE        0x8
#define UART_PORT_ENABLE        0x10


/*the virtual address of FPGA's regs in userspace*/
void *reg_base;
int reg_fd;
int h2c_fd;
int c2h_fd;

#ifdef SDI_IMAGE_SAVE_RGB
static  int sdi_saved_rgb_num[SDI_PORT_NUM] = {0};
#endif
#ifdef SDI_IMAGE_SAVE_YUV
static  int sdi_saved_yuv_num[SDI_PORT_NUM] = {0};
#endif
#ifdef SDI_IMAGE_SAVE_BMP
static  int sdi_saved_bmp_num[SDI_PORT_NUM] = {0};
#endif

/*Ensure that the thread does not exit*/
int event_up_work = 1;
int event_down_work = 1;
static int uart_recv_work = 1;
static int cameralink_recv_work = 1;
#ifdef SHOW_INFO
static int show_info_work = 1;
int frame_in_kfifo = {0};
int frame_out_kfifo = {0};
int cameralink_read_count = {0};
int sdi_write_count = {0};
int sdi_write_lost_count = {0};
int cameralink_recv_int_count = {0};
int sdi_send_int_count = {0};
#endif

struct kfifo uart_recv_fifo[UART_PORT_NUM];
struct kfifo cameralink_recv_fifo;

/*virtual address in userspace of fpga regs*/
//void *reg_base;

pthread_t event_up_thread;
pthread_t event_down_thread;
pthread_t uart_recv_thread;
pthread_t cameralink_recv_thread;
#ifdef SHOW_INFO
pthread_t show_info_thread;
#endif

#define DEVICE_H2C "/dev/xdma0_h2c_0"
#define DEVICE_C2H "/dev/xdma0_c2h_0"
#define DEVICE_REG "/dev/xdma0_user"
#define DEVICE_EVENT_UP "/dev/xdma0_events_0"
#define DEVICE_EVENT_DOWN "/dev/xdma0_events_1"

static sem_t cameralink_rx_sem;
static sem_t sdi_tx_sem;
/**
* Represents the number of frames in KFIFO.
* sdi_read() decreases the count, sdi_recv() increases the count
*/
static sem_t cameralink_kfifo_sem;
static sem_t uart_kfifo_sem[UART_PORT_NUM];

/*for sdi send*/
static pthread_mutex_t sdi_send_mutex;
/*only one h2c channel*/
static pthread_mutex_t sdi_write_mutex;


