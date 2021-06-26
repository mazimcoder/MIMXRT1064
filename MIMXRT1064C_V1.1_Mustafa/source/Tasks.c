


#include "fsl_debug_console.h"
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "Globals.h"
#include "GlobalBuffer.h"
#include "Tasks.h"
#include "edma.h"
#include "flexio3.h"

void KeepAlltasksAlive(void){
	g_task1_status = eTaskGetState(g_Task1Handel);
	g_task2_status = eTaskGetState(g_Task2Handel);
	g_task3_status = eTaskGetState(g_Task3Handel);
	if(g_task1_status !=eRunning)
		vTaskResume(g_Task1Handel);
	if(g_task2_status !=eRunning)
		vTaskResume(g_Task2Handel);
	if(g_task3_status !=eRunning)
		vTaskResume(g_Task3Handel);
}

void Task1 (void *pVparameter){
	//g_task1_status = eTaskGetState(g_Task1Handel);
	//g_task2_status = eTaskGetState(g_Task2Handel);
	PRINTF("Task1 running!\n");
	initialize_globalbuf();
	vTaskDelay(10/portTICK_PERIOD_MS);
	BufPtr[0]="This is a simple data of 256 bytes";
	//vTaskSuspend(g_Task1Handel);
	EDMA_Transfer(0,1);
	//PRINTF("EDMA_Transfer!\n");

	for(;;){
		//PRINTF("Task 1 loop counter %d",x);
		if(g_Transfer_Done==1)
			g_Transfer_Done=2;
		vTaskDelay(1000/portTICK_PERIOD_MS);
		vTaskList(BufPtr[2]);
		strcat(BufPtr[2],"============== Task1\r\n");
		PRINTF(BufPtr[2]);
		KeepAlltasksAlive();
	}
}

void Task2 (void *pVparameter){
	//g_task1_status = eTaskGetState(g_Task1Handel);
	//g_task2_status = eTaskGetState(g_Task2Handel);
	PRINTF("Task2 running!\n");
	vTaskDelay(20/portTICK_PERIOD_MS);
	for(;;){

		if(g_Transfer_Done ==2){
			PRINTF("Destination Buffer received through Task 2 eDMA Mem2Mem:\r\n %s",BufPtr[1]);
			g_Transfer_Done=0;
		}
		vTaskDelay(1000/portTICK_PERIOD_MS);
		vTaskList(BufPtr[2]);
		strcat(BufPtr[2],"============== Task2\r\n");
		PRINTF(BufPtr[2]);
		KeepAlltasksAlive();
	}
}



void Task3(void *pVparameter){
	PRINTF("Task3 running!\n");
	vTaskDelay(30/portTICK_PERIOD_MS);
	status_t r = -1;
	if(!g_uartflexio3_TxOnGoing)
		r = Flexio3UartSend("Serial 115200\r\n");


	for(;;){
		if(g_Transfer_Done ==2){
					PRINTF("Destination Buffer received through Task3 eDMA Mem2Mem:\r\n %s",BufPtr[1]);
					g_Transfer_Done=0;
				}
		//vTaskDelay(1000/portTICK_PERIOD_MS);
		//vTaskList(BufPtr[2]);
		//strcat(BufPtr[2],"============== Task3\r\n");
		//PRINTF(BufPtr[2]);


		if(g_uartflexio3_TxOnGoing)
			g_uartflexio3_TxOnGoing=false;


		r = SetupFlexio3UartReceive();
		if(g_uartflexio3_RxOnGoing || g_uartflexio3_error!=-1){
			g_uartflexio3_RxOnGoing=false;
			if(!g_uartflexio3_TxOnGoing)
					r = Flexio3UartSend(Flexio3_RxBuffer);

			//(void)memset(&Flexio3_RxBuffer,0,10);
//			for(uint16_t i =0; i<Flexio3_RingBufferArraySize;i++){
//				Flexio3_RxBuffer[i]=0;
//			}
		}

		if(g_uartflexio3_error!=-1){
			PRINTF("ERROR g_uartflexio3_error = %d",g_uartflexio3_error);
			g_uartflexio3_error=-1;
		}

		KeepAlltasksAlive();
	}
}


void CreatexTasks(void){

	if(xTaskCreate(Task1,"Task1",1024,NULL,configMAX_PRIORITIES,&g_Task1Handel)!=pdPASS)
	 PRINTF("Task Error Task1\r\n");


	if(xTaskCreate(Task2,"Task2",1024,NULL,configMAX_PRIORITIES-2,&g_Task2Handel)!=pdPASS)
	 PRINTF("Task Error Task2\r\n");

	if(xTaskCreate(Task3,"Task3",1024,NULL,configMAX_PRIORITIES-3,&g_Task3Handel)!=pdPASS)
	 PRINTF("Task Error Task3\r\n");

	g_task1_status = eTaskGetState(g_Task1Handel);
	g_task2_status = eTaskGetState(g_Task2Handel);
	g_task3_status = eTaskGetState(g_Task3Handel);
}
