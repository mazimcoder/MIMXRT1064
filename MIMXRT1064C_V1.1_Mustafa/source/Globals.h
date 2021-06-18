
#include <stdint.h>
#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#ifndef GLOBALS_H_
#define GLOBALS_H_



extern char *BufPtr[3];

extern const int32_t BufSize;

extern volatile uint16_t IdxBuf;

extern volatile uint8_t g_Transfer_Done;


extern TaskHandle_t g_Task1Handel;
extern TaskHandle_t g_Task2Handel;
extern TaskHandle_t g_Task3Handel;

extern eTaskState 	g_task1_status;
extern eTaskState 	g_task2_status;
extern eTaskState 	g_task3_status;
extern edma_handle_t g_EDMA_Handle;
extern edma_transfer_config_t g_EDMA_transfer_Config;




#endif /* GLOBALS_H_ */
