
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

#include "peripherals.h"

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_msc.h"
//#include "usb_device_ch9.h"
#include "usb_device_descriptor.h"
#include "disk.h"

#include "usb_disk_adapter.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "board.h"

#if (defined(FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT > 0U))
#include "fsl_sysmpu.h"
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
#include "usb_phy.h"
#endif

#include "sdmmc_config.h"

void USB_task(void *pv){


	USB_DeviceApplicationInit();


    while (1){
#if USB_DEVICE_CONFIG_USE_TASK
        USB_DeviceTaskFn(g_msc_access().deviceHandle);
#endif
        USB_DeviceMscAppTask();
#if (defined(USB_DEVICE_CONFIG_USE_TASK) && (USB_DEVICE_CONFIG_USE_TASK > 0)) && \
    (defined(USB_DEVICE_MSC_USE_WRITE_TASK) && (USB_DEVICE_MSC_USE_WRITE_TASK > 0))
        USB_DeviceMscWriteTask();
#endif
    }

}

int main(void) {

//    BOARD_ConfigMPU();
//    BOARD_InitBootPins();
//    BOARD_InitBootClocks();
//    BOARD_InitBootPeripherals();
//#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
//    BOARD_InitDebugConsole();
//#endif
//
//    PRINTF("Hello World\n");
//
//    /* Force the counter to be placed into memory. */
//    volatile static int i = 0 ;
//    /* Enter an infinite loop, just incrementing a counter. */
//    while(1) {
//        i++ ;
//        /* 'Dummy' NOP to allow source level single stepping of
//            tight while() loop */
//        __asm volatile ("nop");
//    }
//    return 0 ;



	BOARD_ConfigMPU();

	    BOARD_InitPins();
	    BOARD_BootClockRUN();
	    BOARD_USB_Disk_Config(USB_DEVICE_INTERRUPT_PRIORITY);
	    BOARD_InitDebugConsole();

	    USB_DeviceClockInit();

	    if(pdPASS != xTaskCreate(USB_task, "USB Task",4096, NULL, configMAX_PRIORITIES -3, NULL))
	    	PRINTF("Error  xTaskCreate USB_task \r\n");


	    vTaskStartScheduler();
	    while(1){


	    }

}
