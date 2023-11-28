/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "MLX90640_I2C_Driver.h"

//I2C i2c(p9, p10);

i2c_handle_type hi2cx;

void i2c_lowlevel_init(i2c_handle_type* hi2c)
{
  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == I2C1)
  {
    /* i2c periph clock enable */
    crm_periph_clock_enable(CRM_I2C1_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

    /* gpio configuration */
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;

    /* configure i2c pins: scl */
    gpio_initstructure.gpio_pins = GPIO_PINS_6;
    gpio_init(GPIOB, &gpio_initstructure);

    /* configure i2c pins: sda */
    gpio_initstructure.gpio_pins = GPIO_PINS_7;
    gpio_init(GPIOB, &gpio_initstructure);

    /* configure and enable i2c interrupt */
    nvic_irq_enable(I2C1_EVT_IRQn, 0, 0);
    nvic_irq_enable(I2C1_ERR_IRQn, 0, 0);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, 100000);

    i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, 0xA0);
  }
  
}

void MLX90640_I2CInit()
{   
	//uint8_t temp[2]={0,0};
	//uint16_t t2;
	//i2c_status_type i2c_status;
	
	at32_board_init();
	hi2cx.i2cx=I2C1;
	i2c_config(&hi2cx);
	
	/*
	uart_print_init(115200);
	
	printf("start");
  
  while(1)
  {
	  delay_ms(1000);
	  
		i2c_status = i2c_memory_read_int(&hi2cx,I2C_MEM_ADDR_WIDIH_16,0x33<<1,0x800D,temp,2,5000);
	   if(i2c_wait_end(&hi2cx,5000)!=I2C_OK) printf("ERRTIMOUT");
		printf("%u+%u ",temp[0],temp[1]);
	  
	  // if(MLX90640_I2CRead(0x33, 0x800D, 1, &t2)!=-1) printf("%u ",t2);
		
  }
  */
}

int MLX90640_I2CGeneralReset(void)
{    
    int ack;
    uint8_t cmd[2] = {0,0};
    
    cmd[0] = 0x00;
    cmd[1] = 0x06;    
	 
    //ack = i2c.write(cmd[0], &cmd[1], 1, 0);
	 //ack = i2c_memory_write_int(&hi2cx,I2C_MEM_ADDR_WIDIH_16,cmd[0],cmd[0],cmd+1,1,500);
    
    if (ack != I2C_OK)
    {
        return -1;
    }           
    
    delay_us(50);    
    
    return 0;
}

int MLX90640_I2CRead(uint8_t slaveAddr, uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data)
{
    uint8_t sa;                           
    i2c_status_type ack;
    int cnt = 0;
    int i = 0;
    uint8_t i2cData[1664] = {0};
    uint16_t *p;
    
    p = data;
    sa = (slaveAddr << 1);
	 
    //sa = sa | 0x01;
	 ack = i2c_memory_read_int(&hi2cx,I2C_MEM_ADDR_WIDIH_16,sa,startAddress,i2cData,nMemAddressRead*2,50000);
	 if(i2c_wait_end(&hi2cx,5000000)!=I2C_OK) printf("ERRTIMOUT");
	 
    if (ack != I2C_OK)
    {
        return -1; 
    }            
    
    for(cnt=0; cnt < nMemAddressRead; cnt++)
    {
        i = cnt << 1;
        *p++ = (uint16_t)(i2cData[i]<<8) + (uint16_t)i2cData[i+1];
    }
	 
    return 0;   
} 

void MLX90640_I2CFreqSet(int freq)
{
    //i2c.frequency(1000*freq);
}

int MLX90640_I2CWrite(uint8_t slaveAddr, uint16_t writeAddress, uint16_t data)
{
    uint8_t sa;
    i2c_status_type ack;
    uint8_t cmd[2]={0,0};
    static uint16_t dataCheck;
    
    sa = (slaveAddr << 1);
	 
	 cmd[0] = data >> 8;
	 cmd[1] = data & 0x00FF;
        
    //ack = i2c.write(sa, cmd, 4, 0);
    
	ack = i2c_memory_write_int(&hi2cx,I2C_MEM_ADDR_WIDIH_16,sa,writeAddress,cmd,2,50000);
	if(i2c_wait_end(&hi2cx,50000)!=I2C_OK) printf("ERRTIMOUT");
	 
    if (ack != I2C_OK)
    {
        return -1;
    }
	 
    
    MLX90640_I2CRead(slaveAddr,writeAddress,1, &dataCheck);
    
    if ( dataCheck != data)
    {
        return -2;
    }    
	 
    return 0;
}

