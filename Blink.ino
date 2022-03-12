

struct A
{
  A(){
    a = 1000;
  }
  void blink(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(a);
    digitalWrite(LED_BUILTIN, LOW);
    delay(a);
    a -= 10;
    if( a < 10 ) {
      a = 1000;
    }
  }
  int a;
};

static A a;



int ledState = LOW;                       //ledState used to set the LED
unsigned long previousMillisInfo = 0;     //will store last time Wi-Fi information was updated
unsigned long previousMillisLED = 0;      // will store the last time LED was updated
const int intervalInfo = 5000;            // interval at which to update the board information

void blinkLed(int duration = 500, int delayms = 500, int count = 1)
{
  for (size_t i = 0; i < count; i++)
  {
    if ( i > 0 ) delay(delayms);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(duration);
    digitalWrite(LED_BUILTIN, LOW);
  }
}



int nextNetworkCheck = 0;




/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/b0c8d0b4-a526-4703-b9ee-6752ab706c06 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  bool test;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

// #include "thingProperties.h"

bool light = false;
int next = 0;
int periodOff = 900;
int periodOn  = 100;

int sevenSegmentCounter = 0;
int sevenSegmentSecondCount = 0;
bool sevenSegmentButton = false;
bool sevenSegmentButtonSetting = false;

const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;
const int H = 9;
const int BUTTON = 10;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  set7(-1);
  // blinkLed(200,200,5);
}

void set7(int value) {
  if (value < 0) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    return;
  }
  switch(value % 10) {
    case 0:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    case 1:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 2:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    case 3:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    case 4:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 5:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 6:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 7:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 8:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 9:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
  }
}

void loop() {
  delay(2);
  int current = millis();
  if (current > next) {
    next += light ? periodOff : periodOn;
    digitalWrite(H, light ? LOW : HIGH);
    light = !light;
  }

  int currentSeconds = current / 1000;
  switch(digitalRead(BUTTON)) {
    case LOW:
      if(!sevenSegmentButton) {
        sevenSegmentButtonSetting = !sevenSegmentButtonSetting;
      }
      sevenSegmentButton = true;
      break;
    case HIGH:
      sevenSegmentButton = false;
      break;
  }

  if( sevenSegmentButtonSetting && currentSeconds != sevenSegmentSecondCount) {
    sevenSegmentSecondCount = currentSeconds;
    set7(sevenSegmentSecondCount);
  } else if (!sevenSegmentButtonSetting) {
    sevenSegmentSecondCount = 0;
    set7(-1);
  }

  /*
  ArduinoCloud.update();
  // Your code here 
  delay(1000);

  if (test) {
    blinkLed(1000, 500, 3);
  } else if ( nextNetworkCheck < millis())
  {
    if (ArduinoCloud.connected() > 0 ) {
      blinkLed(300);
    } else {
      blinkLed(200, 200, 4);
    }
    nextNetworkCheck += 10000;
  }
  */
  
}

/*
  Since Test is READ_WRITE variable, onTestChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTestChange()  {
  // Add your code here to act upon Test change
}
