/*
 * RF24HAL_ChibiosChibios.cpp
 *
 *  Created on: 26 лют. 2018 р.
 *      Author: Bogdan
 */

#include <hal.h>

#include "RF24HALChibios.h"
#include "RF24HALChibiosConfig.h"

#define RFM7x_CSN_LOW palClearPad(RFM7x_CSN_PORT, RFM7x_CSN_PAD)
#define RFM7x_CSN_HI  palSetPad(RFM7x_CSN_PORT, RFM7x_CSN_PAD)

#define RFM7x_CE_LOW  palClearPad(RFM7x_CE_PORT, RFM7x_CE_PAD)
#define RFM7x_CE_HI   palSetPad(RFM7x_CE_PORT, RFM7x_CE_PAD)

/**
 * @biref   SPI configuration strucrture.
 */
#if CH_HAL_MAJOR == 5
static const SPIConfig spiCfg = {
	NULL,       /* SPI callback.          */
	RFM7x_CSN_PORT,          /* SPI chip select port.  */
	RFM7x_CSN_PAD,                /* SPI chip select pad.   */
	0
};
#endif
#if CH_HAL_MAJOR == 6
static const SPIConfig spiCfg = {
  NULL,                  /* SPI callback.                  */
  RFM7x_CSN_PORT,                      /* SPI chip select port.          */
  RFM7x_CSN_PAD,                            /* SPI chip select pad.           */
  SPI_CR_DORD_MSB_FIRST     |   /* SPI Data order.                */
  SPI_CR_CPOL_CPHA_MODE(0)  |   /* SPI clock polarity and phase.  */
  SPI_CR_SCK_FOSC_128,          /* SPI clock.                     */
  SPI_SR_SCK_FOSC_2             /* SPI double speed bit.          */
};
#endif

RF24HAL_Chibios::RF24HAL_Chibios() {
	// TODO Auto-generated constructor stub

}

RF24HAL_Chibios::~RF24HAL_Chibios() {
	// TODO Auto-generated destructor stub
}

uint32_t RF24HAL_Chibios::millis() {
	return TIME_I2MS(osalOsGetSystemTimeX());
}

void RF24HAL_Chibios::delay(uint16_t ms) {
	osalThreadSleepMilliseconds(ms);
}

void RF24HAL_Chibios::delayMicroseconds(uint16_t us) {
	osalThreadSleepMicroseconds(us);
}

void RF24HAL_Chibios::csn(int mode)
{
  if(mode)
  {
      palSetPad(RFM7x_CSN_PORT, RFM7x_CSN_PAD);
  }
  else
  {
      palClearPad(RFM7x_CSN_PORT, RFM7x_CSN_PAD);
  }
}

void RF24HAL_Chibios::ce(int level)
{
    if(level)
    {
        palSetPad(RFM7x_CE_PORT, RFM7x_CE_PAD);
    }
    else
    {
        palClearPad(RFM7x_CE_PORT, RFM7x_CE_PAD);
    }
}

uint8_t RF24HAL_Chibios::spi_transfer(uint8_t tx) {
	uint8_t rxbuf[1];
	uint8_t txbuf[1];
	
	txbuf[0] = tx;
	spiExchange(&RFM7x_USE_SPI, 1,
	txbuf, rxbuf);

	return rxbuf[0];
}

void RF24HAL_Chibios::hal_init(){
    palSetPadMode(RFM7x_CSN_PORT, RFM7x_CSN_PAD, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(RFM7x_CE_PORT, RFM7x_CE_PAD, PAL_MODE_OUTPUT_PUSHPULL);

	/*
   * Activate the spi driver 1 by using the defined configuration.
   */
	spiStart(&RFM7x_USE_SPI, &spiCfg);
}


