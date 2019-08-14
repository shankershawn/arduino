#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

const int csn_pin = 9;
const int ce_pin = 10;
const int main_motor_pin = 8;
const int cell1_pin = A1;
const int cell2_pin = A2;
const int cell3_pin = A3;

// SCK = 13
// MOSI = 11
// MISO = 12

RF24 radio(ce_pin,csn_pin);
Servo mainMotor;
const byte address[][6] = {"frdv4","ed32w"};
int dataArray[3];
bool changeFlag = false;
int motorRunStatus = -1;

void setup() {
  Serial.begin(9600);
  radioSetup();
  mainMotorSetup();
  Serial.println("Setup complete.");
}

void mainMotorSetup(){
  mainMotor.attach(8);
  pinMode(main_motor_pin, OUTPUT);
  Serial.println("Main Motor setup complete.");
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
  }
}

void transmitVoltage(){
  
}

void updateMainMotorParams(){
  if(dataArray[2] == 0 && changeFlag){
    motorRunStatus *= -1;
    changeFlag = false;
  }else if(dataArray[2] == 1){
    changeFlag = true;
  }
  if(motorRunStatus == 1){
    mainMotor.write(map(dataArray[0], 0, 1023, 100, 180));
  }else{
    mainMotor.write(0);
  }
}
