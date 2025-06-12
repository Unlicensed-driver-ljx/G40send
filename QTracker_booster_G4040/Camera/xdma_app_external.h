//#ifndef XDMA_APP_EXTERNAL_H
//#define XDMA_APP_EXTERNAL_H
#include <QQueue>

#ifndef __XDMA_APP_EXTERNAL__
#define __XDMA_APP_EXTERNAL__

// 0x0: base
// 0x2: full
#define CAMERALINK_IMAGE_MODE 0x0

// taps(1,2,3,4,8)
// bits(8,10.12,14,16)
// for test 8bit 3taps
#define CAMERALINK_IMAGE_TAPS 3
#define CAMERALINK_IMAGE_BITS 8

// input: rgb888
#define CAMERALINK_IMAGE_WIDTH      960
#define CAMERALINK_IMAGE_HEIGHT     1080

// output: yuyv422 8bit
#define SDI_IMAGE_WIDTH     960
#define SDI_IMAGE_HEIGHT    1080
/**
* cameralink recv: 4 frames of data are cached, and if there is not enough space,
* the read frames are discarded
*/

#define CAMERALINK_IMAGE_KFIFO_NUM   4

// image moudle
extern int xdma_app_init(void);
extern int image_init(uint32_t width, uint32_t height, uint32_t taps, uint32_t bits, uint32_t mode, uint32_t image_kfifo_num);
extern void xdma_event_init(void);
extern void xdma_app_receive_stop(void);
extern void xdma_app_send_stop(void);
extern void xdma_app_uart_recv_stop();
extern int sdi_write(uint8_t *buf, uint32_t count);
extern int cameralink_read(uint8_t *buf, uint32_t count);
extern void write_file(char const *filename, uint8_t *buf, uint32_t count);

// uart module
extern int uart_port_init(uint32_t uart_num, uint32_t baundrate);
extern int uart_read(uint32_t uart_num, char *buf, uint32_t count);
extern int uart_write(uint32_t uart_num, char *buf, uint32_t count);
extern uint32_t read_reg_new(uint32_t offset);
int getlen_fifo(uint32_t uart_num);

// sync module
extern void sync_module_disable(void);
extern void sync_module_enable(void);
extern void sync_duty_out_set(double time_in_seconds);
extern void sync_freq_out_set(int freq);
extern void sync_out_polarity_sel(int polarity);
extern void sync_input_polarity_sel(int polarity);

// central crosshair
extern void central_crosshair_set(int flag);
extern void central_crosshair_pos_set(int row, int col);
extern void central_crosshair_len_set(int len);

// target crosshair
extern void target_crosshair_set(int crosshair_num, int flag);
extern void target_crosshair_pos_set(int crosshair_num, int row, int col);
extern void target_crosshair_len_set(int crosshair_num, int len);

// character display
extern void character_data_set(int char_num, int flag, int char_size, uint8_t *buf);
extern void character_data_position_set(int col, int row, int flag);
extern void character_data_space_set(int char_space, int flag);
extern void character_data_size_set(int width, int height);
extern void character_data_set_complete();

extern QQueue<uchar*> rec_Queue;
extern QList<uchar*> rev_List;

#endif

