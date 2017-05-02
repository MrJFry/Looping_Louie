//-----------------------------------------------------------------------------//
//                      Looping Louie upgrade Hack                             //
//                            by Jannis Ret                                    //
//                 Version 0.2.5 -not released- 17.03.2017                       //
//      for use with Hardware: LoopingLouie,ArduinoNanoV3,SSD1306 & L293D      //
//-----------------------------------------------------------------------------//


/*include Libraries and stuff for LCD*******************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
#define CHARWIDTH           5
#define CHARHEIGHT          8
/*******************************************************************************/

// pin declaration
const int analogInPin = A0;  // Analog input pin for potentiometer
const int direction1 = 5; // motor output 1
const int direction2 = 6; // motor output 2
const byte interruptPin = 2;

// variable declaration
int sensorValue = 0;        // value read from the pot
int sensorValue1 = 0;       // calculated value
int outputValue = 0;        // Output value
int gamemode = 0;          // Gamemode 0= Pause, 1= manual speed 2= random
int rantime = 0;


/***************************SETUP*************************************************************************************************************************/
void setup() {
  Serial.begin(9600);
  initDisplay();
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), changemode, LOW);  

}
/***************************LOOP************************************************/
void loop() {
  if (gamemode == 0) {
    gamepause();
  }
  else if (gamemode == 2) {
    SPEEDpot();
    motordrive();
  }
  else if (gamemode == 1) {
    randomspeed();
    motordrive();
  }
}
/***************************Functions*******************************************/
void dispSet(int X, int Y, int color, int Texsize) {
  display.setTextSize(Texsize);
  display.setTextColor(color);
  display.setCursor(X, Y);
}

void initDisplay(void) {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  dispSet(0, 0, WHITE, 2);
  display.println("Looping   Louie");
  dispSet(64, 23, WHITE, 1);
  display.println("V0.2");
  dispSet(0, 55, WHITE, 1);
  display.println("hacked by Jannis ;)");
  display.display();
  delay(1500);
  display.clearDisplay();
}

void manSpeedFrame(void) {
  dispSet(0, 0, WHITE, 2);
  display.println("Man. Speed");
  dispSet(0, 35, WHITE, 1);
  display.println("current speed:");
  dispSet(36, 56, WHITE, 1);
  display.println("%");
}

void ranSpeedFrame(void) {
  dispSet(0, 0, WHITE, 2);
  display.println("random    Speed");
  dispSet(0, 35, WHITE, 1);
  display.println("speed:");
  dispSet(36, 56, WHITE, 1);
  display.println("%");
  dispSet(64, 35, WHITE, 1);
  display.println("for:");
  dispSet(110, 56, WHITE, 1);
  display.println("sec");
}

void SPEEDpot(void) {
 // sensorValue = analogRead(analogInPin);
 //  sensorValue = 1025;
 // sensorValue1 = (sensorValue / 10.24);
 // outputValue = (sensorValue);
  analogWrite(direction1, LOW);
  analogWrite(direction2, 255);
  display.clearDisplay();
  manSpeedFrame();
  dispSet(0, 50, WHITE, 2);
  display.println("100");
  display.display();  
  Serial.println("SPEED");
  Serial.println(outputValue);
}

void motordrive(void) {
  analogWrite(direction1, LOW);
  analogWrite(direction2, outputValue);
}

void changemode(void) {
  switch (gamemode) {
    case 0:
      gamemode = 1;
      delay(100);
      break;
    case 1:
      gamemode = 2;
      delay(100);
      break;
    case 2:
      gamemode = 0;
      rantime = 0;
      delay(100);
      break;
  }
  Serial.println(gamemode);
  delay(10000);

}

void gamepause(void) {
  display.clearDisplay();
  dispSet(0, 5, WHITE, 3);
  display.println(" Pause");
  dispSet(0, 55, WHITE, 1);
  display.println("Press button to start");
  display.display();
  delay(500);
  Serial.println("Pause");
  display.clearDisplay();
  dispSet(0, 55, WHITE, 1);
  display.println("Press button to start");
  display.display();
  delay(500);
  analogWrite(direction1, LOW);
  analogWrite(direction2, 0);
}

void randomspeed(void) {
  rantime = random(250, 10000);
  sensorValue = random(70, 255);
  outputValue = sensorValue;
  sensorValue1 = (sensorValue / 2.55);
  display.clearDisplay();
  ranSpeedFrame();
  dispSet(0, 50, WHITE, 2);
  display.println(sensorValue1);
  dispSet(85, 50, WHITE, 2);
  display.println((rantime/1000));
  display.display();  
  Serial.println("SPEED(Random)");
  Serial.println(outputValue);
  delay(rantime);
}

void wait(int ms) {
 for (int i=0; i<=ms; i++);
 
}



