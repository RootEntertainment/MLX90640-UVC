/**
  **************************************************************************
  * @file     cdc_desc.c
  * @version  v2.0.7
  * @date     2022-04-02
  * @brief    usb cdc device descriptor
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
#include "stdio.h"
#include "usb_std.h"
#include "usbd_sdr.h"
#include "usbd_core.h"
#include "video_desc.h"
#include "video_class.h"

/** @addtogroup AT32F435_437_middlewares_usbd_class
  * @{
  */

/** @defgroup USB_cdc_desc
  * @brief usb device cdc descriptor
  * @{
  */

/** @defgroup USB_cdc_desc_private_functions
  * @{
  */

static usbd_desc_t *get_device_descriptor(void);
static usbd_desc_t *get_device_qualifier(void);
static usbd_desc_t *get_device_configuration(void);
static usbd_desc_t *get_device_other_speed(void);
static usbd_desc_t *get_device_lang_id(void);
static usbd_desc_t *get_device_manufacturer_string(void);
static usbd_desc_t *get_device_product_string(void);
static usbd_desc_t *get_device_serial_string(void);
static usbd_desc_t *get_device_interface_string(void);
static usbd_desc_t *get_device_config_string(void);

static uint16_t usbd_unicode_convert(uint8_t *string, uint8_t *unicode_buf);
static void usbd_int_to_unicode (uint32_t value , uint8_t *pbuf , uint8_t len);
static void get_serial_num(void);
static uint8_t g_usbd_desc_buffer[256];

/**
  * @brief device descriptor handler structure
  */
usbd_desc_handler video_desc_handler =
{
  get_device_descriptor,
  get_device_qualifier,
  get_device_configuration,
  get_device_other_speed,
  get_device_lang_id,
  get_device_manufacturer_string,
  get_device_product_string,
  get_device_serial_string,
  get_device_interface_string,
  get_device_config_string,
};

/**
  * @brief usb device standard descriptor
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
ALIGNED_HEAD static uint8_t g_usbd_descriptor[USB_DEVICE_DESC_LEN] ALIGNED_TAIL =
{
  USB_DEVICE_DESC_LEN,                   /* bLength */
  USB_DESCIPTOR_TYPE_DEVICE,             /* bDescriptorType */
  0x00,                                  /* bcdUSB */
  0x02,
  0xEF,                                  /* miscellaneous device class */
  0x02,                                  /* bDeviceSubClass : common class */
  0x01,                                  /* bDeviceProtocol : interface association descripter*/
  USB_MAX_EP0_SIZE,                      /* bMaxPacketSize */
  LBYTE(USBD_VIDEO_VENDOR_ID),             /* idVendor */
  HBYTE(USBD_VIDEO_VENDOR_ID),             /* idVendor */
  LBYTE(USBD_VIDEO_PRODUCT_ID),            /* idProduct */
  HBYTE(USBD_VIDEO_PRODUCT_ID),            /* idProduct */
  0x00,                                  /* bcdDevice rel. 2.00 */
  0x01,
  USB_MFC_STRING,                        /* Index of manufacturer string */
  USB_PRODUCT_STRING,                    /* Index of product string */
  USB_SERIAL_STRING,                     /* Index of serial number string */
  1                                      /* bNumConfigurations */
};

/**
  * @brief usb configuration standard descriptor
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
ALIGNED_HEAD static uint8_t g_usbd_configuration[USBD_VIDEO_CONFIG_DESC_SIZE] ALIGNED_TAIL =
{
	/*emmmm no*/
	
//	USB_DEVICE_CFG_DESC_LEN,               /* bLength: configuration descriptor size */
//  USB_DESCIPTOR_TYPE_CONFIGURATION,      /* bDescriptorType: configuration */
//  LBYTE(USBD_VIDEO_CONFIG_DESC_SIZE),      /* wTotalLength: bytes returned */
//  HBYTE(USBD_VIDEO_CONFIG_DESC_SIZE),      /* wTotalLength: bytes returned */
//  0x02,                                  /* bNumInterfaces: 2 interface */
//  0x01,                                  /* bConfigurationValue: configuration value */
//  0x04,                                  /* iConfiguration: index of string descriptor describing
//                                            the configuration */
//  0x80,                                  /* bmAttributes: self powered */
//  0xFA,                                  /* MaxPower 100 mA: this current is used for detecting vbus */
// 
//  /* interface association descripter(IAD) */
//  0x08,
//  0x0B,
//  0x00,
//  0x02,
//  0x0E,
//  0x03,
//  0x00,
//  0x02,
//  
//  /* video control interface descripter */ 
//  /* standard VC interface descriper */
//  0x09,
//  USB_DESCIPTOR_TYPE_INTERFACE,
//  0x00,
//  0x00,
//  0x00,
//  0x0E,
//  0x01,
//  0x00,
//  0x02,
//  
//  /* class specific VC interface descipter */
//  0x0D,
//  0x24,
//  0x01,
//  0x10,
//  0x01,
//  0x1e,//0x27
//  0x00,
//  0x80,/*dwClockFrequency:12000000hz*/
//  0x8d,
//  0x5b,
//  0x00,
//  0x01,
//  0x01,
//  
//  /* input terminal descipter(camera) */
//  0x11,
//  0x24,
//  0x02,
//  0x01,
//  0x01,
//  0x02,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x02,
//  0x00,
//  0x00,
//  
//  /* output terminal descipter */
//  0x09,
//  0x24,
//  0x03,
//  0x02,
//  0x01,
//  0x01,
//  0x00,
//  0x01,
//  0x00,
//  
//  /* video streaming interface descripter */  
//  /* zero-bandwidth alternate setting0 */
//  /* standard VS interface descripter */
//  0x09,
//  0x04,
//  0x01,
//  0x00,
//  0x00,
//  0x0E,
//  0x02,
//  0x00,
//  0x02,
//  
//  /* class-specific VS header descirpter(input) */
//  0x0E,
//  0x24,
//  0x01,
//  0x01,
//  0x3F,
//  0x00,
//  0x81,
//  0x00,
//  0x02,
//  0x00,
//  0x00,
//  0x00,
//  0x01,
//  0x00,
//  
//  /* class-specific VS format descripter */
//  0x0B,/* bLength:Size of this Descriptor, in bytes: 11 */
//  0x24,/* bDescriptorType:CS_INTERFACE Descriptor type */
//  0x06,/* bDescriptorSubtype:VS_FORMAT_MJPEG Descriptor subtype */
//  0x01,/* bFormatIndex */
//  0x01,/* bNumFrameDescriptors */
//  0x01,/* bmFlags */
//  0x01,/* bDefaultFrameIndex:Default frame index is 1. */
//  0x00,/* bAspectRatioX */
//  0x00,/* bAspectRatioY */
//  0x00,/* bDefaultFrameIndex */
//  0x00,/* bCopyProtect */
//  
//  /* class-specific VS frame descripter */
//  0x26,
//  0x24,
//  0x07,
//  0x01,
//  0x02,
//  0x1D,
//  0x01,
//  0x58,
//  0x01,
//  /*dwMinBitRate:285*344*16*40*/
//  0x60,
//  0xeb,
//  0x1d,
//  0x00,
//  /*dwMaxBitRate:285*344*16*40*/
//  0xc0,
//  0xd6,
//  0x3b,
//  0x00,
//  /* dwMaxVideoFrameBufSize */
//  0xf0,
//  0xfd,
//  0x02,
//  0x00,
//  
//  0x20,/*40bps*/
//  0xa1,
//  0x07,
//  0x00,
//  
//  0x00,
//  
//  0x20,
//  0xa1,
//  0x07,
//  0x00,
//  
//  0x20,/*40bps*/
//  0xa1,
//  0x07,
//  0x00,
//  
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  
//  /* Alternate setting 1 Descriptor */
//  /* standard VS interface descripter */
//  0x09,
//  0x04,
//  0x01,
//  0x01,
//  0x01,
//  0x0E,
//  0x02,
//  0x00,
//  0x05,
//  
//  /* standard VS isochronous video data endpoint descriptor */
//  0x07,
//  0x05,
//  0x81,
//  0x05,
//  LBYTE(USBD_ISO_IN_MAXPACKET_SIZE),
//  HBYTE(USBD_ISO_IN_MAXPACKET_SIZE),
//  0x01

/*origin OK*/

//  USB_DEVICE_CFG_DESC_LEN,               /* bLength: configuration descriptor size */
//  USB_DESCIPTOR_TYPE_CONFIGURATION,      /* bDescriptorType: configuration */
//  LBYTE(USBD_VIDEO_CONFIG_DESC_SIZE),      /* wTotalLength: bytes returned */
//  HBYTE(USBD_VIDEO_CONFIG_DESC_SIZE),      /* wTotalLength: bytes returned */
//  0x02,                                  /* bNumInterfaces: 2 interface */
//  0x01,                                  /* bConfigurationValue: configuration value */
//  0x00,                                  /* iConfiguration: index of string descriptor describing
//                                            the configuration */
//  0x80,                                  /* bmAttributes: self powered */
//  0xFA,                                  /* MaxPower 100 mA: this current is used for detecting vbus */
// 
//  /* interface association descripter(IAD) */
//  0x08,
//  0x0B,
//  0x00,
//  0x02,
//  0x0E,
//  0x03,
//  0x00,
//  0x02,
//  
//  /* video control interface descripter */ 
//  /* standard VC interface descriper */
//  0x09,
//  USB_DESCIPTOR_TYPE_INTERFACE,
//  0x00,
//  0x00,
//  0x00,
//  0x0E,
//  0x01,
//  0x00,
//  0x02,
//  
//  /* class specific VC interface descipter */
//  0x0D,
//  0x24,
//  0x01,
//  0x10,
//  0x01,
//  0x27,
//  0x00,
//  0x00,/*dwClockFrequency:12000000hz*/
//  0x1b,
//  0xb7,
//  0x00,
//  0x01,
//  0x01,
//  
//  /* input terminal descipter(camera) */
//  0x12,
//  0x24,
//  0x02,
//  0x02,
//  0x01,
//  0x02,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x00,
//  0x03,
//  0x00,
//  0x02,
//  0x00,
//  
//  /* output terminal descipter */
//  0x09,
//  0x24,
//  0x03,
//  0x03,
//  0x01,
//  0x01,
//  0x00,
//  0x05,
//  0x00,
//  
//  /* video streaming interface descripter */  
//  /* zero-bandwidth alternate setting0 */
//  /* standard VS interface descripter */
//  0x09,
//  0x04,
//  0x01,
//  0x00,
//  0x00,
//  0x0E,
//  0x02,
//  0x00,
//  0x00,
//  
//  /* class-specific VS header descirpter(input) */
//  0x0E,
//  0x24,
//  0x01,
//  0x01,
//  0x3F,
//  0x00,
//  0x81,
//  0x00,
//  0x03,
//  0x00,
//  0x01,
//  0x00,
//  0x01,
//  0x00,
//  
//  /* class-specific VS format descripter */
//  0x0B,/* bLength:Size of this Descriptor, in bytes: 11 */
//  0x24,/* bDescriptorType:CS_INTERFACE Descriptor type */
//  0x06,/* bDescriptorSubtype:VS_FORMAT_MJPEG Descriptor subtype */
//  0x01,/* bFormatIndex */
//  0x01,/* bNumFrameDescriptors */
//  0x01,/* bmFlags */
//  0x01,/* bDefaultFrameIndex:Default frame index is 1. */
//  0x00,/* bAspectRatioX */
//  0x00,/* bAspectRatioY */
//  0x00,/* bDefaultFrameIndex */
//  0x00,/* bCopyProtect */
//  
//  /* class-specific VS frame descripter */
//  0x1e,
//  0x24,
//  0x07,
//  0x01,
//  0x02,
//  0x1D,
//  0x01,
//  0x58,
//  0x01,
//  /*dwMinBitRate:285*344*16*40*/
//  0x60,
//  0xeb,
//  0x1d,
//  0x00,
//  /*dwMaxBitRate:285*344*16*40*/
//  0x60,
//  0xeb,
//  0x1d,
//  0x00,
//  /* dwMaxVideoFrameBufSize */
//  0xf0,
//  0xfd,
//  0x02,
//  0x00,
//  
//  0x20,/*20bps*/
//  0xa1,
//  0x07,
//  0x00,
//  0x01,
//  0x20,
//  0xa1,
//  0x07,
//  0x00,
//  
//  
//  /* Alternate setting 1 Descriptor */
//  /* standard VS interface descripter */
//  0x09,
//  0x04,
//  0x01,
//  0x01,
//  0x01,
//  0x0E,
//  0x02,
//  0x00,
//  0x00,
//  
//  /* standard VS isochronous video data endpoint descriptor */
//  0x07,
//  0x05,
//  0x81,
//  0x05,
//  LBYTE(USBD_ISO_IN_MAXPACKET_SIZE),
//  HBYTE(USBD_ISO_IN_MAXPACKET_SIZE),
//  0x01


/*Configuration Descriptor*/	
  0x09, /* bLength: Configuation Descriptor size */
  USB_DESCIPTOR_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  LBYTE(USBD_VIDEO_CONFIG_DESC_SIZE),     /* wTotalLength: Bytes returned */
  HBYTE(USBD_VIDEO_CONFIG_DESC_SIZE),
  0x02,         /*bNumInterfaces: 2 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing the configuration*/
  0x80,         /*bmAttributes: bus powered device */
  0xFA,         /*MaxPower 500 mA: this current is used for detecting Vbus*/
  /* 09 */
  /*---------------------------------------------------------------------------*/

  /*Interface Association Descriptor*/
  0x08,	/* bLength: Interface Association Descriptor size */
  11, /* bDescritorType: Interface Association */
  0x00,			/* bFirstInterface: VideoControl Interface ID */
  0x02,			/* bInterfaceCount: 2 Video Interface */
  0x0E,			/* bFunctionClass: CC_VIDEO */
  0x03,			/* bFunctionSubClass: SC_VIDEO_INTERFACE_COLLECTION */
  0x00,			/* bFunctionProtocol: PC_PROTOCOL_UNDEFINED */
  USBD_IDX_INTERFACE_STR,			/* iFunction: Index of string descriptor descripting the function */

  /*Standard VC Interface Descriptor*/
  0x09,	/* bLenght: Standard VC Interface Descriptor size */
  4,	/*bDescriptorType: interface */
  0x00,			/* bInterfaceNumber: interface ID */
  0x00,			/* bAlternateSetting: Alternate setting */
  0x00,			/* bNumEndpoints: no endpoint */
  0x0E,			/* bInterfaceClass: CC_VIDEO */
  0x01,			/* bInterfaceSubClass: SC_VIDEOCONTROL */
  0x00,			/* bInterfacePortocol: PC_PROTOCOL_15 */
  USBD_IDX_INTERFACE_STR,			/*iInterface: Index of string descriptor descripting the interface */

  /*Class-specific VC Interface Header Descriptor*/
  0x0D, /* bLength: Class-specific VC Interface Header Descriptor size */
  0x24, 		/* bDescriptorType: CS_INTERFACE */
  0x01,			/* bDescriptorSubType: VC_HEADER */
  0x10,			/* bcdUVC: UVC1.5 revision */
  0x01,
  0x27,			/* wTotalLength: total size of class-specific descriptors */
  0x00,
  0x80,			/* dwClockFrequency: deprecated */
  0x8D,
  0x5B,
  0x00,
  0x01,			/* bInCollection: number of streaming interfaces */
  0x01,			/* baInterfaceNr(1): VideoStreaming interface 1 belongs to VC interface */

  /*Input Terminal Descriptor Composite*/
  0x11,	/* bLength: Input Terminal Descriptor size */
  0x24, 		/* bDescriptorType: CS_INTERFACE */
  0x02,			/* bDescriptorSubType: VC_INPUT_TERMINAL */
  0x01,			/* bTerminalID: Terminal ID */
  0x01,			/* wTerminalType: ITT_CAMERA */
  0x02,
  0x00,			/* bAssocTerminal: no association */
  0x00, 		/*iTerminal: index of string descriptor descripting the terminal */
  0x00,			/* wObjectiveFocalLengthMin: No optical zoom supported */
  0x00,
  0x00,			/* wObjectiveFocalLengthMax: No optical zoom supported */
  0x00,
  0x00,			/* wOcularFocalLength: No optical zoom supported */
  0x00,
  0x02,			/* bControlSize: this terminal doesn't implement any controls */
  0x00,			/* bmControls: No controls are supported */
  0x00,
  
/*
	//Processing Unit Descriptor
	0x0A,
	0x24,
	0x05,
	0x02,
	0x01,
	0x00,
	0x00,
	0x01,
	0x00,
	0x00,
*/

  /*Output Terminal Descriptor*/
  0x09,	/* bLength: Output Terminal Descriptor size */
  0x24,			/* bDescriptorType: CS_INTERFACE */
  0x03,			/* bDescriptorSubType: VC_OUTPUT_TERMINAL */
  0x03,			/* bTerminalID: Terminal ID */
  0x01,			/* wTerminalType: TT_STREAMING */
  0x01,
  0x00,			/* bAssocTerminal: no association */
  0x01,			/* bSourceID: connect to the input terminal output pin */
  0x00, 		/*iTerminal: index of string descriptor descripting the terminal */

  /*---------------------------------------------------------------------------*/	
  /*Standard VS Interface Alternate 0 setting Descriptor*/
  0x09,	/* bLength: Standard VS Interface Descriptor size */
  4,	/* bDescriptorType: INTERFACE */
  0x01,			/* bInterfaceNumber: Interface ID */
  0x00,			/* bAlternateSetting: index of this alternate setting */
  0x00,			/* bNumEndpoints: 0 endpoint */
  0x0E,			/* bInterfaceClass: CC_VIDEO */
  0x02,			/* bInterfaceSubClass: SC_VIDEOSTREAMING */
  0x00,			/* bInterfaceProtocol: PC_PROTOCOL_15 */
  USBD_IDX_INTERFACE_STR,			/*iInterface: Index of string descriptor descripting the interface */

  /*Class-specific VS Header Descriptor*/
  0x0E,	/* bLength: Class-specific VS Header Descriptor size */
  0x24,			/* bDescriptorType: CS_INTERFACE */
  0x01,			/* bDescriptorSubType: VS_INPUT_HEADER */
  0x01,			/* bNumFormats: one format descriptor follows */
  0x45,//3f  		/* wTotalLength: Total size of class-specific VS interface descriptors */
  0x00,
  0x81,			/* bEndpointAddress: address of isochronour video data endpoint */
  0x00,			/* bmInfo: no dynamic format change supported */
  0x03,			/* bTerminalLink: the terminal ID of output Terminal */
  0x01,			/* bStillCaptureMethod: no supports still image capture method */
  0x00,			/* bTriggerSupport: no supports hardware trigger */
  0x00,			/* bTriggerUsage: initiate still image capture */
  0x01,			/* bControlSize: the size of bmaControls field */
  0x00,			/* bmaControls: no VS specific controls are supported */
	
  /*Payload Format Descriptor*/
  0x0B,	/* blength: Payload Format Descriptor size */
  0x24,			/* bDescriptorType: CS_INTERFACE */
  0x06,			/* bDescriptorSubType: VS_FORMAT_MJPEG */
  0x01,			/* bFormatIndex: index of the format descriptor */
  0x01,			/* bNumFrameDescriptor: number of frame descriptors */
  0x01,			/* bmFlags: FixedSizeSamples */
  0x01,			/* bDefaultFrameIndex: */
  0x00,			/* bAspectRatioX: not required */
  0x00,			/* bAspectRatioY: not required */
  0x00,			/* bInterlaceFlags: non-interlaced stream */
  0x00,			/* bCopyProtect: no restrictions */

  /*Class-specific VS Frame Descriptor*/
  0x26,	/* bLength: Class-specific VS Frame Descriptor size */
  0x24,			/* bDescriptorType: CS_INTERFACE */
  0x07,			/* bDescriptorSubType: VS_FRAME_MJPEG */
  0x01,			/* bFrameIndex: index of frame descriptor */
  0x01,			/* bmCapabilities:still image capture method 0 supported,fixed frame-rate */
  
  MAKE_WORD(IMG_WIDTH),			/* wWidth: frame width */
  MAKE_WORD(IMG_HEIGHT),			/* wHeight: frame height */
  MAKE_DWORD(MIN_BITRATE),			/* dwMinBitRate: */
  MAKE_DWORD(MAX_BITRATE),			/* dwMaxBitRate: */
  MAKE_DWORD(FRAME_BUFFER_SIZE),			/* dwMaxVideoFrameBufSize: in bytes */
  MAKE_DWORD(FRAME_INTERVAL),			/* dwDefaultFrameInterval: */
  0x00,//00			/* bFrameIntervalType: Continuous frame interval */
  MAKE_DWORD(FRAME_INTERVAL),			/* dwMinFrameInterval: */
  MAKE_DWORD(FRAME_INTERVAL),			/* dwMaxFrameInterval: */
  0x00,			/* dwFrameIntervalSetp: no frame interval step supported */
  0x00,
  0x00,
  0x00,
 
 
	//------- VS Color Matching Descriptor Descriptor -------
	0x06,
	0x24,
	0x0d,
	0x01,
	0x01,
	0x04,
 
 
 
  /*---------------------------------------------------------------------------*/	
  /*Standard VS Interface  Alternate setting 1 Descriptor*/
  0x09,	/* bLength: Standard VS Interface Descriptor size */
  4,	/* bDescriptorType: INTERFACE */
  0x01,			/* bInterfaceNumber: Interface ID */
  0x01,			/* bAlternateSetting: index of this alternate setting */
  0x01,			/* bNumEndpoints: 1 endpoint */
  0x0E,			/* bInterfaceClass: CC_VIDEO */
  0x02,			/* bInterfaceSubClass: SC_VIDEOSTREAMING */
  0x00,			/* bInterfaceProtocol: PC_PROTOCOL_15 */
  0x00,//USBD_IDX_INTERFACE_STR,			/*iInterface: Index of string descriptor descripting the interface */

  /*Endpoint Descriptor*/
  0x07,	/* bLength: Endpoint Descriptor size */
  5,	/* bDescriptorType: ENDPOINT */
  0x81,			/* bEndpointAddress: address of isochronour video data endpoint */
  0x05,			/* bmAttributes: Isochronous transfer Asynchronous data type */
  LBYTE(USBD_ISO_IN_MAXPACKET_SIZE),		/* wMaxPacketSize: */
  HBYTE(USBD_ISO_IN_MAXPACKET_SIZE),	
  0x01,			/* bInterval: */
  /**********  Descriptor of UVC interface 0 Alternate setting 0 **************/  
  
};

#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
/* USB Probe & Commit Control */
uint8_t USBD_UVC_ProbeControl[34] =
{
//  0x00,	/* bmHint: indicate which fields shall be kept constant */
//  0x00,
//  0x01,	/* bFormatIndex: Video Format Index from a Format Descriptor */
//  0x01,	/* bFrameIndex: Video Frame Index from a Frame Descriptor */

//  0x20,/* dwFrameInterval: Frame interval in 100ns uints */
//  0xA1,
//  0x07,
//  0x00,
//  0x00,	/* wKeyFrameRate: */
//  0x00,
//  0x00, /* wPFrameRate: */
//  0x00,
//  0x00,	/* wCompQuality: */
//  0x00,
//  0x00,	/* wCompWindowSize: */
//  0x00,
//  0x00,	/* wDelay: */
//  0x00,

//  0xf0,/* dwMaxVideoFrameSize: */
//  0xfd,
//  0x02,
//  0x00,
//  
//  0x00,	/* dwMaxPayloadTransferSize: */
//  0x00,
//  0x00,
//  0x00,
//  0x00,	/* dwClockFrequency: */
//  0x00,
//  0x00,
//  0x00,
//  0x00,	/* bmFramingInfo: */
//  0x00,	/* bPreferedVersion: */
//  0x00,	/* bMinVersion: */
//  0x00,	/* bMaxVersion: */



  0x00,	/* bmHint: indicate which fields shall be kept constant */
  0x00,
  0x01,	/* bFormatIndex: Video Format Index from a Format Descriptor */
  0x01,	/* bFrameIndex: Video Frame Index from a Frame Descriptor */
  MAKE_DWORD(FRAME_INTERVAL),	/* dwFrameInterval: Frame interval in 100ns uints */
  0x00,	/* wKeyFrameRate: */
  0x00,
  0x00, /* wPFrameRate: */
  0x00,
  0x00,	/* wCompQuality: */
  0x00,
  0x00,	/* wCompWindowSize: */
  0x00,
  0x00,	/* wDelay: */
  0x00,
  MAKE_DWORD(FRAME_BUFFER_SIZE),	/* dwMaxVideoFrameSize: */
  0x00,	/* dwMaxPayloadTransferSize: */
  0x00,
  0x00,
  0x00,
  0x00,	/* dwClockFrequency: */
  0x00,
  0x00,
  0x00,
  0x00,	/* bmFramingInfo: */
  0x00,	/* bPreferedVersion: */
  0x00,	/* bMinVersion: */
  0x00,	/* bMaxVersion: */

};
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
uint8_t USBD_UVC_CommitControl[34] =
{
//  0x00,	/* bmHint: indicate which fields shall be kept constant */
//  0x00,
//  0x01,	/* bFormatIndex: Video Format Index from a Format Descriptor */
//  0x01,	/* bFrameIndex: Video Frame Index from a Frame Descriptor */
//  
//  0x20,/* dwFrameInterval: Frame interval in 100ns uints */
//  0xA1,
//  0x07,
//  0x00,
//  0x00,	/* wKeyFrameRate: */
//  0x00,
//  0x00, /* wPFrameRate: */
//  0x00,
//  0x00,	/* wCompQuality: */
//  0x00,
//  0x00,	/* wCompWindowSize: */
//  0x00,
//  0x00,	/* wDelay: */
//  0x00,
//  
//  0xf0,/* dwMaxVideoFrameSize: */
//  0xfd,
//  0x02,
//  0x00,
//  
//  0x00,	/* dwMaxPayloadTransferSize: */
//  0x00,
//  0x00,
//  0x00,
//  0x00,	/* dwClockFrequency: */
//  0x00,
//  0x00,
//  0x00,
//  0x00,	/* bmFramingInfo: */
//  0x00,	/* bPreferedVersion: */
//  0x00,	/* bMinVersion: */
//  0x00,	/* bMaxVersion: */



  0x00,	/* bmHint: indicate which fields shall be kept constant */
  0x00,
  0x01,	/* bFormatIndex: Video Format Index from a Format Descriptor */
  0x01,	/* bFrameIndex: Video Frame Index from a Frame Descriptor */
  MAKE_DWORD(FRAME_INTERVAL),	/* dwFrameInterval: Frame interval in 100ns uints */
  0x00,	/* wKeyFrameRate: */
  0x00,
  0x00, /* wPFrameRate: */
  0x00,
  0x00,	/* wCompQuality: */
  0x00,
  0x00,	/* wCompWindowSize: */
  0x00,
  0x00,	/* wDelay: */
  0x00,
  MAKE_DWORD(FRAME_BUFFER_SIZE),	/* dwMaxVideoFrameSize: */
  0x00,	/* dwMaxPayloadTransferSize: */
  0x00,
  0x00,
  0x00,
  0x00,	/* dwClockFrequency: */
  0x00,
  0x00,
  0x00,
  0x00,	/* bmFramingInfo: */
  0x00,	/* bPreferedVersion: */
  0x00,	/* bMinVersion: */
  0x00,	/* bMaxVersion: */
  
};

/**
  * @brief usb string lang id
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
ALIGNED_HEAD static uint8_t g_string_lang_id[USBD_VIDEO_SIZ_STRING_LANGID] ALIGNED_TAIL =
{
  USBD_VIDEO_SIZ_STRING_LANGID,
  USB_DESCIPTOR_TYPE_STRING,
  0x09,
  0x04,
};

/**
  * @brief usb string serial
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
ALIGNED_HEAD static uint8_t g_string_serial[USBD_VIDEO_SIZ_STRING_SERIAL] ALIGNED_TAIL =
{
  USBD_VIDEO_SIZ_STRING_SERIAL,
  USB_DESCIPTOR_TYPE_STRING,
  'A', 0, 'T', 0, '3', 0, '2', 0, '1', 0, '0', 0, ' ', 0
};


/* device descriptor */
static usbd_desc_t device_descriptor =
{
  USB_DEVICE_DESC_LEN,
  g_usbd_descriptor
};

/* config descriptor */
static usbd_desc_t config_descriptor =
{
  USBD_VIDEO_CONFIG_DESC_SIZE,
  g_usbd_configuration
};

/* langid descriptor */
static usbd_desc_t langid_descriptor =
{
  USBD_VIDEO_SIZ_STRING_LANGID,
  g_string_lang_id
};

/* serial descriptor */
static usbd_desc_t serial_descriptor =
{
  USBD_VIDEO_SIZ_STRING_SERIAL,
  g_string_serial
};

static usbd_desc_t vp_desc;

/**
  * @brief  standard usb unicode convert
  * @param  string: source string
  * @param  unicode_buf: unicode buffer
  * @retval length
  */
static uint16_t usbd_unicode_convert(uint8_t *string, uint8_t *unicode_buf)
{
  uint16_t str_len = 0, id_pos = 2;
  uint8_t *tmp_str = string;

  while(*tmp_str != '\0')
  {
    str_len ++;
    unicode_buf[id_pos ++] = *tmp_str ++;
    unicode_buf[id_pos ++] = 0x00;
  }

  str_len = str_len * 2 + 2;
  unicode_buf[0] = (uint8_t)str_len;
  unicode_buf[1] = USB_DESCIPTOR_TYPE_STRING;

  return str_len;
}

/**
  * @brief  usb int convert to unicode
  * @param  value: int value
  * @param  pbus: unicode buffer
  * @param  len: length
  * @retval none
  */
static void usbd_int_to_unicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;

  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2 * idx] = (value >> 28) + '0';
  }
  else
  {
      pbuf[2 * idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[2 * idx + 1] = 0;
  }
}

/**
  * @brief  usb get serial number
  * @param  none
  * @retval none
  */
static void get_serial_num(void)
{
  uint32_t serial0, serial1, serial2;

  serial0 = *(uint32_t*)MCU_ID1;
  serial1 = *(uint32_t*)MCU_ID2;
  serial2 = *(uint32_t*)MCU_ID3;

  serial0 += serial2;

  if (serial0 != 0)
  {
    usbd_int_to_unicode (serial0, &g_string_serial[2] ,8);
    usbd_int_to_unicode (serial1, &g_string_serial[18] ,4);
  }
}

/**
  * @brief  get device descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_descriptor(void)
{
  return &device_descriptor;
}

/**
  * @brief  get device qualifier
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t * get_device_qualifier(void)
{
  return NULL;
}

/**
  * @brief  get config descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_configuration(void)
{
  return &config_descriptor;
}

/**
  * @brief  get other speed descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_other_speed(void)
{
  return NULL;
}

/**
  * @brief  get lang id descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_lang_id(void)
{
  return &langid_descriptor;
}


/**
  * @brief  get manufacturer descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_manufacturer_string(void)
{
  vp_desc.length = usbd_unicode_convert((uint8_t *)USBD_VIDEO_DESC_MANUFACTURER_STRING, g_usbd_desc_buffer);
  vp_desc.descriptor = g_usbd_desc_buffer;
  return &vp_desc;
}

/**
  * @brief  get product descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_product_string(void)
{
  vp_desc.length = usbd_unicode_convert((uint8_t *)USBD_VIDEO_DESC_PRODUCT_STRING, g_usbd_desc_buffer);
  vp_desc.descriptor = g_usbd_desc_buffer;
  return &vp_desc;
}

/**
  * @brief  get serial descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_serial_string(void)
{
  get_serial_num();
  return &serial_descriptor;
}

/**
  * @brief  get interface descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_interface_string(void)
{
  vp_desc.length = usbd_unicode_convert((uint8_t *)USBD_VIDEO_DESC_INTERFACE_STRING, g_usbd_desc_buffer);
  vp_desc.descriptor = g_usbd_desc_buffer;
  return &vp_desc;
}

/**
  * @brief  get device config descriptor
  * @param  none
  * @retval usbd_desc
  */
static usbd_desc_t *get_device_config_string(void)
{
  vp_desc.length = usbd_unicode_convert((uint8_t *)USBD_VIDEO_DESC_CONFIGURATION_STRING, g_usbd_desc_buffer);
  vp_desc.descriptor = g_usbd_desc_buffer;
  return &vp_desc;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
