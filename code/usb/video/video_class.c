/**
  **************************************************************************
  * @file     cdc_class.c
  * @version  v2.0.7
  * @date     2022-04-02
  * @brief    usb cdc class type
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
#include "usbd_core.h"
#include "video_class.h"
#include "video_desc.h"
#include "stdio.h"
#include "ejpeg.h"
#include "stdlib.h"
#include "string.h"
#include "jpegbuff.h"

/** @addtogroup AT32F435_437_middlewares_usbd_class
  * @{
  */

/** @defgroup USB_cdc_class
  * @brief usb device class cdc demo
  * @{
  */

/** @defgroup USB_cdc_class_private_functions
  * @{
  */

static usb_sts_type class_init_handler(void *udev);
static usb_sts_type class_clear_handler(void *udev);
static usb_sts_type class_setup_handler(void *udev, usb_setup_type *setup);
static usb_sts_type class_ept0_tx_handler(void *udev);
static usb_sts_type class_ept0_rx_handler(void *udev);
static usb_sts_type class_in_handler(void *udev, uint8_t ept_num);
static usb_sts_type class_out_handler(void *udev, uint8_t ept_num);
static usb_sts_type class_sof_handler(void *udev);
static usb_sts_type class_event_handler(void *udev, usbd_event_type event);

//static usb_sts_type cdc_struct_init(cdc_struct_type *pcdc);


static void video_req_get_cur(void *udev, usb_setup_type *setup);
static void video_req_set_cur(void *udev, usb_setup_type *setup);

uint16_t packet_count = (uint16_t)((uint32_t)JPEG_BUFFSIZE/(USBD_ISO_IN_MAXPACKET_SIZE-2));
uint16_t packet_remainder = (uint16_t)(((uint32_t)JPEG_BUFFSIZE)%((uint32_t)(USBD_ISO_IN_MAXPACKET_SIZE-2)));
uint16_t packet_index = 0;
uint8_t payload_header[2] = {0x02,0x00};
uint8_t* jpeg_data=jpeg_data1;

uint8_t* buffselect[2]={jpeg_data1,jpeg_data2};

/* cdc data struct */
video_struct_type video_struct;

extern uint8_t USBD_UVC_ProbeControl[34];
extern uint8_t USBD_UVC_CommitControl[34];
/* usb device class handler */
usbd_class_handler video_class_handler =
{
  class_init_handler,
  class_clear_handler,
  class_setup_handler,
  class_ept0_tx_handler,
  class_ept0_rx_handler,
  class_in_handler,
  class_out_handler,
  class_sof_handler,
  class_event_handler,
  &video_struct
};
/**
  * @brief  initialize usb custom hid endpoint
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type
  */
static usb_sts_type class_init_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
	
	/* enable uvc in endpoint double buffer mode */
  usbd_ept_dbuffer_enable(pudev, USBD_VIDEO_ISO_IN_EPT);
	
  /* open in endpoint */
  usbd_ept_open(pudev, USBD_VIDEO_ISO_IN_EPT, EPT_ISO_TYPE, USBD_ISO_IN_MAXPACKET_SIZE);

  return status;
}

/**
  * @brief  clear endpoint or other state
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type
  */
static usb_sts_type class_clear_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
	
  /* close in endpoint */
  usbd_ept_close(pudev, USBD_VIDEO_ISO_IN_EPT);

  return status;
}

uint8_t play_status = PLAY_STATUS_STOP;

/**
  * @brief  usb device class setup request handler
  * @param  udev: to the structure of usbd_core_type
  * @param  setup: setup packet
  * @retval status of usb_sts_type
  */
static usb_sts_type class_setup_handler(void *udev, usb_setup_type *setup)
{
	uint8_t* pbuf;
	uint16_t len;
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  video_struct_type *pvideo = (video_struct_type *)pudev->class_handler->pdata;
	
  
  switch(setup->bmRequestType & USB_REQ_TYPE_RESERVED)
  {
    // class request
    case USB_REQ_TYPE_CLASS:      
      switch (setup->bRequest)
      {
        case UVC_GET_CUR:
          //video_req_get_cur(pudev, setup);
          //break;
		  case UVC_GET_DEF:
		  case UVC_GET_MIN:
			  /*
			  if(setup->wIndex==0x0001){
				  
				  if(setup->wValue==0x0100){
					  usbd_ctrl_send(pudev, USBD_UVC_ProbeControl, setup->wLength);
					  //usbd_ctrl_unsupport(pudev);
				  }
				  else if(setup->wValue==0x0200){
					  usbd_ctrl_send(pudev, USBD_UVC_CommitControl, setup->wLength);
					  //usbd_ctrl_unsupport(pudev);
				  }else{
					  usbd_ctrl_send(pudev, pvideo->control.data, setup->wLength);
				  }
				  
			  }else{
				  usbd_ctrl_unsupport(pudev);
			  }
			  
			  break;
		     */
		  case UVC_GET_MAX:
			  /*
			  if(setup->wIndex==0x0001){
				  
				  if(setup->wValue==0x0100){
					  usbd_ctrl_send(pudev, USBD_UVC_ProbeControl, setup->wLength);
					  //usbd_ctrl_unsupport(pudev);
				  }
				  else if(setup->wValue==0x0200){
					  usbd_ctrl_send(pudev, USBD_UVC_CommitControl, setup->wLength);
					  //usbd_ctrl_unsupport(pudev);
				  }else{
					  usbd_ctrl_send(pudev, pvideo->control.data, setup->wLength);
				  }
				  
			  }else{
				  usbd_ctrl_unsupport(pudev);
			  }
			  break;
			  */
			  video_req_get_cur(pudev, setup);
		     break;
		  case UVC_SET_CUR:
           video_req_set_cur(pudev, setup);   
           break;
        default:
				//gpio_bits_reset(GPIOA,GPIO_PINS_1);
				usbd_ctrl_unsupport(pudev);
				return USB_FAIL;   
      }
      break;
    // standard request
    case USB_REQ_TYPE_STANDARD:
      switch(setup->bRequest)
      {
        case USB_STD_REQ_GET_DESCRIPTOR:
			  /*
			  if(HBYTE(setup->wValue) == CS_DEVICE){
				  gpio_bits_reset(GPIOA,GPIO_PINS_1);
				  pbuf=video_desc_handler.get_device_descriptor()->descriptor;
				  len=USBD_VIDEO_CONFIG_DESC_SIZE>setup->wLength?setup->wLength:USBD_VIDEO_CONFIG_DESC_SIZE;
			  }
			 usbd_ctrl_send(pudev, pbuf, len);
		    */
          usbd_ctrl_unsupport(pudev);
          break;
        case USB_STD_REQ_GET_INTERFACE:
          usbd_ctrl_send(pudev, (uint8_t *)&pvideo->alt_setting, 1);
          break;
        case USB_STD_REQ_SET_INTERFACE:
          if((setup->wValue )  <= 1)
          {
            pvideo->alt_setting = setup->wValue;
            if(pvideo->alt_setting == 1)
            {
					play_status = PLAY_STATUS_READY;
            }
            else
            {
					play_status = PLAY_STATUS_STOP;
            }
          }
          else
          {
            usbd_ctrl_unsupport(pudev);
          }
          break;
		  
        default:
			 usbd_ctrl_unsupport(pudev);
          break;
			 
      }
      break;
	 
    default:
      usbd_ctrl_unsupport(pudev);
      break;
		
  }
  
  
  return status;
}

/**
  * @brief  usb device endpoint 0 in status stage complete
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type
  */
static usb_sts_type class_ept0_tx_handler(void *udev)
{
  usb_sts_type status = USB_OK;

  /* ...user code... */

  return status;
}

/**
  * @brief  usb device endpoint 0 out status stage complete
  * @param  udev: usb device core handler type
  * @retval status of usb_sts_type
  */
static usb_sts_type class_ept0_rx_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  
  /* ...user code... */
	
	
  
  return status;
}

uint8_t packet[USBD_ISO_IN_MAXPACKET_SIZE]={0x00};

/**
  * @brief  usb device transmision complete handler
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_num: endpoint number
  * @retval status of usb_sts_type
  */
static usb_sts_type class_in_handler(void *udev, uint8_t ept_num)
{
	usb_sts_type status = USB_OK;
	
  usbd_core_type *pudev = (usbd_core_type *)udev;
  
  
  video_struct_type *pvideo = (video_struct_type *)pudev->class_handler->pdata;

  uint16_t packet_size = 0;
	/*
	if(packet_index > packet_count)
   {
        packet_index = 0;
   }
	*/
  //gpio_bits_reset(GPIOA,GPIO_PINS_0);
  if((ept_num & 0x7F) == (USBD_VIDEO_ISO_IN_EPT & 0x7F))
  {
    if(PLAY_STATUS_STREAMING == play_status)
    {
      if(packet_index == 0)
      {
		  payload_header[1]&=0xfd;
		  payload_header[1]^=0x01;
        memcpy(packet+2,jpeg_data+packet_index*(USBD_ISO_IN_MAXPACKET_SIZE-2),USBD_ISO_IN_MAXPACKET_SIZE-2);
        packet_size = USBD_ISO_IN_MAXPACKET_SIZE;
		  packet_index++;
      }
      else if(packet_index < packet_count)
      {
        memcpy(packet+2,jpeg_data+packet_index*(USBD_ISO_IN_MAXPACKET_SIZE-2),USBD_ISO_IN_MAXPACKET_SIZE-2);
        packet_size = USBD_ISO_IN_MAXPACKET_SIZE;
		  packet_index++;
      }
      else if(packet_index == packet_count)
      {
		  payload_header[1] |= 0x02;
        memcpy(packet+2,jpeg_data+packet_index*(USBD_ISO_IN_MAXPACKET_SIZE-2),packet_remainder);
        packet_size = packet_remainder + 2;
			
			if(buffsta[!buffnow]){
				buffsta[buffnow]=FALSE;
				buffnow=!buffnow;
				jpeg_data=buffselect[buffnow];
			}
			
			packet_index=0;
      }
		
      packet[0] = payload_header[0];
		packet[1] = payload_header[1];
      
		usbd_ept_send(pudev, USBD_VIDEO_ISO_IN_EPT, packet, packet_size);
      
    }
  }
  

  return status;
}

/**
  * @brief  usb device endpoint receive data
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_num: endpoint number
  * @retval status of usb_sts_type
  */
static usb_sts_type class_out_handler(void *udev, uint8_t ept_num)
{
  usb_sts_type status = USB_OK;
  return status;
}

/**
  * @brief  usb device sof handler
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type
  */
static usb_sts_type class_sof_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  
  //payload_header[0]=0x02;
  //payload_header[1]=0x00;
	
  if(PLAY_STATUS_READY == play_status)
  {
	  if(!buffsta[buffnow]){
		  buffnow=!buffnow;
		  jpeg_data=buffselect[buffnow];
	  }
	 packet_index=0;
	 //payload_header[1]=0x00;
    play_status = PLAY_STATUS_STREAMING;
	  
	 usbd_ept_send(pudev, USBD_VIDEO_ISO_IN_EPT, payload_header, 2);
	  
  }
	
  /* ...user code... */

  return status;
}

/**
  * @brief  usb device event handler
  * @param  udev: to the structure of usbd_core_type
  * @param  event: usb device event
  * @retval status of usb_sts_type
  */
static usb_sts_type class_event_handler(void *udev, usbd_event_type event)
{
  usb_sts_type status = USB_OK;
  switch(event)
  {
    case USBD_RESET_EVENT:

      /* ...user code... */

      break;
    case USBD_SUSPEND_EVENT:

      /* ...user code... */

      break;
    case USBD_WAKEUP_EVENT:
      /* ...user code... */

      break;
    case USBD_INISOINCOM_EVENT:
      break;
    case USBD_OUTISOINCOM_EVENT:
      break;

    default:
      break;
  }
  return status;
}



static void video_req_get_cur(void *udev, usb_setup_type *setup)
{
  usbd_core_type *pudev = (usbd_core_type *)udev;
  video_struct_type *pvideo = (video_struct_type *)pudev->class_handler->pdata;
  
  memset(pvideo->control.data, 0, USB_MAX_EP0_SIZE);
  
  if((HBYTE(setup->wValue)) == VS_PROBE_CONTROL)
  {
    usbd_ctrl_send(pudev, USBD_UVC_ProbeControl, setup->wLength);
  }
  else if((HBYTE(setup->wValue)) == VS_COMMIT_CONTROL)
  {
    usbd_ctrl_send(pudev, USBD_UVC_CommitControl, setup->wLength);
  }
  else
  {
    usbd_ctrl_send(pudev, pvideo->control.data, setup->wLength);
  }
  
}

static void video_req_set_cur(void *udev, usb_setup_type *setup)
{
  usbd_core_type *pudev = (usbd_core_type *)udev;
  video_struct_type *pvideo = (video_struct_type *)pudev->class_handler->pdata;
	
	//uint8_t* temp = (uint8_t*) malloc(sizeof(uint8_t)*setup->wLength);
	
  if(setup->wLength > 0U)
  {
    if((HBYTE(setup->wValue)) == VS_PROBE_CONTROL)
    {
      usbd_ctrl_recv(pudev, USBD_UVC_ProbeControl, setup->wLength);
    }
    else if((HBYTE(setup->wValue)) == VS_COMMIT_CONTROL)
    {
      usbd_ctrl_recv(pudev, USBD_UVC_CommitControl, setup->wLength);
    }
    else
    {
      usbd_ctrl_recv(pudev, pvideo->control.data, setup->wLength);
    }
  }
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

