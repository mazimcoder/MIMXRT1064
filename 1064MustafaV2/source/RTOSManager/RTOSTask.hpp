/*
 * RTOSTask.hpp
 *
 *  Created on: 24 Jun 2021
 *      Author: mustafaabdelazim
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"


#ifndef RTOSMANAGER_RTOSTASK_HPP_
#define RTOSMANAGER_RTOSTASK_HPP_




#ifdef __cplusplus
extern "C" {
#endif


extern void taskMethod1(void* pv);






#ifdef __cplusplus
}
#endif



class TaskManager{

public:	TaskHandle_t handel;
public: eTaskState lastStatus;


public: TaskManager(TaskFunction_t taskmethod,char* name, uint16_t stacksize,uint16_t priority, void* pv);

public: void taskCreate(TaskFunction_t taskmethod,char* _name, uint16_t _stacksize,uint16_t _priority, void* _pv);

public: void taskDelete(void);

public: eTaskState status(void);

public: void changePriority(uint16_t priority);

public: void suspend(void);

public: BaseType_t resume(bool fromISR);


};



#endif /* RTOSMANAGER_RTOSTASK_HPP_ */
