/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-19     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <rtdevice.h>
#include "drv_common.h"
#include <bsp/static_task/static_task.h>
#include <bsp/malloc_task/malloc_task.h>

#define LED1_PIN    GET_PIN(A, 2)
#define LED2_PIN    GET_PIN(A, 1)

int main(void)
{
    int count = 1;

//    static_task_sample();
//    malloc_task_sample();

    LOG_D("Hello RT-Thread!");
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        //LOG_D("Hello RT-Thread!");
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
