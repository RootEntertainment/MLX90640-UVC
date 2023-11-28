/**
  **************************************************************************
  * @file     cdc_desc.h
  * @version  v2.0.7
  * @date     2022-04-02
  * @brief    usb cdc descriptor header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __CDC_DESC_H
#define __CDC_DESC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "video_class.h"
#include "usbd_core.h"

/** @addtogroup AT32F435_437_middlewares_usbd_class
  * @{
  */

/** @addtogroup USB_cdc_desc
  * @{
  */

/** @defgroup USB_cdc_desc_definition
  * @{
  */
/**
  * @brief usb bcd number define
  */
#define CDC_BCD_NUM                      0x0110

/**
  * @brief usb vendor id and product id define
  */
#define USBD_VIDEO_VENDOR_ID               0x2E3C
#define USBD_VIDEO_PRODUCT_ID              0x5765

/**
  * @brief usb descriptor size define
  */
#define USBD_VIDEO_CONFIG_DESC_SIZE        159
#define USBD_VIDEO_SIZ_STRING_LANGID       4
#define USBD_VIDEO_SIZ_STRING_SERIAL       26
#define USBD_IDX_INTERFACE_STR 				 0x02

#define USB_ASSOCIATION_DESCRIPTOR_TYPE	 0x0B
#define MAKE_WORD(x)        (u8)((x)&0xFF),(u8)(((x)>>8)&0xFF)
#define MAKE_DWORD(x)       (u8)((x)&0xFF),(u8)(((x)>>8)&0xFF),(u8)(((x)>>16)&0xFF),(u8)(((x)>>24)&0xFF)


/**
  * @brief usb string define(vendor, product configuration, interface)
  */
#define USBD_VIDEO_DESC_MANUFACTURER_STRING    "Artery"
#define USBD_VIDEO_DESC_PRODUCT_STRING         "ATvideo"
#define USBD_VIDEO_DESC_CONFIGURATION_STRING   "Virtual video Config"
#define USBD_VIDEO_DESC_INTERFACE_STRING       "Virtual video Interface"

/**
  * @brief usb endpoint interval define
  */
#define CDC_HID_BINTERVAL_TIME                0xFF

/**
  * @brief usb mcu id address deine
  */
#define         MCU_ID1                   (0x1FFFF7E8)
#define         MCU_ID2                   (0x1FFFF7EC)
#define         MCU_ID3                   (0x1FFFF7F0)
/**
  * @}
  */
 
extern usbd_desc_handler video_desc_handler;


/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif
