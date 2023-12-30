#include "motors.h"
#include "gpio.h"
#include <avr/io.h>

static void init_fast_pwm(void);

void init_fast_pwm(void)
{
    /**
     * TODO Add proper description !!!
     */

    // TCCR0A init value 0x00
    // TCCR0B init value 0x00
    // OCR0A  init value 0x00
    // OCR0B  init value 0x00
    // Waveform Generation Mode
    // Fast PWM

    //TCCR0B &= ~_BV(WGM02);
    // Compare Output Mode, Fast PWM
    // Clear OC0A on compare match, set OC0A at BOTTOM, (non-inverting mode)
    //TCCR0A |= _BV(COM0A1);
    //TCCR0A &= ~_BV(COM0A0);
    // Clear OC0B on compare match, set OC0B at BOTTOM, (non-inverting mode)
    //TCCR0A |= _BV(COM0B1);
    //TCCR0A &= ~_BV(COM0B0);
    // Clock Select
    // clkIO/64
    // Duties
//    OCR0A = 250;
//    OCR0B = 250;

    TCCR0A |= _BV(WGM00) | _BV(WGM01) | _BV(COM0A1) | _BV(COM0B1);
    TCCR0B |= _BV(CS01) | _BV(CS00);
}

void motors_init(void)
{
    init_fast_pwm();
}

void set_speed(uint8_t speed)
{
    OCR0A = speed;
    OCR0B = speed;
}

void set_direction(uint8_t direction)
{
    //PORTD &= ~_BV(DDD4);
    GPIO_LOW(STCP);
    
    for (uint8_t i = 0; i < 8; i++)  {
        if (direction & 128) 
            //PORTB |= _BV(DDB0);
            GPIO_HIGH(DATA);
        else
            //PORTB &= ~_BV(DDB0); 
            GPIO_LOW(DATA);

		direction <<= 1;
			
		//PORTD |= _BV(DDD2);
        GPIO_HIGH(SHCP);
        //_delay_us(1);
		//PORTD &= ~_BV(DDD2);
        GPIO_LOW(SHCP);
	}

    //PORTD |= _BV(DDD4);
    GPIO_HIGH(STCP);
}