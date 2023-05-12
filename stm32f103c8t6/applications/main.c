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

#include <bsp/static_task/static_task.h>
#include <bsp/malloc_task/malloc_task.h>


int main(void)
{
    int count = 1;

    //static_task_sample();
    //malloc_task_sample();

    LOG_D("Hello RT-Thread!");

    while (count++)
    {
        if(count < 2)
        {
            LOG_D("main running!");
        }

        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
