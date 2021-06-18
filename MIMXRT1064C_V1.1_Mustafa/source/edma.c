#include "fsl_debug_console.h"
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "Globals.h"
#include "GlobalBuffer.h"



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
