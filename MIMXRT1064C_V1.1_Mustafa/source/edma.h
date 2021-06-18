

#ifndef EDMA_H_
#define EDMA_H_


void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);


void EDMA_Transfer(uint16_t srcIdx, uint16_t desIdx);

#endif /* EDMA_H_ */
