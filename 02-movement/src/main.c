#define F_CPU (16000000UL)

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/motors.h"

int main(void)
{
    gpio_init();
    motors_init();

    set_speed(250);

    while (true)
    {
        set_direction(92);
        _delay_ms(2000);

        set_direction(0);
        _delay_ms(2000);
    }
}
