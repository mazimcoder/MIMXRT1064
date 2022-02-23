/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_DISK_ADAPTER_H__
#define __USB_DISK_ADAPTER_H__

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define USB_DEVICE_DISK_BLOCK_SIZE_POWER (9U)
/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief disk configration function.
 *
 * This function configure the disk.
 */
extern void BOARD_USB_Disk_Config(uint32_t usbPriorty);

/*!
 * @brief device msc disk init function.
 *
 * This function initialize the disk.
 * @return kStatus_USB_Success or error.
 */
extern uint8_t USB_DeviceMscDiskStorageInit(void);

/*!
 * @brief Writes data blocks to the disk.
 *
 */
extern status_t USB_Disk_WriteBlocks(const uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief read data blocks from the disk.
 *
 */
extern status_t USB_Disk_ReadBlocks(uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief get block size.
 *
 */
extern uint32_t USB_Disk_GetBlockSize();

/*!
 * @brief get block count.
 *
 */
extern uint32_t USB_Disk_GetBlockCount();



#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __USB_DISK_ADAPTER_H__ */
