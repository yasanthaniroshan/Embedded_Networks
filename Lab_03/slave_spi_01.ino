

#include<SPI.h>

volatile boolean received;

volatile byte Slavereceived, Slavesend;
int x;
void setup()

{

  Serial.begin(9600);
  pinMode(MISO, OUTPUT);                  //Sets MISO as OUTPUT (Have to Send data to Master IN
  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received = false;
  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
}


ISR (SPI_STC_vect)                        //Inerrrput routine function
{
  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True
}


void loop()
{
  if (received)                           //Logic to SET LED ON OR OFF depending upon the value recerived from master
  {
    Serial.println(Slavereceived);
    Slavesend=Slavereceived - 1;
    if(Slavesend < 0)
    {
      Slavesend = 0;
    }
    SPDR = Slavesend;  
  }
}

