


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"
#include "/usr/local/include/cjson/cJSON.h"
#include "RTOSTask.hpp"
#include "Globals.hpp"


TaskHandle_t g_Task1Handel;

GlobalBuf* buf;

cJSON *root;
cJSON *info;



int main(void) {


    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL

    BOARD_InitDebugConsole();
#endif

    //PRINTF("Hello World\r\n");
    //root = cJSON_CreateObject();

    //cJSON_AddItemToObject(root,"UserInfo",info = cJSON_CreateObject());
    //cJSON_AddStringToObject(info, "userEmail", "m@info.com");
    //cJSON_AddStringToObject(info, "phone", "01234567");



    buf= new GlobalBuf(15);


    char* ptr = (char*)buf->access();

    strcpy(ptr,"0123456789");

    std::cout<<ptr<<std::endl;

    buf->reinitialize(15);

    std::cout<<ptr<<std::endl;

    volatile static int i = 0 ;

    while(1) {
        i++ ;

        __asm volatile ("nop");
    }
    return 0 ;
}
