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
#ifndef _MLX90640_I2C_Driver_H_
#define _MLX90640_I2C_Driver_H_

#include "stdint.h"
#include "at32f403a_407_board.h"
#include "i2c_application.h"

#define LOW 0;
#define HIGH 1;

#define MLX90640_Add 0x33
#define TA_SHIFT 8

/*
#define SCL_HIGH GPIOB->scr=GPIO_PINS_6;
#define SCL_LOW GPIOB->clr=GPIO_PINS_6;
#define SDA_HIGH SDA_setInput();
#define SDA_LOW SDA_setOutput();

#define SDA gpio_input_data_bit_read(GPIOB,GPIO_PINS_7)
*/
	 
enum REFRESHRATE{
  FPS2 = 0x02,
  FPS4 = 0x03,
  FPS8 = 0x04,
  FPS16 = 0x05,
  FPS32 = 0x06
};
/*
void SDA_setInput(void);
void SDA_setOutput(void); 
*/
void MLX90640_I2CInit(void);
int MLX90640_I2CGeneralReset(void);
int MLX90640_I2CRead(uint8_t slaveAddr,uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data);
int MLX90640_I2CWrite(uint8_t slaveAddr,uint16_t writeAddress, uint16_t data);
void MLX90640_I2CFreqSet(int freq);


#endif