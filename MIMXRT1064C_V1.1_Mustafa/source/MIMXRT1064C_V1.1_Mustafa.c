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

#include "Globals.h"














#include "GlobalBuffer.h"
#include "Tasks.h"
#include "edma.h"






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
