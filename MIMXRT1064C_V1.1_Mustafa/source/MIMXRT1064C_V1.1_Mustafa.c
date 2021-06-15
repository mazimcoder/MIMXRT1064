// Mustafa ABDEL AZIM eDMA mem2mem with 3 tasks



#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "task.h"
#include "timers.h"


#ifndef TotalArrayBuff
#define TotalArrayBuff	3
#endif



TaskHandle_t g_Task1Handel;
TaskHandle_t g_Task2Handel;
TaskHandle_t g_Task3Handel;

eTaskState 	g_task1_status;
eTaskState 	g_task2_status;
eTaskState 	g_task3_status;
edma_handle_t g_EDMA_Handle;
edma_transfer_config_t g_EDMA_transfer_Config;
volatile uint8_t g_Transfer_Done = 0;

volatile uint16_t IdxBuf;
char *BufPtr[TotalArrayBuff];
const int32_t BufSize=1024;



void initialize_globalbuf(void)
{
	int cnt =0;
	IdxBuf=TotalArrayBuff;
	do{
		  if(BufPtr[cnt]==NULL){
			  BufPtr[cnt] = (char*)calloc(BufSize,sizeof(char));
			  if(BufPtr[cnt]==NULL)
				  PRINTF("GlobalBufError: %d \r\n",cnt);
		  }
		  else if(BufPtr[cnt]>0){
			  free(BufPtr[cnt]);
			  BufPtr[cnt] = (char*)calloc(BufSize,sizeof(char));
		  }
		  cnt++;
	}while(cnt<IdxBuf);

}

void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done = 1;
    }
}

void EDMA_Transfer(uint16_t srcIdx, uint16_t desIdx)
{
	EDMA_PrepareTransfer(&g_EDMA_transfer_Config,
			BufPtr[srcIdx],
			sizeof(BufPtr[srcIdx][0]),
			BufPtr[desIdx],
			sizeof(BufPtr[srcIdx][0]),
			sizeof(BufPtr[srcIdx][0]),
			strlen(BufPtr[srcIdx]),
			kEDMA_MemoryToMemory
			);
	EDMA_SubmitTransfer(&g_EDMA_Handle, &g_EDMA_transfer_Config);
	EDMA_StartTransfer(&g_EDMA_Handle);

}
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
	for(;;){
		if(g_Transfer_Done ==2){
					PRINTF("Destination Buffer received through Task3 eDMA Mem2Mem:\r\n %s",BufPtr[1]);
					g_Transfer_Done=0;
				}
		vTaskDelay(1000/portTICK_PERIOD_MS);
		vTaskList(BufPtr[2]);
		strcat(BufPtr[2],"============== Task3\r\n");
		PRINTF(BufPtr[2]);
		KeepAlltasksAlive();
	}
}



int main(void) {

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\n");

    DMAMUX_Init(DMAMUX);


#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON
    DMAMUX_EnableAlwaysOn(DMAMUX, 0, true);
#else
    DMAMUX_SetSource(DMA0, 0, 63);
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON */
    DMAMUX_EnableChannel(DMAMUX, 0);




   if(xTaskCreate(Task1,"Task1",1024,NULL,configMAX_PRIORITIES,&g_Task1Handel)!=pdPASS)
	 PRINTF("Task Error Task1\r\n");


   if(xTaskCreate(Task2,"Task2",1024,NULL,configMAX_PRIORITIES-2,&g_Task2Handel)!=pdPASS)
	 PRINTF("Task Error Task2\r\n");

   if(xTaskCreate(Task3,"Task3",1024,NULL,configMAX_PRIORITIES-3,&g_Task3Handel)!=pdPASS)
   	 PRINTF("Task Error Task3\r\n");

   edma_config_t userConfig;

   EDMA_GetDefaultConfig(&userConfig);
   EDMA_Init(DMA0, &userConfig);
   EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0);
   EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);



   g_task1_status = eTaskGetState(g_Task1Handel);
   g_task2_status = eTaskGetState(g_Task2Handel);
   g_task3_status = eTaskGetState(g_Task3Handel);

   vTaskStartScheduler();


//#define configTOTAL_HEAP_SIZE                   ((size_t)(10240))

    volatile static int i = 0 ;
    while(1) {
        i++ ;
        __asm volatile ("nop");
    }
    return 0 ;
}
