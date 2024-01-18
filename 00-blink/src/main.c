#include <avr/io.h>
#include <stdbool.h>

int main(void)
{
    // PD6 (pin 6) Alternate Function - OC0A (Timer/Counter0 Output Compare Match A Output)
    // PD5 (pin 5) Alternate Function - OC0B (Timer/Counter0 Output Compare Match B Output)
    DDRD |= _BV(DDD5) | _BV(DDD6);

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
    // clkIO/1 (No prescaling)
    TCCR0B &= ~_BV(CS02);
    TCCR0B &= ~_BV(CS01);
    TCCR0B |= _BV(CS00);

    // Duties
    OCR0A = 127;    // 50% duty
    OCR0B = 63;     // 25% duty

    while (true)
    {
        // NOP
    }
}
