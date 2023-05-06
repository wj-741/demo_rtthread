/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 * 
 * @file      malloc_task.c
 * @author    wj (tjwangj@126.com)
 * @version   V0.1
 * @date      2023-05-06
 * @brief 
 * 
 * **********************************************************************************
 */
#include "malloc_task.h"
#include <rtthread.h>

#define MALLOC_TASK_PRIORITY     24
#define MALLOC_TASK_STACK_SIZE   256
#define MALLOC_TASK_TIMESLICE    5

static rt_thread_t t_malloc_task = RT_NULL;

/**
 * @brief 线程1的入口函数
 * @param  parameter        参数
 */
static void malloc_task_entry(void * parameter)
{
    rt_uint32_t index = 0;

    while(1)
    {
        if(index < 10)
        {
            rt_kprintf("malloc task count: %d\n", index++);
        }

        rt_thread_mdelay(500);
    }
}


/**
 * @brief 创建malloc_task_sample，并启动
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
MSH_CMD_EXPORT(malloc_task_sample, run malloc task);
