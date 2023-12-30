#include "gpio.h"

void gpio_init(void)
{
    GPIO_SET_OUTPUT(PWM_1);
    GPIO_SET_OUTPUT(PWM_2);
    GPIO_SET_OUTPUT(SHCP);
    GPIO_SET_OUTPUT(STCP);
    GPIO_SET_OUTPUT(DATA);
    GPIO_SET_OUTPUT(OE);
}