/*
 * RF24HAL.h
 *
 *  Created on: 4 ���. 2018 �.
 *      Author: Bogdan
 */

#ifndef NRF24_RF24HAL_H_
#define NRF24_RF24HAL_H_

class RF24HAL {
public:
	RF24HAL();
	virtual ~RF24HAL();

	uint32_t millis();
	void delay(uint16_t ms);
	void delayMicroseconds(uint16_t us);
	void csn(int mode);
	void ce(int level);
	uint8_t spi_transfer(uint8_t tx);
	void hal_init();
};

#endif /* NRF24_RF24HAL_H_ */
