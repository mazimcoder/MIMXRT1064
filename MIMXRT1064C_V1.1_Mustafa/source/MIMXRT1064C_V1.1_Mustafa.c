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
#include "flexio3.h"





int main(void) {
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    SetupFlexio3Clock();

    PRINTF("Program Start Mustafa ::: eDMA mem2mem ::: GlobalBuffer ::: Tasks\n");

    DMAMUX_Init(DMAMUX);
#if defined(FSL_FEATURE_DMAMUX_HAS_A_ON) && FSL_FEATURE_DMAMUX_HAS_A_ON
    DMAMUX_EnableAlwaysOn(DMAMUX, 0, true);
#else
    DMAMUX_SetSource(DMA0, 0, 63);
#endif /* FSL_FEATURE_DMAMUX_HAS_A_ON */
    DMAMUX_EnableChannel(DMAMUX, 0);


    CreatexTasks();

    Setup_EDMA();
    Setup_EDMA_FLEXIO3_UART();

    SetupFlexio3Uart();



	PRINTF("Flexio3 Clock %d \r\n", FLEXIO3_Clock_Frequency);


    vTaskStartScheduler();


//#define configTOTAL_HEAP_SIZE                   ((size_t)(10240))

    volatile static int i = 0 ;
    while(1) {
        i++ ;
        __asm volatile ("nop");
    }
    return 0 ;
}
