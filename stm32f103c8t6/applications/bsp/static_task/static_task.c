/**
 * **********************************************************************************
 * @copyright Copyright (c) 2023 Shaanxi Tianji Communication Technologies Co., Ltd.
 * 
 * @file      static_task.c
 * @author    wj (tjwangj@126.com)
 * @version   V0.1
 * @date      2023-05-06
 * @brief 
 * 
 * **********************************************************************************
 */
#include "static_task.h"
#include <rtthread.h>

#define STATIC_TASK_PRIORITY     25
#define STATIC_TASK_STACK_SIZE   512
#define STATIC_TASK_TIMESLICE    5


/* 使用静态线程时,线程的栈需要设置字节对齐 */
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t static_task_stack[STATIC_TASK_STACK_SIZE];    // 提前分配任务栈空间
static struct rt_thread static_task;

/**
 * @brief 线程1的入口函数
 * @param  parameter        参数
 */
static void static_task_entry(void * parameter)
{
    rt_uint32_t index = 0;

    while(1)
    {
        if(index < 10)
        {
            rt_kprintf("static task count: %d\n", index++);
        }

        rt_thread_mdelay(500);
    }
}


/**
 * @brief 创建static_task_sample，并启动
 * @return int 
 */
int static_task_sample(void)
{
    /* 初始化线程1, 名称是static_task, 入口是static_task_entry */
    rt_thread_init(&static_task,
                   "static_task",
                   static_task_entry,
                   RT_NULL,
                   static_task_stack,
                   STATIC_TASK_STACK_SIZE,
                   STATIC_TASK_PRIORITY,
                   STATIC_TASK_TIMESLICE);

    /* 启动线程 */
    rt_thread_startup(&static_task);

    return 0;
}

/* 导出到msh命令列表 */
MSH_CMD_EXPORT(static_task_sample, run static task);

