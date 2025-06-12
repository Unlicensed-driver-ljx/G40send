
#include "xdma_app.h"

static uint32_t cam_image_size, sdi_image_size;
static uint32_t bytes_per_pixel;
static uint32_t taps_per_pixel;
static uint32_t kfifo_size;
static uint32_t cam_ping_start_addr, cam_ping_end_addr;
static uint32_t cam_pong_start_addr, cam_pong_end_addr;
static uint32_t sdi_ping_start_addr, sdi_ping_end_addr;
static uint32_t sdi_pong_start_addr, sdi_pong_end_addr;
static char *cam_rx_buf = NULL;

int open_event(char const *devicename)
{
    int fd;

    fd = open(devicename, O_RDWR|O_SYNC );
    if (fd < 0)
    {
        printf("open event error\n");
        return -1;
    }

    return fd;
}

int read_event(int fd)
{
    int val;
    ssize_t result;

    if ((result = read(fd, &val, 4)) == -1) {
        printf("read_event error \n");
        return -1;
    }

    return val;
}

static int open_control(char const *filename)
{
    int fd;

    fd = open(filename, O_RDWR | O_SYNC);
    if(fd < 0)
    {
        printf("open control error, file name: %s, fd = %d\n", filename, fd);
        return -1;
    }

    return fd;
}


/* map fpga regs to userspace */
static void *mmap_control(int fd,long mapsize)
{
    void *vir_addr;

    vir_addr = mmap(0, mapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (vir_addr == MAP_FAILED) {
        printf("%s mmap error\n", __func__);
        return NULL;
    }
    return vir_addr;
}

/*write regs*/
static void write_reg(uint32_t offset,uint32_t val)
{
    *((uint32_t volatile *)((char *)reg_base + offset)) = val;
}

/*read regs*/
static uint32_t read_reg(uint32_t offset)
{
    uint32_t val = *((uint32_t volatile *)((char *)reg_base + offset));
    return val;
}

void central_crosshair_set(int flag)
{
    if ((flag != 0 && flag != 1)) {
        printf("invalid flag\n");
        return;
    }

    write_reg(CENTRAL_CROSS_SELECT_REG, flag);
}

void central_crosshair_pos_set(int row, int col)
{
    // Combine the row and column into a single 32-bit value
    uint32_t reg_value = ((row & 0xFFFF) << 16) | (col & 0xFFFF);

    // Write the value to the register
    write_reg(CENTRAL_CROSS_POSITION_REG, reg_value);

}

void central_crosshair_len_set(int len)
{
    write_reg(CENTRAL_CROSS_LENGTH_REG, len);

}

/*
 * target_crosshairs_set
 * Function to set the crosshair display
 *
 * flag
 * 0: disable
 * 1: enable
 *
 */
void target_crosshair_set(int crosshair_num, int flag)
{
    if (crosshair_num < 0 || crosshair_num > 9 || (flag != 0 && flag != 1)) {
        // Invalid crosshair number or flag, handle the error appropriately
        printf("invalid crosshair number or flag\n");
        return;
    }

    // Read the current value of the TARGET_CROSS_DISPLAY_SELECT_REG
    uint32_t reg_value = read_reg(TARGET_CROSS_DISPLAY_SELECT_REG);

    // Update the specific bit for the crosshair
    if (flag == 1) {
        reg_value |= (1 << crosshair_num); // Set the bit to enable the crosshair
    } else {
        reg_value &= ~(1 << crosshair_num); // Clear the bit to disable the crosshair
    }

    // Write the updated value back to the register
    write_reg(TARGET_CROSS_DISPLAY_SELECT_REG, reg_value);
}

void target_crosshair_pos_set(int crosshair_num, int row, int col)
{

    if (crosshair_num < 0 || crosshair_num > 9) {
        // Invalid crosshair number, handle the error appropriately
        return;
    }

    // Calculate the register address for the specified crosshair number
    uint32_t reg_address = TARGET_CROSS_POSITION_REG(crosshair_num);

    // Combine the row and column into a single 32-bit value
    uint32_t reg_value = ((row & 0xFFFF) << 16) | (col & 0xFFFF);

    // Write the value to the register
    write_reg(reg_address, reg_value);
}

void target_crosshair_len_set(int crosshair_num, int len)
{

    if (crosshair_num < 0 || crosshair_num > 9) {
        // Invalid crosshair number, handle the error appropriately
        return;
    }

    // Calculate the register address for the specified crosshair number
    uint32_t reg_address = TARGET_CROSS_LENGTH_REG(crosshair_num);

    // Write the value to the register
    write_reg(reg_address, len);
}

void character_data_set(int char_num, int flag, int char_size, uint8_t *buf)
{
    int i;
    uint32_t reg_addr;

    if (flag == 1)
        reg_addr = UPPER_CHAR_DATA_REG(char_num);
    else if (flag == 0)
        reg_addr = LOWER_CHAR_DATA_REG(char_num);

    for (i = 0; i < char_size; i+=4)
    {
       write_reg(reg_addr, buf[i]);
    }

}

void character_data_position_set(int col, int row, int flag)
{
    uint32_t reg_addr;

    if (flag == 1)
        reg_addr = UPPER_CHAR_START_COORD_REG;
    else if (flag == 0)
        reg_addr = LOWER_CHAR_START_COORD_REG;

    write_reg(reg_addr, (col | (row << 16)));

}

void character_data_set_complete()
{
    write_reg(CHAR_DATA_COMPLETE_REG, 1);

}

void character_data_size_set(int width, int height)
{
    write_reg(CHAR_SIZE_REG, (height | (width << 16)));

}

// Function to set the character spacing
void character_data_space_set(int char_space, int flag)
{
    // Read the current value of the CHAR_SPACING_REG
    uint32_t reg_value = read_reg(CHAR_SPACING_REG);

    if (flag == 1) {
        // Set the spacing for the upper characters
        reg_value = (reg_value & 0xFFFF0000) | (char_space & 0xFFFF);
    } else {
        // Set the spacing for the lower characters
        reg_value = (reg_value & 0x0000FFFF) | ((char_space & 0xFFFF) << 16);
    }

    // Write the updated value back to the CHAR_SPACING_REG
    write_reg(CHAR_SPACING_REG, reg_value);

}

void uart_disable(void)
{
    int val;
    int gpio_reg = GPIO_REG;

    val = read_reg(gpio_reg);
    val &= (~UART_PORT_ENABLE);
    write_reg(gpio_reg, val);
}

void uart_enable(void)
{
    int val;
    int gpio_reg = GPIO_REG;

    val = read_reg(gpio_reg);
    val |= UART_PORT_ENABLE;
    write_reg(gpio_reg, val);
}

static int uart_sem_init(void)
{
    int i;
    int ret = 0;

    for (i = 0; i < UART_PORT_NUM; i++) {
        ret = sem_init(&uart_kfifo_sem[i], 0, 0);
        if (ret != 0) {
            printf("%s: uart_kfifo_sem[%d] init error\n", __func__, i);
            return -1;
        }
    }

    return ret;

}


/**
* init uart.
* Return Value: 0 if success, otherwise error code
*/
int uart_port_init(uint32_t uart_num, uint32_t baundrate)
{
    int ret = 0;

    if (uart_num > UART_PORT_NUM) {
        printf("%s: invalid parameters\n", __func__);
        return -1;
    }

    /* 0.set the frequency division factor */
    write_reg(UART_BAUNDRATE(uart_num), FPGA_CLOCK/baundrate);

    uart_enable();

    return ret;
}

static int fpga_uart_recv_from_reg(uint32_t uart_num, uint32_t count, char *buf)
{
    int i, val;

    for (i = 0; i < count; i++) {
       val = read_reg(UART_DATA(uart_num));
       buf[i] = val;
    }

    return count;
}


/**/
static int fpga_uart_recv(uint32_t uart_num, uint32_t count)
{
#ifdef UART_DATA_PRINT
    int i;
#endif
    int ret = 0;
    int fifo_avail, recv_len;
    /*An integer multiple of 4 bytes ?*/
    char data_buf[UART_MAX_DATA_LEN] = {0};
    struct kfifo *fifo = &uart_recv_fifo[uart_num];

    recv_len = fpga_uart_recv_from_reg(uart_num, count, data_buf);
#ifdef UART_DATA_PRINT
    for (i = 0; i < recv_len; i++)
       printf("%s: off: %d, val: 0x%x\n",__func__, i, data_buf[i]);
#endif

    fifo_avail = kfifo_avail(fifo);

    if (fifo_avail >= recv_len) {
        kfifo_in(fifo, data_buf, recv_len);
        sem_post(&uart_kfifo_sem[uart_num]);
        ret = recv_len;
    } else {
        //printf("uart_recv_fifo[%d] has no enough room\n",uart_num);
        ret  = 0;
    }
    return ret;
}

/**
* @brief
*
* @Param uart_num
* @Param buf
* @Param count
*
* @Returns
*/
int uart_read(uint32_t uart_num, char *buf, uint32_t count)
{
#ifdef UART_DATA_PRINT
    uint32_t i;
#endif
    uint32_t rd_len;
    uint32_t used_bytes;
    struct kfifo *fifo = &uart_recv_fifo[uart_num];

    if (uart_num > UART_PORT_NUM || !buf) {
        printf("%s parameters error\n",__func__);
        return -1;
    }
    sem_wait(&uart_kfifo_sem[uart_num]);

    used_bytes = kfifo_len(fifo);
    if (used_bytes >= count) {
        rd_len = kfifo_out(fifo, buf, count);
    } else {
        //printf("Not enough data for one frame %d\n", used_bytes);
        return -1;
    }
#ifdef UART_DATA_PRINT
    for (i = 0; i < count; i++)
       printf("%s: off: %d, val: 0x%x\n",__func__, i, buf[i]);
#endif

    return rd_len;
}

int getlen_fifo(uint32_t uart_num)
{
#ifdef UART_DATA_PRINT
    uint32_t i;
#endif

    uint32_t used_bytes;
    struct kfifo *fifo = &uart_recv_fifo[uart_num];

    //sem_wait(&uart_kfifo_sem[uart_num]);

    used_bytes = kfifo_len(fifo);
    return used_bytes;
}
static int fpga_uart_send_to_reg(uint32_t uart_num, char *buf, uint32_t count)
{
    int i;
    uint32_t reg = UART_DATA(uart_num);

    for (i = 0; i < count; i++)
    {
        write_reg(reg, buf[i]);
    }

    return count;
}

/**
* @brief
*
* @Param uart_num
* @Param buf
* @Param count
*
* @Returns
*/
static int fpga_uart_send(uint32_t uart_num, char *buf, uint32_t count)
{
    int ret;
    uint32_t fifo_flag;
    uint32_t uart_send_fifo_reg = UART_SEND_FIFO_STATUS;

    /* Check if there is a frame of space
     */
    fifo_flag = (read_reg(uart_send_fifo_reg) >> uart_num) & 0x1;

    do {
        if (fifo_flag == 1)
            break;
        else
            usleep(1000);

        fifo_flag = (read_reg(uart_send_fifo_reg) >> uart_num) & 0x1;
    } while (fifo_flag == 0);

    ret = fpga_uart_send_to_reg(uart_num, buf, count);

    return ret;
}

/**
* @brief
*
* @Param uart_num
* @Param buf
* @Param count
*
* @Returns
*/
int uart_write(uint32_t uart_num, char *buf, uint32_t count)
{
    int ret;

    ret = fpga_uart_send(uart_num, buf, count);

    return ret;

}

static void *uart_recv(void *p)
{
    int i;
    int all_ports_empty;

    while (uart_recv_work)
    {
        all_ports_empty = 1;

        for (i = 0; i < UART_PORT_NUM; i++)
        {
            uint32_t count = read_reg(UART_FIFO_COUNT(i));

            if (count != 0) {
                fpga_uart_recv(i, count);
                all_ports_empty = 0; // At least one port had data
            }
        }

        if (all_ports_empty) {
            usleep(5);  // Sleep for 5 microseconds
        }
    }
    return NULL;
}

void sync_module_disable(void)
{
    int val;
    int gpio_reg = GPIO_REG;

    val = read_reg(gpio_reg);
    val &= (~SYNC_PORT_ENABLE);
    write_reg(gpio_reg, val);
}

void sync_module_enable(void)
{
    int val;
    int gpio_reg = GPIO_REG;

    val = read_reg(gpio_reg);
    val |= SYNC_PORT_ENABLE;
    write_reg(gpio_reg, val);
}

/**
 * @brief sync_duty_out_set
 * The duration of the low level or high level is in multiples of 8ns.
 *
 * @param freq
 *
 * @return
 */
void sync_duty_out_set(double time_in_seconds)
{
    // Convert time from seconds to 8ns intervals
    int times = (int)(time_in_seconds / 8e-9);

    // Write the calculated value to the register
    write_reg(SYNC_DUTY_OUT, times);
}

/**
 * @brief sync_freq_out_set
 *
 * @param freq
 *
 * @return
 */
void sync_freq_out_set(int freq)
{
    int reg_value = (int)(1.0 / ((double)freq * 8e-9));

    write_reg(SYNC_FREQ_OUT, reg_value);
}
/**
 * @brief sync_output_set
 *
 * @param polarity 0 rising edge; 1 falling edge
 */
void sync_out_polarity_sel(int polarity)
{
    write_reg(SYNC_OUT, polarity);
}

/**
 * @brief sync_input_set
 *
 * @param polarity 0 rising edge; 1 falling edge
 */
void sync_input_polarity_sel(int polarity)
{
    write_reg(SYNC_IN, polarity);
}

#ifdef SYNC_MODULE_TEST
void sync_module_init()
{
    // do nothing
}
#endif

static int image_sem_init(void)
{
    if (sem_init(&cameralink_rx_sem, 0, 0) != 0) {
        printf("%s: cameralink_rx_sem init error\n", __func__);
        return -1;
    }
    /* Initialized to 3 for sdi port reception */
    if (sem_init(&sdi_tx_sem, 0, 2) != 0) {
        printf("%s: sdi_tx_sem init error\n", __func__);
        return -1;
    }

    if (sem_init(&cameralink_kfifo_sem, 0, 0) != 0) {
        printf("%s: sdi_kfifo_sem init error\n", __func__);
        return -1;
    }

    return 0;
}

/**
* @brief Initializes the semaphores
*/
static int sdi_mutex_init(void)
{
    /**
    * Used to protect the frame buffer,
    * the host is the writer, FPGA is the reader
    */
    if (pthread_mutex_init(&sdi_send_mutex, NULL) != 0) {
        printf("%s: sdi_send_mutex created error\n", __func__);
        return -1;
    }

    if (pthread_mutex_init(&sdi_write_mutex, NULL) != 0) {
        printf("%s: sdi_write_mutex created error\n", __func__);
        return -1;
    };

    return 0;

}

/**
 * @brief fpga_cameralink_recv
 *
 * @param flag
 *
 * @return
 */
static int fpga_cameralink_recv(int flag)
{
    int rx_len;
    struct kfifo *fifo = &cameralink_recv_fifo;
    uint32_t cameralink_offset = flag ? cam_pong_start_addr : cam_ping_start_addr;
    uint32_t count = cam_image_size;

    lseek(c2h_fd, cameralink_offset, SEEK_SET);

    time2 = QDateTime::currentDateTime();
    rx_len = read(c2h_fd, cam_rx_buf, count);
    if (rx_len != count) {
        printf("%s cameralink recv error\n",__func__);
        return rx_len;
    }
    qDebug() << QString(" read pcie use time %1ms ").arg(time2.msecsTo(QDateTime::currentDateTime()));
    qDebug() << QString(" read 1 FRAM total time %1ms ").arg(lastirq_time.msecsTo(QDateTime::currentDateTime()));
    lastirq_time = QDateTime::currentDateTime();

    //缓存list写入前30贞

//    if(frame_in_kfifo<30){
//        memcpy(rev_List[frame_in_kfifo],cam_rx_buf,75497472);
//    }

    frame_in_kfifo++;

    if (kfifo_avail(fifo) >= count) {
        kfifo_in(fifo, cam_rx_buf, count);
        rx_len = count;


#ifdef SHOW_INFO
#endif
        sem_post(&cameralink_kfifo_sem);
    } else {
        //printf("cameralink: no enough space and the frame is discarded\n");
        return -1;
    }
    return rx_len;
}

/**
* @brief
*
* @Param sdi_num
* @Param buf
* @Param count
*
* @Returns
*   count: success;
*   < count: failed;
*/
int cameralink_read(uint8_t *buf, uint32_t count)
{
    uint32_t rd_len = 0;
    struct kfifo *fifo = &cameralink_recv_fifo;

    if (!buf) {
        printf("%s invalid parameters\n", __func__);
        return -1;
    }
#ifdef SHOW_INFO
    cameralink_read_count++;
#endif
    sem_wait(&cameralink_kfifo_sem);
    /*
     * write[kfifo->in, kfifo->in + len]
     * update kfifo->in to kfifo->in + len
     */
    rd_len = kfifo_out(fifo, buf, count);
    if (rd_len < count) {
        printf("The dequeue frame size %d is not correct!", rd_len);
    } else {
#ifdef SHOW_INFO
    frame_out_kfifo++;
#endif
    }

    return rd_len;
}

static int sdi_can_send(void)
{
    int send_done = 0;

    pthread_mutex_lock(&sdi_send_mutex);
    send_done = sdi_send_done;
    pthread_mutex_unlock(&sdi_send_mutex);

    return send_done;
}

static void clear_send_done(void)
{
    /*ping or pong*/
    int flag = sdi_send_flag;

    pthread_mutex_lock(&sdi_send_mutex);
    sdi_send_done &= (~(1 << flag));
    pthread_mutex_unlock(&sdi_send_mutex);

    sdi_send_flag = !flag;
}

/**
 * @brief fpga_sdi_send
 *
 * @param sdi_num
 * @param buf
 * @param count
 *
 * @return
 */
static int fpga_sdi_send(uint8_t *buf, uint32_t count)
{
    int tx_len = 0;
    /* ping or pong */
    uint32_t sdi_offset;
    uint32_t write_done_reg;

    sem_wait(&sdi_tx_sem);
    //usleep(10000);

    if (sdi_send_flag == 0) {
        // ping
        sdi_offset = SDI_PING_START_ADDR;
        write_done_reg = SDI_PING_WRITE_DONE_REG;
    } else if (sdi_send_flag == 1) {
        // pong
        sdi_offset = SDI_PONG_START_ADDR;
        write_done_reg = SDI_PONG_WRITE_DONE_REG;
    }

    if (sdi_can_send()) {
        lseek(h2c_fd, sdi_offset, SEEK_SET);


        while(lastirq_time.msecsTo(QDateTime::currentDateTime())<100)
            usleep(1000);
        qDebug() << QString(" write pcie  time %1 ").arg(lastirq_time.msecsTo(QDateTime::currentDateTime()));
        lastirq_time = QDateTime::currentDateTime();

        tx_len = write(h2c_fd, buf, count);



        if (tx_len != count) {
            printf("%s write error\n",__func__);
            return -1;
        }
        clear_send_done();
        /**
        * Tell the FPGA that the image is in memory.
        * 0x20 bit0 ping has writen to the fpga
        * 0x24 bit1 pong has writen to the fpga
        */
        write_reg(write_done_reg, 1);
#ifdef SHOW_INFO
        sdi_write_count++;
#endif
    } else {
#ifdef SHOW_INFO
        sdi_write_lost_count++;
#endif
        printf(" %s has not been sent\n", sdi_send_flag ? "pong" : "ping");
        return -1;
    }

    return tx_len;
}

/**
* @brief
*
* @Param sdi_num
* @Param buf
* @Param count
*
* @Returns count: success;
*          < count:    failed;
*/
int sdi_write(uint8_t *buf, uint32_t count)
{
    int ret;

    if (!buf) {
        printf("%s parameters error\n",__func__);
        return -1;
    }
    pthread_mutex_lock(&sdi_write_mutex);
    ret = fpga_sdi_send(buf, count);
    pthread_mutex_unlock(&sdi_write_mutex);

    return ret;

}

#ifdef SHOW_INFO
static void *show_info(void *p)
{
    while (show_info_work)
    {

        printf("frame_in_fifo: %d\n", frame_in_kfifo);
        printf("frame_out_fifo: %d\n", frame_out_kfifo);
        printf("cameralink_read_count: %d\n", cameralink_read_count);
        printf("sdi_write_count: %d\n", sdi_write_count);
        printf("sdi_write_lost_count: %d\n", sdi_write_lost_count);
        printf("cameralink_recv_int_count: %d\n", cameralink_recv_int_count);
        printf("sdi_send_int_count: %d\n", sdi_send_int_count);
        usleep(3000000);
    }
    return NULL;
}
#endif

static void *cameralink_recv(void *p)
{
    int cameralink_flag;

    while (cameralink_recv_work)
    {
        /* wait cameralink receive interrupt */
        sem_wait(&cameralink_rx_sem);
#ifdef SHOW_INFO
        cameralink_recv_int_count++;
#endif
        /**
        * 0: ping 1: pong
        */
        cameralink_flag = read_reg(IRQ_UP_FLAG) & 0x1;
        fpga_cameralink_recv(cameralink_flag);
    }
    return NULL;
}

/**
 * @brief set_send_done
 *  It will be called by the function event_down.
 *
 * @param st
 *
 * @return
 */
static int set_send_done()
{
    int irq_down_flag = read_reg(IRQ_DOWN_FLAG);
    int flag = CHECK_BIT(irq_down_flag, 0);
#ifdef SHOW_INFO
    sdi_send_int_count++;
#endif
    /*
     * 1.(irq_down_flag >> i) & 0x1:
     *  Extract the ping/pong flag of the corresponding SDI channel
     * 2. ping=0,pong=1; 1 << flag:
     *  If it is a ping interrupt, then set bit0 of
     *  sdi_send_done for the corresponding SDI channel to 1;
     *  if it is a pong interrupt, then set bit1 to 1.
     * */
    pthread_mutex_lock(&sdi_send_mutex);
    sdi_send_done |= (1 << flag);
    pthread_mutex_unlock(&sdi_send_mutex);

    return 0;
}

/**
* @brief usr_irq_req 0
*
* @Param p
*
* @Returns
*/
static void *event_up(void *p)
{
    int event_up_fd;
    uint32_t status;

    event_up_fd = open_event(DEVICE_EVENT_UP);
    if (event_up_fd < 0) {
        printf("%s: open %s error\n", __func__, DEVICE_EVENT_UP);
        return NULL;
    }

    while (event_up_work)
    {
       /* it will block when there has no interrupt
         */
        read_event(event_up_fd);

        qDebug() << QString(" IRQ use time %1ms ").arg(time1.msecsTo(QDateTime::currentDateTime()));
                time1 = QDateTime::currentDateTime();

        status = read_reg(IRQ_UP_STATUS);

        if (status & 0x1) {
            sem_post(&cameralink_rx_sem);
        }
        /* clear interrupt */
        write_reg(IRQ_UP_CLEAR, status);
    }
    if (event_up_fd >= 0)
        close(event_up_fd);

    return NULL;
}


/**
* @brief usr_irq_req 1
*
* @Param p
*
* @Returns
*/
static void *event_down(void *p)
{
    uint32_t status;
    int event_down_fd;

    event_down_fd = open_event(DEVICE_EVENT_DOWN);
    if (event_down_fd < 0) {
        printf("open %s error\n",DEVICE_EVENT_DOWN);
    }

    while (event_down_work)
    {
        /* read /dev/xdma0_events_1 */
        read_event(event_down_fd);

        status = read_reg(IRQ_DOWN_STATUS);

        /* Check that the SDI channel has been sent */
        if (status & 0x1) {
            set_send_done();
            sem_post(&sdi_tx_sem);
        }
        /* clear interrupt */
        write_reg(IRQ_DOWN_CLEAR, status);
    }

    if (event_down_fd >= 0)
        close(event_down_fd);

    return NULL;
}

static void xdma_reset(void)
{
    int gpio_reg = GPIO_REG;

    /**
    * bit[0]: 1 assert reset signal, 0 deassert
    */
    write_reg(gpio_reg, 1);
    usleep(1000);
    write_reg(gpio_reg, 0);
}

static void fpga_init(void)
{
    /* reset the lvds module */
    xdma_reset();
}

static void sem_mutex_deinit(void)
{
    int i;

    sem_destroy(&cameralink_rx_sem);
    sem_destroy(&sdi_tx_sem);

    sem_destroy(&cameralink_kfifo_sem);
    pthread_mutex_destroy(&sdi_send_mutex);

    for (i = 0; i < UART_PORT_NUM; i++) {
        sem_destroy(&uart_kfifo_sem[i]);
    }

    pthread_mutex_destroy(&sdi_write_mutex);
}

static int kfifos_init()
{
    int i;
    int ret = 0;

    for (i = 0; i < UART_PORT_NUM; i++)
    {
        /*The third parameter is not used*/
        ret = kfifo_alloc(&uart_recv_fifo[i], UART_KFIFO_SIZE, 0);
        if (ret != 0) {
            printf("%s uart kfifo init failed\n",__func__);
            return -1;
        }

    }

    return 0;
}



static void kfifos_deinit(void)
{
    int i;

    for (i = 0; i < UART_PORT_NUM; i++)
    {
        kfifo_free(&uart_recv_fifo[i]);
    }

    kfifo_free(&cameralink_recv_fifo);
}

/* map the fpga regs in usersapce */
static int fpga_regs_map_init(void)
{
    int reg_fd;

    // pcie bar0
    reg_fd = open_control(DEVICE_REG);
    if (reg_fd < 0) {
        printf("%s: open %s error\n", __func__, DEVICE_REG);
        return -1;
    }

    reg_base = mmap_control(reg_fd, PCIE_BAR0_SIZE);
    if (!reg_base) {
        printf("%s: mmap_control error\n", __func__);
        close(reg_fd);
        return -1;
    }

    return 0;

}

static void cam_image_mem_init(uint32_t cam_ping_start_addr, uint32_t cam_ping_end_addr, uint32_t cam_pong_start_addr, uint32_t cam_pong_end_addr)
{
    write_reg(CAMERALINK_PING_START_REG, cam_ping_start_addr);
    write_reg(CAMERALINK_PING_END_REG, cam_ping_end_addr);
    write_reg(CAMERALINK_PONG_START_REG, cam_pong_start_addr);
    write_reg(CAMERALINK_PONG_END_REG, cam_pong_end_addr);
}

static void sdi_image_mem_init(uint32_t sdi_ping_start_addr, uint32_t sdi_ping_end_addr, uint32_t sdi_pong_start_addr, uint32_t sdi_pong_end_addr)
{
    write_reg(SDI_PING_START_REG, sdi_ping_start_addr);
    write_reg(SDI_PING_END_REG, sdi_ping_end_addr);
    write_reg(SDI_PONG_START_REG, sdi_pong_start_addr);
    write_reg(SDI_PONG_END_REG, sdi_pong_end_addr);
}

static void cameralink_size_set(uint32_t cam_image_size)
{
    write_reg(CAMERALINK_IMAGE_SIZE_REG, (cam_image_size/1024/4));
}

static void sdi_size_set(uint32_t sdi_image_size)
{
    write_reg(SDI_IMAGE_SIZE_REG, (sdi_image_size/1024/4));
}

static void cameralink_mode_set(uint32_t mode)
{
    write_reg(CAMERALINK_MODE_REG, mode);
}

static void cameralink_param_set(uint32_t taps, uint32_t bits)
{
    write_reg(CAMERALINK_PARAM_REG, ((bits << 16) | taps));
}

static void cameralink_format_set(uint32_t width, uint32_t height)
{
    write_reg(CAMERALINK_IMAGE_FORMAT_REG, ((height <<16) | width));
}

static void image_port_enable(void)
{
    int val;

    val = read_reg(GPIO_REG);
    val |= CAMERALINK_PORT_ENABLE | SDI_PORT_ENABLE;
    write_reg(GPIO_REG, val);
}

void image_port_disable(void)
{
    int val;

    val = read_reg(GPIO_REG);
    val &= (~(CAMERALINK_PORT_ENABLE | SDI_PORT_ENABLE));
    write_reg(GPIO_REG, val);
}


/**
 * @brief image_init
 *
 */
int image_init(uint32_t width, uint32_t height, uint32_t taps, uint32_t bits, uint32_t mode, uint32_t image_kfifo_num)
{

    int ret = 0;

    if (mode != 0 && mode != 1 && mode != 2) {
        printf("%s cameralink mode set error, only 0(base) or 2(full)\n", __func__);
        return -1;
    }
    // Calculate the size of the image
    bytes_per_pixel = (bits == 8 ? 1 : 2);
    taps_per_pixel = (taps == 3 ? 3 : 1);
   // cam_image_size = width*height*bytes_per_pixel*taps;
    cam_image_size = width*height*bytes_per_pixel*taps_per_pixel;
    // yuyv422 8bits
    sdi_image_size = width*height*2*taps_per_pixel;

    kfifo_size = image_kfifo_num*cam_image_size;

    // The third parameter is not used
    ret = kfifo_alloc(&cameralink_recv_fifo, kfifo_size, 0);
    if (ret != 0) {
        printf("%s cameralink kfifo init failed\n", __func__);
        return -1;
    }

    cam_rx_buf =(char *)malloc (cam_image_size);
    if (!cam_rx_buf) {
        printf("%s cameralink receive buff malloc failed\n", __func__);
        return -1;
    }

    // Calculate the address of the image
    cam_ping_start_addr = CAMERALINK_PING_START_ADDR;
    cam_ping_end_addr = cam_ping_start_addr + cam_image_size;
    cam_pong_start_addr = CAMERALINK_PONG_START_ADDR;
    cam_pong_end_addr = cam_pong_start_addr + cam_image_size;
    sdi_ping_start_addr = SDI_PING_START_ADDR;
    sdi_ping_end_addr = sdi_ping_start_addr + sdi_image_size;
    sdi_pong_start_addr = SDI_PONG_START_ADDR;
    sdi_pong_end_addr = sdi_pong_start_addr + sdi_image_size;

    cam_image_mem_init(cam_ping_start_addr, cam_ping_end_addr, cam_pong_start_addr, cam_pong_end_addr);
    sdi_image_mem_init(sdi_ping_start_addr, sdi_ping_end_addr, sdi_pong_start_addr, sdi_pong_end_addr);

    cameralink_size_set(cam_image_size);
    sdi_size_set(sdi_image_size);

    cameralink_mode_set(mode);
    cameralink_format_set(width, height);
    cameralink_param_set(taps, bits);

    image_port_enable();

    return 0;
}

/**
 * @brief xdma_app_init
 *
 * @return
 *   0 on success; -1 on error.
 */
int xdma_app_init(void)
{
    char *device_h2c = DEVICE_H2C;
    char *device_c2h = DEVICE_C2H;

    /* open h2c device(/dev/xdma0_h2c_0) */
    h2c_fd = open(device_h2c, O_RDWR | O_NONBLOCK);
    if (h2c_fd < 0) {
        printf("%s : open %s error\n", __func__, device_h2c);
        return -1;
    }
    /* open c2h device(/dev/xdma0_c2h_0) */
    c2h_fd= open(device_c2h, O_RDWR | O_NONBLOCK);
    if (c2h_fd < 0) {
        printf("%s : open %s error\n", __func__, device_c2h);
        return -1;
    }
    if (uart_sem_init() != 0) {
        printf("%s uart_sem_init error\n", __func__);
        return -1;
    }
    if (image_sem_init() != 0) {
        printf("%s sdi_sem_init error\n", __func__);
        return -1;
    }
    if (sdi_mutex_init() != 0) {
        printf("%s sdi_sem_init error\n", __func__);
        return -1;
    }
    if (fpga_regs_map_init() != 0) {
        printf("%s fpga_reg_map_init error\n", __func__);
        return -1;
    }
    if (kfifos_init() != 0) {
        printf("%s fpga_reg_map_init error\n", __func__);
        return -1;
    }

    fpga_init();

    return 0;
}

void xdma_event_init(void)
{
    event_up_work = 1;
    event_down_work = 1;
    pthread_create(&event_up_thread, NULL, event_up, NULL);
    pthread_create(&event_down_thread, NULL, event_down, NULL);
    uart_recv_work = 1;
    pthread_create(&uart_recv_thread, NULL, uart_recv, NULL);
    cameralink_recv_work = 1;
    pthread_create(&cameralink_recv_thread, NULL, cameralink_recv, NULL);
//#ifdef SHOW_INFO
//    pthread_create(&show_info_thread, NULL, show_info, NULL);
//#endif
}

void xdma_app_uart_recv_stop(void)
{
    uart_recv_work = 0;
    pthread_join(uart_recv_thread, NULL);
}

void xdma_app_send_stop(void)
{
    printf("%s %d\n", __func__, __LINE__);
    /* exit the pthreads */

    event_down_work = 0;

//#ifdef SHOW_INFO
//    show_info_work = 0;
//#endif

    pthread_join(event_down_thread, NULL);


//#ifdef SHOW_INFO
//    pthread_join(show_info_thread, NULL);
//#endif
    /* disable sdi port */
    image_port_disable();
    /* disable sdi port */
    uart_disable();
    /* destroy the sem and mutex */
    sem_mutex_deinit();
    kfifos_deinit();
    /* free the fpga regs of mmap */
    if (reg_base)
        munmap(reg_base, PCIE_BAR0_SIZE);
    /* close the fds */
    if (reg_fd)
        close(reg_fd);
    if (h2c_fd)
        close(h2c_fd);
    if (c2h_fd)
        close(c2h_fd);
    printf("%s %d\n", __func__, __LINE__);
}

void xdma_app_receive_stop(void)
{
    printf("%s %d\n", __func__, __LINE__);
    /* exit the pthreads */
    event_up_work = 0;
    cameralink_recv_work = 0;
//#ifdef SHOW_INFO
//    show_info_work = 0;
//#endif
    pthread_join(event_up_thread, NULL);
    pthread_join(cameralink_recv_thread, NULL);

//#ifdef SHOW_INFO
//    pthread_join(show_info_thread, NULL);
//#endif
    /* disable sdi port */
    image_port_disable();
    /* disable sdi port */
    uart_disable();
    /* destroy the sem and mutex */
    sem_mutex_deinit();
    kfifos_deinit();
    /* free the fpga regs of mmap */
    if (reg_base)
        munmap(reg_base, PCIE_BAR0_SIZE);
    /* close the fds */
    if (reg_fd)
        close(reg_fd);
    if (h2c_fd)
        close(h2c_fd);
    if (c2h_fd)
        close(c2h_fd);
    printf("%s %d\n", __func__, __LINE__);
}

