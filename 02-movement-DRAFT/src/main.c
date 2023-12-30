#define F_CPU (16000000L)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

const int Forward       = 92;                               // forward
const int Backward      = 163;                              // back
const int Turn_Left     = 149;                              // left translation
const int Turn_Right    = 106;                              // Right translation 
const int Top_Left      = 20;                               // Upper left mobile
const int Bottom_Left   = 129;                              // Lower left mobile
const int Top_Right     = 72;                               // Upper right mobile
const int Bottom_Right  = 34;                               // The lower right move
const int Stop          = 0;                                // stop
const int Contrarotate  = 172;                              // Counterclockwise rotation
const int Clockwise     = 83;                               // Rotate clockwise

void shift_data(int data)
{
    for (uint8_t i = 0; i < 8; i++)  {
        if (data & 128) 
            PORTB |= _BV(DDB0);
        else
            PORTB &= ~_BV(DDB0); 

		data <<= 1;
			
		PORTD |= _BV(DDD2);
        //_delay_us(1);
		PORTD &= ~_BV(DDD2);
	}
}

void motor(int direction, int speed)
{
    PORTD &= ~_BV(DDD7);
    OCR0A = speed;
    OCR0B = speed;

    PORTD &= ~_BV(DDD4);
    shift_data(direction);
    PORTD |= _BV(DDD4);
}

int main(void)
{
    // PD7 OE Output Enable Input
    // PD6 Alternate Function - OC0A (Timer/Counter0 Output Compare Match A Output)
    // PD5 Alternate Function - OC0B (Timer/Counter0 Output Compare Match B Output)
    // PD4 STCP Storage Register Clock Input
    // PD2 SHCP Shift Register Clock Input
    DDRD |= _BV(DDD2) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7);

    // PB0 DDS Serial Data Input
    DDRB |= _BV(DDB0);

    // Waveform Generation Mode
    // Fast PWM
    TCCR0A |= _BV(WGM00) | _BV(WGM01);
    TCCR0B &= ~_BV(WGM02);

    // Compare Output Mode, Fast PWM
    // Clear OC0A on compare match, set OC0A at BOTTOM, (non-inverting mode)
    TCCR0A |= _BV(COM0A1);
    TCCR0A &= ~_BV(COM0A0);
    // Clear OC0B on compare match, set OC0B at BOTTOM, (non-inverting mode)
    TCCR0A |= _BV(COM0B1);
    TCCR0A &= ~_BV(COM0B0);

    // Clock Select
    // clkIO/64
    TCCR0B |= _BV(CS01) | _BV(CS00);

    // Duties
//    OCR0A = 250;
//    OCR0B = 250;


        // motor(Forward, 250);
        // _delay_ms(2000);

    while (true)
    {
        motor(Forward, 220);
        _delay_ms(2000);

        motor(Stop, 220);
        _delay_ms(2000);
    }
}