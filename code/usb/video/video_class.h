/**
  **************************************************************************
  * @file     cdc_class.h
  * @version  v2.0.7
  * @date     2022-04-02
  * @brief    usb cdc class file
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
#ifndef __CDC_CLASS_H
#define __CDC_CLASS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb_std.h"
#include "usbd_core.h"
#include "jpegbuff.h"

/** @addtogroup AT32F435_437_middlewares_usbd_class
  * @{
  */

/** @addtogroup USB_cdc_class
  * @{
  */

/** @defgroup USB_cdc_class_definition
  * @{
  */

/**
  * @brief usb cdc use endpoint define
  */
#define USBD_VIDEO_ISO_IN_EPT             0x81

/**
  * @brief usb cdc in and out max packet size define
  */
#ifdef IMG1
#define USBD_ISO_IN_MAXPACKET_SIZE        520
#define IMG_WIDTH 285
#define IMG_HEIGHT 344
#define IMG_FRAME 40
#endif

#ifdef IMG2
#define USBD_ISO_IN_MAXPACKET_SIZE        159
#define IMG_WIDTH 128
#define IMG_HEIGHT 160
#define IMG_FRAME 15
#endif
/*
#ifdef IMG3
#define USBD_ISO_IN_MAXPACKET_SIZE        520
#define IMG_WIDTH 320
#define IMG_HEIGHT 240
#define IMG_FRAME 7
#endif
*/

#ifdef IMG4
#define USBD_ISO_IN_MAXPACKET_SIZE        520
#define IMG_WIDTH 320
#define IMG_HEIGHT 240
#define IMG_FRAME 20
#endif

#ifdef IMG5
#define USBD_ISO_IN_MAXPACKET_SIZE        520
#define IMG_WIDTH 320
#define IMG_HEIGHT 240
#define IMG_FRAME (uint8_t)(((uint32_t)(1000*USBD_ISO_IN_MAXPACKET_SIZE))/((uint32_t)JPEG_SIZE1))
#endif

/*
#ifdef IMG6
#define USBD_ISO_IN_MAXPACKET_SIZE        ((uint16_t)((IMG_FRAME*(uint32_t)JPEG_SIZE1)/1000))//520
#define IMG_WIDTH 320
#define IMG_HEIGHT 240
#define IMG_FRAME 20//(uint8_t)(1000/((uint32_t)JPEG_SIZE1/USBD_ISO_IN_MAXPACKET_SIZE))
#endif

#ifdef IMG7
#define USBD_ISO_IN_MAXPACKET_SIZE        ((uint16_t)((IMG_FRAME*(uint32_t)JPEG_SIZE1)/1000))
#define IMG_WIDTH 320
#define IMG_HEIGHT 240
#define IMG_FRAME 10
#endif
*/

#define USBD_ISO_IN_MAXPACKET_SIZE        256
#define IMG_WIDTH 160
#define IMG_HEIGHT 120
#define IMG_FRAME 16


#define MAX_BITRATE IMG_WIDTH*IMG_HEIGHT*16*IMG_FRAME
#define MIN_BITRATE IMG_WIDTH*IMG_HEIGHT*16*IMG_FRAME
#define FRAME_BUFFER_SIZE JPEG_BUFFSIZE*2//IMG_WIDTH*IMG_HEIGHT*2
#define FRAME_INTERVAL (unsigned long)10000000/IMG_FRAME

/*
#define UVC_SET_CUR						 			0x01
#define UVC_GET_CUR						 			0x81
#define VS_PROBE_CONTROL				 			0x01
#define VS_COMMIT_CONTROL				 			0x02

#define UVC_GET_MIN						 			0x82
#define UVC_GET_MAX						 			0x83
#define UVC_GET_RES						 			0x84
#define UVC_GET_LEN						 			0x85
#define UVC_GET_INFO					 			0x86
#define UVC_GET_DEF						 			0x87

*/


/*---------------------------------------------------------------------*/
/*  UVC definitions                                                    */
/*---------------------------------------------------------------------*/
/* Video Class-Specific Descriptor Types */
#define CS_UNDEFINED  								0x20
#define CS_DEVICE  									0x21
#define CS_CONFIGURATION  							0x22
#define CS_STRING  									0x23
#define CS_INTERFACE 	 							0x24
#define CS_ENDPOINT  								0x25

#define UVC_RC_UNDEFINED				 			0x00
#define UVC_SET_CUR						 			0x01
#define UVC_SET_CUR_ALL					 			0x11
#define UVC_GET_CUR						 			0x81
#define UVC_GET_MIN						 			0x82
#define UVC_GET_MAX						 			0x83
#define UVC_GET_RES						 			0x84
#define UVC_GET_LEN						 			0x85
#define UVC_GET_INFO					 			0x86
#define UVC_GET_DEF						 			0x87
#define UVC_GET_CUR_ALL					 			0x91
#define UVC_GET_MIN_ALL					 			0x92
#define UVC_GET_MAX_ALL					 			0x93
#define UVC_GET_RES_ALL					 			0x94
#define UVC_GET_DEF_ALL					 			0x97

/* VideoControl Interface Control Selectors */
#define VC_CONTROL_UNDEFINED  						0x00
#define VC_VIDEO_POWER_MODE_CONTROL  				0x01
#define VC_REQUEST_ERROR_CODE_CONTROL  				0x02

/* Terminal Control Selectors */
#define TE_CONTROL_UNDEFINED  						0x00

/* Camera Terminal Control Selectors */
#define CT_CONTROL_UNDEFINED  						0x00
#define CT_SCANNING_MODE_CONTROL  					0x01
#define CT_AE_MODE_CONTROL  						0x02
#define CT_AE_PRIORITY_CONTROL  					0x03
#define CT_EXPOSURE_TIME_ABSOLUTE_CONTROL 			0x04
#define CT_EXPOSURE_TIME_RELATIVE_CONTROL  			0x05
#define CT_FOCUS_ABSOLUTE_CONTROL  					0x06
#define CT_FOCUS_RELATIVE_CONTROL  					0x07
#define CT_FOCUS_AUTO_CONTROL  						0x08
#define CT_IRIS_ABSOLUTE_CONTROL  					0x09
#define CT_IRIS_RELATIVE_CONTROL  					0x0A
#define CT_ZOOM_ABSOLUTE_CONTROL  					0x0B
#define CT_ZOOM_RELATIVE_CONTROL  					0x0C
#define CT_PANTILT_ABSOLUTE_CONTROL  				0x0D
#define CT_PANTILT_RELATIVE_CONTROL  				0x0E
#define CT_ROLL_ABSOLUTE_CONTROL  					0x0F
#define CT_ROLL_RELATIVE_CONTROL  					0x10
#define CT_PRIVACY_CONTROL 	 						0x11
#define CT_FOCUS_SIMPLE_CONTROL  					0x12
#define CT_WINDOW_CONTROL  							0x13
#define CT_REGION_OF_INTEREST_CONTROL  				0x14

/* Selector Unit Control Selectors */
#define SU_CONTROL_UNDEFINED  						0x00
#define SU_INPUT_SELECT_CONTROL  					0x01

/* Processing Unit Control Selectors */
#define PU_CONTROL_UNDEFINED  			 			0x00
#define PU_BACKLIGHT_COMPENSATION_CONTROL 			0x01
#define PU_BRIGHTNESS_CONTROL  						0x02
#define PU_CONTRAST_CONTROL  						0x03
#define PU_GAIN_CONTROL  							0x04
#define PU_POWER_LINE_FREQUENCY_CONTROL			  	0x05
#define PU_HUE_CONTROL  							0x06
#define PU_SATURATION_CONTROL  						0x07
#define PU_SHARPNESS_CONTROL  						0x08
#define PU_GAMMA_CONTROL  							0x09
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL  		0x0A
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL 	0x0B
#define PU_WHITE_BALANCE_COMPONENT_CONTROL  		0x0C
#define PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL  	0x0D
#define PU_DIGITAL_MULTIPLIER_CONTROL  				0x0E
#define PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL  		0x0F
#define PU_HUE_AUTO_CONTROL  						0x10
#define PU_ANALOG_VIDEO_STANDARD_CONTROL  			0x11
#define PU_ANALOG_LOCK_STATUS_CONTROL  				0x12
#define PU_CONTRAST_AUTO_CONTROL  					0x13

/* Encoding Unit Control Selectors */
#define EU_CONTROL_UNDEFINED  			 			0x00
#define EU_SELECT_LAYER_CONTROL  		 			0x01
#define EU_PROFILE_TOOLSET_CONTROL  	 			0x02
#define EU_VIDEO_RESOLUTION_CONTROL  	 			0x03
#define EU_MIN_FRAME_INTERVAL_CONTROL  	 			0x04
#define EU_SLICE_MODE_CONTROL  			 			0x05
#define EU_RATE_CONTROL_MODE_CONTROL  	 			0x06
#define EU_AVERAGE_BITRATE_CONTROL 		 			0x07
#define EU_CPB_SIZE_CONTROL  			 			0x08
#define EU_PEAK_BIT_RATE_CONTROL  		 			0x09
#define EU_QUANTIZATION_PARAMS_CONTROL   			0x0A
#define EU_SYNC_REF_FRAME_CONTROL  		 			0x0B
#define EU_LTR_BUFFER_CONTROL 			 			0x0C
#define EU_LTR_PICTURE_CONTROL 			 			0x0D
#define EU_LTR_VALIDATION_CONTROL 		 			0x0E
#define EU_LEVEL_IDC_LIMIT_CONTROL  	 			0x0F
#define EU_SEI_PAYLOADTYPE_CONTROL  	 			0x10
#define EU_QP_RANGE_CONTROL  			 			0x11
#define EU_PRIORITY_CONTROL  			 			0x12
#define EU_START_OR_STOP_LAYER_CONTROL   			0x13
#define EU_ERROR_RESILIENCY_CONTROL  	 			0x14

/* Extension Unit Control Selectors */
#define XU_CONTROL_UNDEFINED			 			0x00

/* VideoStreaming Interface Control Selectors */
#define VS_CONTROL_UNDEFINED			 			0x00
#define VS_PROBE_CONTROL				 			0x01
#define VS_COMMIT_CONTROL				 			0x02
#define VS_STILL_PROBE_CONTROL			 			0x03
#define VS_STILL_COMMIT_CONTROL			 			0x04
#define VS_STILL_IMAGE_TRIGGER_CONTROL   			0x05
#define VS_STREAM_ERROR_CODE_CONTROL	 			0x06
#define VS_GENERATE_KEY_FRAME_CONTROL	 			0x07
#define VS_UPDATE_FRAME_SEGMENT_CONTROL	 			0x08
#define VS_SYNCH_DELAY_CONTROL			 			0x09


#define PLAY_STATUS_STOP							0
#define PLAY_STATUS_READY							1
#define PLAY_STATUS_STREAMING						2

/**
  * @}
  */

/** @defgroup USB_cdc_class_exported_types
  * @{
  */

/**
  * @brief usb cdc class struct
  */
  
typedef struct
{
   uint8_t cmd;   
   uint8_t data[USB_MAX_EP0_SIZE];  
   uint8_t len;  
   uint8_t unit;    
}USBD_UVC_ControlType; 


typedef struct
{
  uint8_t 				alt_setting;
  __IO uint8_t 	  tx_state;
  uint8_t 				*tx_ptr;
	uint32_t 				tx_length;
  USBD_UVC_ControlType control;

}video_struct_type;


/**
  * @}
  */

/** @defgroup USB_cdc_class_exported_functions
  * @{
  */
extern usbd_class_handler video_class_handler;

/**
  * @}
  */

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




