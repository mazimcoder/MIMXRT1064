/*
 * RTOSTask.cpp
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
#include "RTOSTask.hpp"


#ifdef __cplusplus
extern "C" {
#endif





#ifdef __cplusplus
}
#endif






TaskManager::TaskManager(TaskFunction_t taskmethod,char* name, uint16_t stacksize,uint16_t priority, void* pv){

	taskCreate(taskmethod,name,stacksize,priority,pv);

};

void TaskManager::taskCreate(TaskFunction_t _taskmethod,char* _name, uint16_t _stacksize,uint16_t _priority, void* _pv){

	if(xTaskCreate(_taskmethod,_name,_stacksize,NULL,3,&handel)!=pdPASS)
			 std::printf("Error: %s TaskManager::taskCreate\r\n",_name);
};


void TaskManager::taskDelete(void){

	vTaskDelete(handel);
};


eTaskState TaskManager::status(void){

	lastStatus = eTaskGetState(handel);
	return lastStatus;
};

void TaskManager::changePriority(uint16_t priority){

	vTaskPrioritySet(handel,priority);

};

void TaskManager::suspend(void){

	vTaskSuspend(handel);
};


BaseType_t TaskManager::resume(bool fromISR){

	if(fromISR)
		return xTaskResumeFromISR(handel);
	else
		vTaskResume(handel);
};
