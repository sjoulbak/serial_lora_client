#include "globals.h"

void setup() {
  Serial.begin(9600); 
  loRa_setup(freq, sf, cs, rst, irq);
}

void loop() {
  String loRaMessage = loRa_receivePacket();
  if (loRaMessage) {
    Serial.print(loRaMessage);
  }

  String serialMessage = "";
  if (Serial.available()) {
    serialMessage = Serial.readString();

    if (serialMessage) {
      loRa_sendPacket(serialMessage);
    }
  }  
}

