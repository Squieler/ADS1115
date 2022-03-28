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

/* Definitions */
#define ADS1115_OS (0b1 << 7) // Default

#define ADS1115_MUX_AIN0 (0b100 << 4)		// Analog input 1
#define ADS1115_MUX_AIN1 (0b101 << 4)		// Analog input 2
#define ADS1115_MUX_AIN2 (0b110 << 4)		// Analog input 3
#define ADS1115_MUX_AIN3 (0b111 << 4)		// Analog input 4

#define ADS1115_PGA_TWOTHIRDS 	(0b000 << 1) 		// 2/3x Gain	-- 0.1875 mV by one bit		MAX: +- VDD + 0.3V
#define ADS1115_PGA_ONE			(0b001 << 1) 		// 1x Gain		-- 0.125 mV by one bit		MAX: +- VDD + 0.3V
#define ADS1115_PGA_TWO			(0b010 << 1) 		// 2x Gain		-- 0.0625 mV by one bit		MAX: +- 2.048 V
#define ADS1115_PGA_FOUR		(0b011 << 1) 		// 4x Gain		-- 0.03125 mV by one bit	MAX: +- 1.024 V
#define ADS1115_PGA_EIGHT		(0b100 << 1) 		// 8x Gain		-- 0.015625 mV by one bit	MAX: +- 0.512 V
#define ADS1115_PGA_SIXTEEN		(0b111 << 1) 		// 16x Gain		-- 0.0078125 mV by one bit	MAX: +- 0.256 V

#define ADS1115_MODE (0b1) // Default

#define ADS1115_DATA_RATE_8		(0b000 << 5)			// 8SPS
#define ADS1115_DATA_RATE_16	(0b001 << 5)			// 16SPS
#define ADS1115_DATA_RATE_32	(0b010 << 5)			// 32SPS
#define ADS1115_DATA_RATE_64	(0b011 << 5)			// 64SPS
#define ADS1115_DATA_RATE_128	(0b100 << 5)			// 128SPS
#define ADS1115_DATA_RATE_250	(0b101 << 5)			// 250SPS
#define ADS1115_DATA_RATE_475	(0b110 << 5)			// 475SPS
#define ADS1115_DATA_RATE_860	(0b111 << 5)			// 860SPS

#define ADS1115_COMP_MODE 	(0b0 << 4) // Default
#define ADS1115_COMP_POL 	(0b0 << 3) // Default
#define ADS1115_COMP_LAT 	(0b0 << 2) // Default
#define ADS1115_COMP_QUE 	(0b11)	   // Default

/* ADS1115 register configurations */
#define ADS1115_CONVER_REG 0x0
#define ADS1115_CONFIG_REG 0x1

/* TIMEOUT */
#define ADS1115_TIMEOUT 1 // Timeout for HAL I2C functions.

/* Function prototypes. */
HAL_StatusTypeDef ADS1115_Init(I2C_HandleTypeDef *handler, uint16_t setDataRate, uint16_t setPGA);
HAL_StatusTypeDef ADS1115_readSingleEnded(uint16_t muxPort, float *voltage);
