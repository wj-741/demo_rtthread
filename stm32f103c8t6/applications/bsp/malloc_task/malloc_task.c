/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 * 
 * @file      malloc_task.c
 * @author    wj (tjwangj@126.com)
 * @version   V0.1
 * @date      2023-05-08
 * @brief     
 * 
 * **********************************************************************************
 */
#include "malloc_task.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"


#define MALLOC_TASK_PRIORITY     24
#define MALLOC_TASK_STACK_SIZE   256
#define MALLOC_TASK_TIMESLICE    5

static rt_thread_t t_malloc_task = RT_NULL;

#define LED1_PIN    GET_PIN(A, 2)

/**
 * @brief  线程1的入口函数
 * @param  parameter        My Param doc
 */
static void malloc_task_entry(void * parameter)
{
    rt_uint32_t index = 0;
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_err_t retval = RT_EOK;

    while(1)
    {
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        rt_kprintf("malloc_task count: %d\n", index++);

        if(5 == index)
        {
            //retval = rt_thread_detach(t_malloc_task);

            retval = rt_thread_delete(t_malloc_task);

            if(RT_EOK == retval)
                rt_kprintf("delete malloc_task successful!\n");
            else
                rt_kprintf("delete malloc_task failed!\n");
        }
    }
}


/**
 * @brief  创建malloc_task_sample，并启动
 * @return int 
 */
int malloc_task_sample(void)

{
    /* 初始化线程1, 名称是static_task, 入口是static_task_entry */
    t_malloc_task = rt_thread_create("malloc_task",
                                     malloc_task_entry,
                                     RT_NULL,
                                     MALLOC_TASK_STACK_SIZE,
                                     MALLOC_TASK_PRIORITY,
                                     MALLOC_TASK_TIMESLICE);

    /* 启动线程 */
    if(t_malloc_task != RT_NULL)
        rt_thread_startup(t_malloc_task);

    return 0;
}

 /* 导出到msh命令列表 */
 MSH_CMD_EXPORT(malloc_task_sample, create & delete malloc task);
