/*
 * Library Name: 	ADS1115 STM32 Single-Ended, Single-Shot, PGA & Data Rate Enabled HAL Library
 * Written By:		Ahmet Batuhan Günaltay
 * Date Written:	02/04/2021 (DD/MM/YYYY)
 * Last Modified:	03/04/2021 (DD/MM/YYYY)
 * Description:		STM32F4 HAL-Based ADS1115 Library
 * References:
 * 	- https://www.ti.com/lit/gpn/ADS1113 [Datasheet]
 *
 * Copyright (C) 2021 - Ahmet Batuhan Günaltay
 *
	This software library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  */

/* [Türkçe/Turkish]
 * Kullanım talimatı:
 *	1) Adress değişkenini güncelleyin:
 *		ADDR PIN --> GND ise 1001000
 *		ADDR PIN --> VDD ise 1001001
 *		ADDR PIN --> SDA ise 1001010
 *		ADDR PIN --> SCL ise 1001011
 *
 *	2) ADS1115_Init(...) fonks. ile I2C peripheral ve PGA ile Data Rate ayarlarını yapın. (HAL_OK veya HAL_ERROR)
 *	3) ADS1115_readSingleEnded(...) fonksiyonu ile single-shot okuma yapacağınız portu seçin ve float tipinde değişkeninizin adresini gönderin.
 *	4) Üçüncü adımdan sonra değişkeninizin içerisinde uygun katsayıyla çarpılmış gerilim değeri saklanacaktır.
 *
 *  */

#include "stm32f4xx_hal.h" // Could be changed for a specific processor.
#include "string.h"
#include "ads1115.h"

/* Variables */
uint8_t ADS1115_devAddress = 0b1001000;	// 7 bit address, without R/W' bit.

I2C_HandleTypeDef ADS1115_I2C_Handler;	// HAL I2C handler store variable.

uint16_t ADS1115_dataRate = ADS1115_DATA_RATE_128; // Default
uint16_t ADS1115_pga = ADS1115_PGA_TWO; // Default
uint16_t ADS1115_port = ADS1115_MUX_AIN0; // Default

uint8_t ADS1115_config[2];
uint8_t ADS1115_rawValue[2];
float ADS1115_voltCoef; // Voltage coefficient.

/* Function definitions. */
HAL_StatusTypeDef ADS1115_Init(I2C_HandleTypeDef *handler, uint16_t setDataRate, uint16_t setPGA) {

	// Handler
	memcpy(&ADS1115_I2C_Handler, handler, sizeof(*handler));

	// Data rate and PGA configurations.
	ADS1115_dataRate = setDataRate;
	ADS1115_pga = setPGA;

	// Voltage coefficient update.
	switch (ADS1115_pga) {

	case ADS1115_PGA_TWOTHIRDS:
		ADS1115_voltCoef = 0.1875;
		break;

	case ADS1115_PGA_ONE:
		ADS1115_voltCoef = 0.125;
		break;

	case ADS1115_PGA_TWO:
		ADS1115_voltCoef = 0.0625;
		break;

	case ADS1115_PGA_FOUR:
		ADS1115_voltCoef = 0.03125;
		break;

	case ADS1115_PGA_EIGHT:
		ADS1115_voltCoef = 0.015625;
		break;

	case ADS1115_PGA_SIXTEEN:
		ADS1115_voltCoef = 0.0078125;
		break;

		}

	if (HAL_I2C_IsDeviceReady(&ADS1115_I2C_Handler, (uint16_t) (ADS1115_devAddress << 1), 5, ADS1115_TIMEOUT) == HAL_OK) {
		return HAL_OK;
	} else {
		return HAL_ERROR;
	}

}

HAL_StatusTypeDef ADS1115_readSingleEnded(uint16_t muxPort, float *voltage) {

	ADS1115_config[0] = ADS1115_OS | muxPort | ADS1115_pga | ADS1115_MODE;
	ADS1115_config[1] = ADS1115_dataRate | ADS1115_COMP_MODE | ADS1115_COMP_POL | ADS1115_COMP_LAT| ADS1115_COMP_QUE;
	uint8_t waiting=1;
	uint16_t cnt=0;

	if(HAL_I2C_Mem_Write(&ADS1115_I2C_Handler, (uint16_t) (ADS1115_devAddress << 1), ADS1115_CONFIG_REG, 1, ADS1115_config, 2, ADS1115_TIMEOUT) == HAL_OK)
	{
		while(waiting) //Checking Data Ready
		{
			if(HAL_I2C_Mem_Read(&ADS1115_I2C_Handler, (uint16_t) ((ADS1115_devAddress << 1) | 0x1), ADS1115_CONFIG_REG, 1, ADS1115_config, 2, ADS1115_TIMEOUT) == HAL_OK)
				{
				if(ADS1115_config[0] & ADS1115_OS) waiting=0;
				}
			else return HAL_ERROR;
			if(++cnt==100) return HAL_ERROR;
		}

		if(HAL_I2C_Mem_Read(&ADS1115_I2C_Handler, (uint16_t) ((ADS1115_devAddress << 1) | 0x1), ADS1115_CONVER_REG, 1, ADS1115_rawValue, 2, ADS1115_TIMEOUT) == HAL_OK)
		{
			*voltage = (float) (((int16_t) (ADS1115_rawValue[0] << 8) | ADS1115_rawValue[1]) * ADS1115_voltCoef);
			return HAL_OK;

		}

	}

	return HAL_ERROR;

}
