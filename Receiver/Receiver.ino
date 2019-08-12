#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

const int csn_pin = 9;
const int ce_pin = 10;

// SCK = 13
// MOSI = 11
// MISO = 12

RF24 radio(ce_pin,csn_pin);
const byte address[6] = "frdv4";
//String radioPayload = "";
int dataArray[3];

void setup() {
  Serial.begin(9600);
  radioSetup();
  Serial.println("Setup complete.");
}

void radioSetup(){
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  Serial.println("Radio setup complete.");
}

void loop() {
  receive();
}

void receive(){
  if(radio.available()){
    radio.read(&dataArray, sizeof(dataArray));
    //Serial.println(radioPayload);
    Serial.println(String(dataArray[0]) + "-" + String(dataArray[1]) + "-" + String(dataArray[2]));
  }
}
