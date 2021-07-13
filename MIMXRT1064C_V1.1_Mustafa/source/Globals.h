
#ifndef globalbufferArrayCapacity
#define globalbufferArrayCapacity 3
#endif


#define FLEXIO3_UART_RX_EDMA
#define FLEXIO2_CLK_SEL 3U
#define FLEXIO2_CLK_PRED 1U
#define FLEXIO2_CLK_PODF 4U
#define FLEXIO3_Clock_Frequency \
	(CLOCK_GetFreq(kCLOCK_Usb1PllClk) / (FLEXIO2_CLK_PRED + 1U) / (FLEXIO2_CLK_PODF + 1U))
#define FLEXIO3_UART_TX_Pin 3U
#define FLEXIO3_UART_RX_Pin 2U
#define FLEXIO3_UART_Baud_Rate 115200



#include <stdint.h>
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "fsl_flexio_uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#ifndef GLOBALS_H_
#define GLOBALS_H_



// Global buffer
extern char *BufPtr[globalbufferArrayCapacity];
extern const int32_t BufSize;
extern volatile uint16_t IdxBuf;



// eDMA	mem2mem
extern volatile uint8_t 		g_Transfer_Done;
extern edma_handle_t 			g_EDMA_Handle;
extern edma_transfer_config_t 	g_EDMA_transfer_Config;
extern edma_config_t 			g_edma_userConfig;

// Tasks
extern TaskHandle_t g_Task1Handel;
extern TaskHandle_t g_Task2Handel;
extern TaskHandle_t g_Task3Handel;
extern eTaskState 	g_task1_status;
extern eTaskState 	g_task2_status;
extern eTaskState 	g_task3_status;


extern flexio_uart_handle_t g_uartflexio3_Handle;	//Transactional layer
extern flexio_uart_config_t g_uartflexio3_config;
extern FLEXIO_UART_Type g_uartflexio3_type;
extern volatile bool g_uartflexio3_TxOnGoing;
extern volatile bool g_uartflexio3_RxOnGoing;
extern volatile status_t g_uartflexio3_error;
#ifdef FLEXIO3_UART_RX_EDMA
extern edma_handle_t g_EDMA_FLEXIO3_UART_RX_Handle;
extern edma_transfer_config_t g_EDMA_FLEXIO3_UART_RX_transfer_Config;
extern edma_config_t g_edma_FLEXIO3_UART_RX_userConfig;
extern volatile uint8_t g_FLEXIO3_UART_RX_Transfer_Done;

#endif



#endif /* GLOBALS_H_ */
