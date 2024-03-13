#include <Arduino.h>

#define LED_PIN 5
#define GIE_bit 7
#define CS12 2
#define CS11 1
#define CS10 0
#define OCF1A 1

void delay_ms(int time)
{
    TCNT1 = 0;
    int i = 0;
    while (i < time)
    {
        if (TIFR1 & (1 << OCF1A))
        {
            i++;
            TCNT1 = 0;
            TIFR1 |= 1 << OCF1A;
        }
    }
    TCNT1 = 0;
}

int main()
{
    TCCR1B |= (1 << CS10) + (1 << CS11);
    OCR1A = 250;
    DDRB |= 1 << LED_PIN;
    while (true)
    {
        PORTB |= 1 << LED_PIN;
        delay_ms(1000);
        PORTB = 0;
        delay_ms(500);
    }
}