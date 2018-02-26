#include "io_relay.h"

void ICACHE_FLASH_ATTR io_relay_init() {
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
  GPIO_OUTPUT_SET(GPIO_ID_PIN(12), 0);
}

void ICACHE_FLASH_ATTR io_relay_on() {
  GPIO_OUTPUT_SET(GPIO_ID_PIN(12), 1);
}

void ICACHE_FLASH_ATTR io_relay_off() {
  GPIO_OUTPUT_SET(GPIO_ID_PIN(12), 0);
}
