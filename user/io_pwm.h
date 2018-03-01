#ifndef __H_IO_PWM__
#define __H_IO_PWM__
#include "ets_sys.h"
#include "pwm.h"

#define PWMFUNC FUNC_GPIO4
#define PWMMUX PERIPHS_IO_MUX_GPIO4_U
#define PWMNUM 4//16 // Also named D8 on weemos d1 mini
#define PWMPERIOD 1000

void ICACHE_FLASH_ATTR io_pwm_initialize();
void ICACHE_FLASH_ATTR io_pwm_on(int duty);
void ICACHE_FLASH_ATTR io_pwm_on_with_percentage(int percentage);
void ICACHE_FLASH_ATTR io_pwm_off();
#endif
