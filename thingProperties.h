// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "pw.h"
void onTestChange();

bool test;

void initProperties(){

  ArduinoCloud.addProperty(test, READWRITE, ON_CHANGE, onTestChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
