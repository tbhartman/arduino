
// arduino pins
const int D2 = 2;
const int D3 = 3;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;

const int BUTTON = D2;
const int LED = D3;

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

bool button = false;
int name = 0;
int lastWrite = 0;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  u8g2.begin();
  /*
  digitalWrite(RED, HIGH);
  delay(1000);
  digitalWrite(GREEN, HIGH);
  delay(1000);
  digitalWrite(BLUE, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  */
}

void loop() {
  bool buttonFlipped = false;
  switch(digitalRead(BUTTON)) {
    case LOW:
      if (!button) {
        // button pressed
        buttonFlipped = true;
      }
      break;
    case HIGH:
      if (button) {
        // button released
        buttonFlipped = true;
      }
      break;
  }
  if(buttonFlipped || millis() < 2000) {
    if (buttonFlipped) {
      button = !button;
      if (button) {
        name++;
      }
    }
    digitalWrite(LED, button || millis() < 1000 ? HIGH : LOW);
  }
  // write to screen
  if (millis() - lastWrite > 500 || lastWrite == 0 || buttonFlipped) {
    String nameStr;
    if (name > 10) {
      name = 0;
    }
    switch(name){
      case 0:
        nameStr = String("Tim");
        break;
      case 1:
        nameStr = String("Andrea");
        break;
      case 2:
        nameStr = String("Piper");
        break;
      case 3:
        nameStr = String("Ryas");
        break;
      case 4:
        nameStr = String("Kella");
        break;
      case 5:
        nameStr = String("Lilias");
        break;
      case 6:
        nameStr = String("Silas");
        break;
      case 7:
        nameStr = String("Titus");
        break;
      case 8:
        nameStr = String("Lenny");
        break;
      case 9:
        nameStr = String("Kevin");
        break;
      case 10:
        nameStr = String("Jonathon");
        break;
    }
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_6x10_mf);
      u8g2.drawStr(4,15,String("Hello " + nameStr + "!").c_str());
      String s(millis() / 1000);
      s += "s";
      u8g2.setFont(u8g2_font_5x7_mf);
      s = String("uptime: " + s );
      u8g2.drawStr(4,30,s.c_str());
      u8g2.
      lastWrite = millis();
    } while ( u8g2.nextPage() );
  }
}
