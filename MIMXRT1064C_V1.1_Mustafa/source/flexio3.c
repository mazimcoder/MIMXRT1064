#include <stdlib.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "Globals.h"
#include "GlobalBuffer.h"
#include "edma.h"
#include "flexio3.h"


uint8_t Flexio3_RingBuffer[Flexio3_RingBufferArraySize];
uint8_t Flexio3_RxBuffer[Flexio3_RingBufferArraySize];
flexio_uart_transfer_t Flexio3_TxXref;
flexio_uart_transfer_t Flexio3_RxXref;


void Flexio3_UART_Callback(FLEXIO_UART_Type *base,
							flexio_uart_handle_t *handle,
							status_t status,
							void *userData){
userData = userData;

	if(kStatus_FLEXIO_UART_TxIdle == status)
		g_uartflexio3_TxOnGoing=true;
	else if(kStatus_FLEXIO_UART_RxIdle == status)
		g_uartflexio3_RxOnGoing=true;
	else
		g_uartflexio3_error =status;


}
void SetupFlexio3Clock(void){	// currently not used since I intialize the clock

	CLOCK_SetMux(kCLOCK_Flexio2Mux, FLEXIO2_CLK_SEL);	//	set CCM CSCMR2  FLEXIO2_CLK_SEL P.1057
	CLOCK_SetDiv(kCLOCK_Flexio2PreDiv, FLEXIO2_CLK_PRED);	// set divider node CS1CDR >> LEXIO2_CLK_PRED
	CLOCK_SetDiv(kCLOCK_Flexio2Div, FLEXIO2_CLK_PODF);	// set divider node CS1CDR >> FLEXIO2_CLK_PODF

}



void SetupFlexio3Uart(void){

	g_uartflexio3_type.flexioBase = FLEXIO3;
	g_uartflexio3_type.shifterIndex[0]=0;
	g_uartflexio3_type.shifterIndex[1]=1;
	g_uartflexio3_type.timerIndex[0]=0;
	g_uartflexio3_type.timerIndex[1]=1;
	g_uartflexio3_type.TxPinIndex = FLEXIO3_UART_TX_Pin;
	g_uartflexio3_type.RxPinIndex = FLEXIO3_UART_RX_Pin;
	status_t result= -1;

	FLEXIO_UART_GetDefaultConfig(&g_uartflexio3_config);
	g_uartflexio3_config.baudRate_Bps = FLEXIO3_UART_Baud_Rate;
	g_uartflexio3_config.enableUart	= true;

	result = FLEXIO_UART_Init(&g_uartflexio3_type, &g_uartflexio3_config, FLEXIO3_Clock_Frequency);
	if(result != kStatus_Success){
		PRINTF("Error FLEXIO_UART_Init() %d\r\n",(uint8_t)kStatus_Success);
		return;
	}

	FLEXIO_UART_TransferCreateHandle(&g_uartflexio3_type,
									&g_uartflexio3_Handle,
									Flexio3_UART_Callback,
									NULL);
	FLEXIO_UART_TransferStartRingBuffer(&g_uartflexio3_type,
										&g_uartflexio3_Handle,
										Flexio3_RingBuffer,
										Flexio3_RingBufferArraySize);
}

status_t Flexio3UartSend(uint8_t txdata[]){

	status_t r =-1;
	Flexio3_TxXref.data=txdata;
	Flexio3_TxXref.dataSize= strlen(txdata);
	if((Flexio3_TxXref.dataSize-1)<=Flexio3_RingBufferArraySize){
		r = FLEXIO_UART_TransferSendNonBlocking(&g_uartflexio3_type,
												&g_uartflexio3_Handle,
												&Flexio3_TxXref);
		return r;
	}
	else
		PRINTF("Flexio3_TxXref.dataSize %d > %d",Flexio3_TxXref.dataSize,Flexio3_RingBufferArraySize);
	return -1;
}

status_t SetupFlexio3UartReceive(void){

	status_t r =-1;
	Flexio3_RxXref.data = Flexio3_RxBuffer;
	Flexio3_RxXref.dataSize = Flexio3_RingBufferArraySize;
	r = FLEXIO_UART_TransferReceiveNonBlocking(&g_uartflexio3_type,
											   &g_uartflexio3_Handle,
											   &Flexio3_RxXref,
											   (size_t)Flexio3_RingBufferArraySize);
	return r;

}


