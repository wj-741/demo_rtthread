/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 * 
 * @file      bsp_uart.c
 * @author    wj (tjwangj@126.com)
 * @version   V0.1
 * @date      2023-05-08
 * @brief     
 * 
 * **********************************************************************************
 */
#include "bsp_uart.h"
#include <rtthread.h>

#define SAMPLE_UART_NAME    "uart3"     /* 需要操作的设备 */
static rt_device_t serial;              /* 设备句柄 */
static char str[] = "hello, this first uart demo!\r\n"; /* 需要发送的数据 */

static int uart_sample(void)
{
    rt_err_t retval = RT_EOK;
    rt_size_t send_len = 0;

    serial = rt_device_find(SAMPLE_UART_NAME);
    if(RT_NULL == serial)
    {
        rt_kprintf("find %s failed!\r", SAMPLE_UART_NAME);
        return -RT_ERROR;
    }

    /* 以中断形式接收及轮询发送模式打开串口设备*/
    retval = rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    if(RT_EOK != retval)
    {
        rt_kprintf("open device failed!\r");
        return -RT_ERROR;
    }

    /* 发送字符串 */
    send_len = rt_device_write(serial, 0, str, (sizeof(str) - 1));
    if((sizeof(str) - 1) != send_len)
    {
        rt_kprintf("send data failed!\r");
        return -RT_ERROR;
    }

    /* 关闭设备 */
    retval  = rt_device_close(serial);
    if(RT_EOK != retval)
    {
        rt_kprintf("close device failed!\r");
        return -RT_ERROR;
    }

    rt_kprintf("serial device test successful!\r");

    return RT_EOK;

}

/* 导出到 msh 命令列表 */
MSH_CMD_EXPORT(uart_sample, uart device sample);
