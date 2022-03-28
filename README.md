# STM32 - ADS1115 Single-Ended, Single-Shot, PGA & Data Rate Enabled HAL Library
A simple C library (STM32 HAL) for single-ended single-shot ADC measurments with ADS1115 module. (Tested on STM32F411RE)

This library includes several configurations such as PGA and data rate of ADS1115 and tested on STM32F411RE. Example project available.

* ! ADS1115_readSingleEnded(...) returns voltage as mV.

* Don't forget to check datasheet of ADS111x for detailed information: https://www.ti.com/lit/gpn/ADS1113
* Don't forget to check ads1115.h file.

## Example Usage
Configure an I2C peripheral on CubeMX.

```c

/* USER CODE BEGIN 2 */

  // ADS1115 Init
  if(ADS1115_Init(&hi2c1, ADS1115_DATA_RATE_64, ADS1115_PGA_ONE) == HAL_OK){
	  // Device found.
	  HAL_Delay(1500);
  } else{
	  // Device cannot found.
	  while(1);
  }

  float voltageRead;

/* USER CODE END 2 */

```
And,
```c
 /* USER CODE BEGIN WHILE */
  while (1)
  {

	if(ADS1115_readSingleEnded(ADS1115_MUX_AIN0, &voltageRead) == HAL_OK){
		//Voltage successfully read.
	 }

 /* USER CODE END WHILE */
```

## [Türkçe/Turkish] Kullanım Talimatı

 * Adress değişkenini güncelleyin:
 	1) ADDR PIN --> GND ise 1001000
 	2) ADDR PIN --> VDD ise 1001001
 	3) ADDR PIN --> SDA ise 1001010
 	4) ADDR PIN --> SCL ise 1001011

 * ADS1115_Init(...) fonks. ile I2C peripheral ve PGA ile Data Rate ayarlarını yapın. (HAL_OK veya HAL_ERROR)
 * ADS1115_readSingleEnded(...) fonksiyonu ile single-shot okuma yapacağınız portu seçin ve float tipinde değişkeninizin adresini gönderin. (HAL_OK veya HAL_ERROR)
 * Üçüncü adımdan sonra değişkeninizin içerisinde uygun katsayıyla çarpılmış gerilim değeri saklanacaktır.
