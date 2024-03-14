#include <Arduino.h>

#define LED_PIN 5
#define GIE_bit 7
#define CS12 2
#define CS11 1
#define CS10 0
#define OCF1A 1

void delay_ms(int time)
{
    TCCR1B |= (1 << CS10) + (1 << CS11);
    OCR1A = 250;
    TCNT1 = 0;
    int i = 0;
    while (i < time)
    {
        if (TIFR1 & (1 << OCF1A))
        {
            TCNT1 = 0;
            TIFR1 |= 1 << OCF1A;
            i++;
        }
    }
    TCNT1 = 0;
}
void delay_us(long time)
{
    TCCR0B |= (1 << CS00);
    OCR0A = 16;
    long i = 0;
    TCNT0 = 0;
    while (i < time)
    {
        if (TCNT0 & (1 << OCF0A))
        {
            TCNT0 = 0;
            TIFR0 |= 1 << OCF0A;
            i++;
        }
    }
    TCNT0 = 0;
}

int main()
{
    DDRB |= 1 << LED_PIN;
    while (true)
    {
        PORTB |= 1 << LED_PIN;
        delay_us(100000);
        PORTB = 0;
        delay_us(100000);
    }
}