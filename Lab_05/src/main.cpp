#include <Arduino.h>

#define LED_PIN 5
#define GIE_bit 7
#define CS12 2
#define CS11 1
#define CS10 0
#define OCF1A 1
#define BUAD 9600

void initializeSerial(unsigned long buadrate)
{
    UBRR0 = (F_CPU / 16 / buadrate) - 1;
    UCSR0B |= (1 << TXEN0);
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}
void serialPrintChar(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void serialPrintInt(int number)
{
    if (number >= 0 && number < 10)
    {
        serialPrintChar(number + 48);
        return;
    }
    serialPrintInt(number / 10);
    serialPrintChar((number % 10 + 48));
}

void serialPrintLn(int number)
{
    serialPrintInt(number);
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = '\n';
}

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
    initializeSerial(BUAD);
    int counter = 0;
    while (true)
    {
       if (counter % 5 == 0)
       {
        serialPrintLn(counter);
       }
        counter++;
        delay_ms(20);
    }
}