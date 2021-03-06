/*
 * RF24HALChibios.h
 *
 *  Created on: 26 ���. 2018 �.
 *      Author: Bogdan
 */

#ifndef NRF24_RF24HALCHIBIOS_H_
#define NRF24_RF24HALCHIBIOS_H_

#include <stdint.h>

#include "RF24HAL.h"

class RF24HAL_Chibios : public RF24HAL {
public:
	RF24HAL_Chibios();
	virtual ~RF24HAL_Chibios();

	uint32_t millis();
	void delay(uint16_t ms);
	void delayMicroseconds(uint16_t us);
	void csn(int mode);
	void ce(int level);
	uint8_t spi_transfer(uint8_t tx);
	void hal_init();
};

#endif /* NRF24_RF24HALCHIBIOS_H_ */
