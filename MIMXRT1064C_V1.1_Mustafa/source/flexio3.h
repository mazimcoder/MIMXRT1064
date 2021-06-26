
#define Flexio3_RingBufferArraySize 16
#ifndef FLEXIO3_H_
#define FLEXIO3_H_

extern uint8_t Flexio3_RingBuffer[];
extern uint8_t Flexio3_RxBuffer[];
extern flexio_uart_transfer_t Flexio3_TxXref;
extern flexio_uart_transfer_t Flexio3_RxXref;

void Flexio3_UART_Callback(FLEXIO_UART_Type *base,flexio_uart_handle_t *handle,status_t status,void *userData);

void SetupFlexio3Clock(void);

void SetupFlexio3Uart(void);

status_t Flexio3UartSend(uint8_t txdata[]);
status_t SetupFlexio3UartReceive(void);

#endif /* FLEXIO3_H_ */
