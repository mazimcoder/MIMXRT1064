

#ifndef EDMA_H_
#define EDMA_H_


void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

void EDMA_Transfer(uint16_t srcIdx, uint16_t desIdx);

void Setup_EDMA(void);


#ifdef FLEXIO3_UART_RX_EDMA

void EDMA_FLEXIO3_UART_RX_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

void Setup_EDMA_FLEXIO3_UART(void);

#endif


#endif /* EDMA_H_ */
