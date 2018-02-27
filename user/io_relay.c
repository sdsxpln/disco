#include "io_relay.h"


void ICACHE_FLASH_ATTR io_relay_init() {
  PIN_FUNC_SELECT(PINMUX, PINFUNC);
  GPIO_OUTPUT_SET(GPIO_ID_PIN(PINNUM), 0);
}

void ICACHE_FLASH_ATTR io_relay_on() {
  GPIO_OUTPUT_SET(GPIO_ID_PIN(PINNUM), 1);
}

void ICACHE_FLASH_ATTR io_relay_off() {
  GPIO_OUTPUT_SET(GPIO_ID_PIN(PINNUM), 0);
}
