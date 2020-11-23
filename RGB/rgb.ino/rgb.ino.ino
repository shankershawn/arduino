const int red_pin = 3;
const int green_pin = 5;
const int blue_pin = 6;

int red_val = 0;
int green_val = 0;
int blue_val = 0;
bool redIncFlag = true;
bool blueIncFlag = true;
bool greenIncFlag = true;

const int switch_pin = 8;
const int x_pin = A0;
const int y_pin = A1;
int switch_val = 0;

int runStatus = -1;
bool changeFlag = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(switch_pin, INPUT);
  digitalWrite(switch_pin, HIGH);
  rgbLed(0,0,0);
  Serial.println("Setup complete.");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(runStatus == 1){
    /*rgbLed(255,0,0);
    delay(100);
    rgbLed(0, 255, 0);
    delay(100);
    rgbLed(0, 0, 255);
    delay(100);*/

    if(redIncFlag){
      red_val += 2;
    }else{
      red_val -= 1;
    }

    if(greenIncFlag){
      green_val += 3;
    }else{
      green_val -= 2;
    }

    if(blueIncFlag){
      blue_val += 4;
    }else{
      blue_val -= 3;
    }
    
    if(red_val >= 255){
      red_val = 255;
      redIncFlag = false;
    }else if(red_val <= 0){
      red_val = 0;
      redIncFlag = true;
    }
    
    if(green_val >= 255){
      green_val = 255;
      greenIncFlag = false;
    }else if(green_val <= 0){
      green_val = 0;
      greenIncFlag = true;
    }

    if(blue_val >= 255){
      blue_val = 255;
      blueIncFlag = false;
    }else if(blue_val <= 0){
      blue_val = 0;
      blueIncFlag = true;
    }
    Serial.println(String(red_val) + "-" + String(green_val) + "-" + String(blue_val));
    rgbLed(red_val, green_val, blue_val);
    
  }else{
    rgbLed(0,0,0);
  }
  
  switch_val = digitalRead(switch_pin);
  if(changeFlag && switch_val == 0){
    changeFlag = false;
    runStatus *= -1;
  }else if(switch_val == 1){
    changeFlag = true;
  }
  
}

void rgbLed(int r, int g, int b) {
   analogWrite(red_pin, 255 - r);
   analogWrite(green_pin, 255 - g);
   analogWrite(blue_pin, 255 - b);
}
