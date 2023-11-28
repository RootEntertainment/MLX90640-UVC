/**
  **************************************************************************
  * @file     main.c
  * @version  v2.1.2
  * @date     2022-08-16
  * @brief    main program
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

#include "at32f403a_407_board.h"
#include "at32f403a_407_clock.h"
#include "usbd_core.h"
#include "video_class.h"
#include "video_desc.h"
#include "usbd_int.h"
#include "MLX90640_I2C_Driver.h"
#include "MLX90640_API.h"
#include "string.h"
#include "jpegbuff.h"
#include "ejpeg.h"
//#include "i2c_application.h"

uint8_t jpeg_data1[JPEG_BUFFSIZE];
uint8_t jpeg_data2[JPEG_BUFFSIZE];

uint8_t buffnow=0;
uint8_t buffsta[2]={FALSE,FALSE};

uint16_t map[120][160];
uint8_t gray[24][32];
//uint8_t gray;

struct Color{
	uint8_t y;
	uint8_t u;
	uint8_t v;
};

struct Color colormap1[256]={{3,142,125},{3,142,125},{3,143,125},{3,143,125},{3,144,125},{3,144,125},{3,145,125},{4,146,125},{4,146,124},{4,147,124},{4,147,124},{4,148,124},{4,148,124},{4,149,124},{4,149,124},{5,150,124},{5,151,124},{5,151,125},{6,151,126},{7,151,127},{8,151,127},{8,151,128},{9,151,129},{10,152,130},{10,152,131},{11,152,133},{12,152,133},{13,153,134},{14,153,135},{14,153,136},{15,153,137},{16,153,138},{17,153,139},{17,154,140},{18,154,141},{19,154,142},{20,155,142},{20,155,143},{21,155,144},{22,155,145},{22,155,146},{23,155,147},{24,156,148},{25,156,149},{26,156,150},{26,156,151},{27,157,152},{28,157,153},{28,157,154},{29,157,155},{30,157,156},{31,157,157},{31,158,158},{32,158,159},{33,158,159},{33,158,160},{34,159,161},{35,159,162},{36,159,163},{36,159,164},{37,159,165},{38,159,166},{39,160,167},{40,160,168},{40,160,169},{41,160,170},{42,161,171},{43,161,172},{43,161,173},{44,161,174},{45,161,174},{45,161,175},{46,162,176},{47,162,177},{48,162,178},{48,162,179},{49,163,180},{50,163,181},{51,163,182},{51,163,183},{52,163,184},{53,163,185},{54,164,186},{54,164,187},{55,164,188},{56,164,189},{57,165,190},{57,165,190},{58,165,191},{59,165,192},{59,165,193},{60,166,194},{60,163,195},{60,160,197},{60,158,198},{60,155,200},{61,153,201},{61,150,203},{61,148,204},{61,145,205},{61,142,207},{61,140,208},{63,137,209},{64,134,209},{66,130,209},{67,127,210},{68,124,210},{70,120,211},{71,117,211},{72,114,212},{74,110,212},{75,107,213},{76,104,213},{78,101,214},{79,97,215},{81,94,215},{83,91,215},{84,87,216},{85,84,216},{86,81,217},{88,78,217},{90,77,217},{92,76,217},{93,75,217},{95,74,218},{97,73,218},{99,72,218},{101,70,218},{103,69,218},{105,68,218},{106,67,218},{108,66,218},{111,65,219},{113,64,219},{114,63,219},{116,62,219},{118,61,219},{120,60,219},{122,58,219},{124,57,219},{126,56,219},{127,56,219},{128,55,218},{130,54,216},{131,53,216},{132,53,215},{133,52,214},{134,51,213},{136,51,212},{137,50,211},{139,49,210},{140,48,209},{141,48,209},{142,47,208},{144,46,206},{145,45,206},{146,45,205},{147,44,204},{149,43,203},{150,43,202},{151,42,201},{153,41,200},{154,40,199},{155,40,198},{156,39,198},{157,38,197},{159,37,196},{160,37,195},{161,36,194},{163,35,193},{164,35,192},{166,34,191},{167,33,190},{168,32,189},{169,32,188},{170,31,188},{171,31,187},{173,30,185},{174,29,185},{176,28,184},{177,28,183},{178,27,182},{180,26,181},{181,25,180},{182,25,179},{183,24,178},{184,23,178},{186,23,177},{187,22,175},{188,21,175},{190,20,174},{191,20,173},{192,19,172},{194,18,171},{195,17,170},{196,17,169},{197,16,168},{198,15,167},{200,15,167},{201,14,165},{203,13,165},{204,12,164},{205,12,163},{206,11,162},{207,10,161},{209,9,160},{210,9,159},{211,8,158},{213,7,157},{214,7,157},{215,6,155},{217,5,155},{218,4,154},{219,4,153},{220,3,152},{222,5,151},{224,7,149},{226,10,148},{228,13,146},{229,16,146},{230,19,145},{230,22,145},{231,25,144},{232,28,144},{232,31,143},{233,34,143},{234,38,142},{235,41,142},{235,44,141},{236,47,141},{237,50,140},{238,53,140},{238,56,139},{239,59,139},{240,62,138},{240,66,138},{241,69,137},{242,72,137},{242,75,136},{243,78,136},{244,81,135},{245,84,135},{245,87,134},{246,90,134},{247,94,133},{247,97,133},{248,100,132},{249,103,132},{249,106,131},{250,109,131},{251,112,130},{252,115,130},{252,118,129},{253,122,128},{254,125,128},{255,128,128}};

float mlx90640To[768];
uint16_t frame[834];
float emissivity=0.95;
uint8_t status;
float vdd;
float Ta;
paramsMLX90640 mlx90640;

uint16_t statusReg;
uint16_t comlen;
uint8_t command[4];

usbd_core_type usb_core_dev;

UInt8* CallBack(UInt8* bufptr, Int32 byte) {
	
	return bufptr;
}

/**
  * @brief  usb 48M clock select
  * @param  clk_s:USB_CLK_HICK, USB_CLK_HEXT
  * @retval none
  */
void usb_clock48m_select(usb_clk48_s clk_s)
{
  if(clk_s == USB_CLK_HICK)
  {
    crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_HICK);

    /* enable the acc calibration ready interrupt */
    crm_periph_clock_enable(CRM_ACC_PERIPH_CLOCK, TRUE);

    /* update the c1\c2\c3 value */
    acc_write_c1(7980);
    acc_write_c2(8000);
    acc_write_c3(8020);

    /* open acc calibration */
    acc_calibration_mode_enable(ACC_CAL_HICKTRIM, TRUE);
  }
  else
  {
    switch(system_core_clock)
    {
      /* 48MHz */
      case 48000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1);
        break;

      /* 72MHz */
      case 72000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1_5);
        break;

      /* 96MHz */
      case 96000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2);
        break;

      /* 120MHz */
      case 120000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2_5);
        break;

      /* 144MHz */
      case 144000000:
        crm_usb_clock_div_set(CRM_USB_DIV_3);
        break;

      /* 168MHz */
      case 168000000:
        crm_usb_clock_div_set(CRM_USB_DIV_3_5);
        break;

      /* 192MHz */
      case 192000000:
        crm_usb_clock_div_set(CRM_USB_DIV_4);
        break;

      default:
        break;

    }
  }
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
	i2c_status_type i2c_status;
  /* config nvic priority group */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

  /* system clock config */
  system_clock_config();

  /* at32 board init */
  
	MLX90640_I2CInit();
	delay_ms(10);
	
  /* select usb 48m clcok source */
  usb_clock48m_select(USB_CLK_HICK);

  /* enable usb clock */
  crm_periph_clock_enable(CRM_USB_PERIPH_CLOCK, TRUE);

  /* enable usb interrupt */
  nvic_irq_enable(USBFS_L_CAN1_RX0_IRQn, 0, 0);

  /* usb core init */
  usbd_core_init(&usb_core_dev, USB, &video_class_handler, &video_desc_handler, 0);
  
  uart_print_init(115200);

	printf("OK ");
	
	JPG_initImgFormat(160, 120, 1, JPG_IMGFMT_YUV422, 2, 0, 0, 0);
	JPG_initOutStream(CallBack, jpeg_data2, JPEG_BUFFSIZE);
	//set_IMGsrc(gray);
	set_IMGsrc(map);
	JPG_WriteHeader(0);
	JPG_setOutBuff(jpeg_data1);
	JPG_WriteHeader(0);
	printf("JPGEnOK ");
	
	if(MLX90640_SetRefreshRate(MLX90640_Add, FPS8)!=0) printf("RefreshRateERR ");  //设置帧率
	else printf("RefreshRateOK ");
	
	if(MLX90640_SetChessMode(MLX90640_Add)!=0) printf("ChessModeERR ");                 //棋盘模式   
	else printf("ChessModeOK ");
	
	if(MLX90640_DumpEE(MLX90640_Add, frame)==-1) printf("DumpEE-ERR "); //读取像素校正参数 
	else printf("DumpEEOK ");
	
	MLX90640_ExtractParameters(frame, &mlx90640);
	
	/* enable usb pull-up */
	usbd_connect(&usb_core_dev);
	
	while(1)
	{
		
		MLX90640_I2CRead(MLX90640_Add, 0x8000, 1, &statusReg);
		if(statusReg & 0x0008)
		{
			gpio_bits_reset(GPIOA,GPIO_PINS_0);
			status=MLX90640_GetFrameData(MLX90640_Add, frame);
			Ta = MLX90640_GetTa(frame, &mlx90640);    //计算实时外壳温度
			MLX90640_CalculateTo(frame, &mlx90640, emissivity , Ta-TA_SHIFT, mlx90640To);   //计算像素点温度
			
			uint16_t k=0;
			for(int i = 0; i < 24; i++){
				for(int j=0; j<32; j++){
					gray[i][j]=(uint8_t)(((float)(mlx90640To[k]-min)/(max-min))*255.0);
					k++;
				}
			}
			
			uint8_t t1,t2;
			for(int i=0; i<120; i++){
				for(int j=0; j<160; j+=2){
					t1=gray[i*23/119][j*31/159];
					t2=gray[i*23/119][(j+1)*31/159];
					map[i][j]=colormap1[t1].u<<8|colormap1[t1].y;
					map[i][j+1]=colormap1[t2].v<<8|colormap1[t2].y;
				}
			}
			
			if(!buffsta[0]){
				JPG_setOutBuff(jpeg_data1+623);
				JPG_Encode();
				buffsta[0]=TRUE;
			}else if(!buffsta[1]){
				JPG_setOutBuff(jpeg_data2+623);
				JPG_Encode();
				buffsta[1]=TRUE;
			}
			
		}else {
			gpio_bits_set(GPIOA,GPIO_PINS_0);
		}
		
	}
}

/**
  * @brief  this function handles usb interrupt.
  * @param  none
  * @retval none
  */
void USBFS_L_CAN1_RX0_IRQHandler(void)
{
  usbd_irq_handler(&usb_core_dev);
}

/**
  * @brief  usb delay millisecond function.
  * @param  ms: number of millisecond delay
  * @retval none
  */
void usb_delay_ms(uint32_t ms)
{
  /* user can define self delay function */
  delay_ms(ms);
}

/**
  * @brief  usb delay microsecond function.
  * @param  us: number of microsecond delay
  * @retval none
  */
void usb_delay_us(uint32_t us)
{
  delay_us(us);
}

/**
  * @}
  */

/**
  * @}
  */
