#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

const int csn_pin = 9;
const int ce_pin = 10;
const int main_motor_pin = 8;

// SCK = 13
// MOSI = 11
// MISO = 12

RF24 radio(ce_pin,csn_pin);
Servo mainMotor;
const byte address[][6] = {"frdv4","ed32w"};
int dataArray[3];

void setup() {
  Serial.begin(9600);
  radioSetup();
  mainMotor.attach(8,1000, 2000);
  pinMode(main_motor_pin, OUTPUT);
  Serial.println("Setup complete.");
}

void radioSetup(){
  radio.begin();
  radio.openReadingPipe(0, address[0]);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  Serial.println("Radio setup complete.");
}

void loop() {
  receiveFlightParams();
  transmitVoltage();
  updateMainMotorParams();
}

void receiveFlightParams(){
  if(radio.available()){
    radio.read(&dataArray, sizeof(dataArray));
    Serial.println(String(dataArray[0]) + "-" + String(dataArray[1]) + "-" + String(dataArray[2]));
  }
}

void transmitVoltage(){
  
}

void updateMainMotorParams(){
  mainMotor.write(map(dataArray[0], 0, 1023, 0, 180));
}
