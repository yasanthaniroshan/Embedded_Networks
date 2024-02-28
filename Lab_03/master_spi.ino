
#include<SPI.h>

#define SS1 10
#define SS2 9

void setup() {
  pinMode(SS1,OUTPUT);
  pinMode(SS2,OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);


}

void loop() {

  byte Mastersend, Mastereceive;
  for (byte data = 0 ; data < 255; data++)
  {
    digitalWrite(SS1, LOW);
    Serial.println("Started sending data");
    Mastereceive = SPI.transfer(data);
    Serial.println("Sent data : "+ String(data));
    Serial.println("recieved from slave 01 : " + String(Mastereceive));
    delay(250);
    digitalWrite(SS1, HIGH);
    data++;
    digitalWrite(SS2, LOW);
    Serial.println("Started sending data");
    Mastereceive = SPI.transfer(data);
    Serial.println("Sent data : "+ String(data));
        Serial.println("recieved from slave 02 : " + String(Mastereceive));

    delay(250);
    digitalWrite(SS2, HIGH);
  }



}