// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

byte x = 0;

void loop() {
  Serial.println("Starting transmission");
  Wire.beginTransmission(4); // transmit to device #8
//  Wire.write("x is ");// sends five bytes
  Serial.println("x is " + String(x));
  Wire.write(x);              // sends one byte
  Serial.println("End Trabsmission");
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
}
