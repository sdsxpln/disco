#include "io_pwm.h"

uint32_t PWM_DUTY[] = { 0 };
uint32_t PWM_PINS[1][3] = { { PWMMUX, PWMFUNC, PWMNUM } };

void ICACHE_FLASH_ATTR io_pwm_initialize() {
  pwm_init(PWMPERIOD, PWM_DUTY, 1, PWM_PINS);
  pwm_start();
}

void ICACHE_FLASH_ATTR io_pwm_on(int duty) {
  pwm_set_duty(duty, PWMNUM);
  pwm_start();
}

void ICACHE_FLASH_ATTR io_pwm_off() {
  pwm_set_duty(0, PWMNUM);
  pwm_start();
}
