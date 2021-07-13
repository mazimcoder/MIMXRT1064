#include "fsl_debug_console.h"
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "Globals.h"
#include "GlobalBuffer.h"
#include "edma.h"


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

void Setup_EDMA(void){

	EDMA_GetDefaultConfig(&g_edma_userConfig);
	EDMA_Init(DMA0, &g_edma_userConfig);
	EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0);	//ch 0	mem2mem
	EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);

}

#ifdef FLEXIO3_UART_RX_EDMA

void EDMA_FLEXIO3_UART_RX_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
    	g_FLEXIO3_UART_RX_Transfer_Done = 1;
    }
}

void Setup_EDMA_FLEXIO3_UART(void){

	EDMA_GetDefaultConfig(&g_edma_FLEXIO3_UART_RX_userConfig);
	EDMA_Init(DMA0, &g_edma_FLEXIO3_UART_RX_userConfig);
	EDMA_CreateHandle(&g_EDMA_FLEXIO3_UART_RX_Handle, DMA0, 1);	//ch 1 perh2mem
	EDMA_SetCallback(&g_EDMA_FLEXIO3_UART_RX_Handle, EDMA_FLEXIO3_UART_RX_Callback, NULL);

}


#endif
