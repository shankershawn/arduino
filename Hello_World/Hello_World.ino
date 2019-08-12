#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

const int cns_pin = 7;
const int ce_pin = 8;

RF24 radio(cns_pin,ce_pin);
const byte address[6] = "shanky";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello world!!!");
  delay(1000);
}
