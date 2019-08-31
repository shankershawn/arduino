#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

const int csn_pin = 9;
const int ce_pin = 10;
const int joystick_x_pin = A0;
int joystick_x_val = 0;
const int joystick_y_pin = A1;
int joystick_y_val = 0;
const int joystick_switch_pin = 8;
int joystick_switch_val = 0;
int dataArray[3];
int joystick_x_old_val = 0;

// SCK = 13
// MOSI = 11
// MISO = 12

RF24 radio(ce_pin,csn_pin);
const byte address[][6] = {"frdv4","ed32w"};

void setup() {
  Serial.begin(9600);
  pinMode(joystick_switch_pin, INPUT);
  digitalWrite(joystick_switch_pin, HIGH);
  dataArray[0] = dataArray[1] = dataArray[2] = 0;
  radioSetup();
  Serial.println("Setup complete.");
}

void radioSetup(){
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  Serial.println("Radio setup complete.");
}

void loop() {
  if(dataArray[0] > 0){
    joystick_x_val = analogRead(joystick_x_pin);
    if(joystick_x_val > joystick_x_old_val){
      joystick_x_old_val += 5;
    }else if(joystick_x_val < joystick_x_old_val){
      joystick_x_old_val -= 5;
    }
    dataArray[0] = joystick_x_old_val;
  }else{
    dataArray[0] = analogRead(joystick_x_pin);
    joystick_x_old_val = 0;
  }
  dataArray[1] = analogRead(joystick_y_pin);
  dataArray[2] = digitalRead(joystick_switch_pin);
  transmitFlightParams();
  receiveVoltage();
}

void transmitFlightParams(){
  Serial.println(String(joystick_x_val) + "-" + String(dataArray[0]) + "-" + String(dataArray[1]) + "-" + String(dataArray[2]));
  radio.write(&dataArray, sizeof(dataArray));
  delay(5);
}

void receiveVoltage(){
  
}
