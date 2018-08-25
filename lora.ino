#include <LoRa.h>

void loRa_setup(long freq, int sf, int cs, int rst, int irq) {
  LoRa.setPins(cs, rst, irq);

  if (!LoRa.begin(freq)) {
    if (debug > 0) {
      Serial.println("Starting LoRa failed!");
    }
    
    while (1);
  }

  LoRa.setSpreadingFactor(sf);
  
  loRa_sleep();
  
  if (debug > 0) {
    Serial.println("Lora Started");
  
    Serial.print("Frequency ");
    Serial.print(freq);
    Serial.print(" SF ");
    Serial.println(sf);
  }
}

String loRa_receivePacket() {
  int packetSize = LoRa.parsePacket();
  String message;
  
  if (packetSize) {
    if (debug > 0) {
      Serial.println("RECEIVED: ");
    }

    while (LoRa.available()) {
      message += (char)LoRa.read();;
    }
  }

  loRa_sleep();
  return message;
}


void loRa_sendPacket(String message) {
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  loRa_sleep();
}

void loRa_sleep() {
  if (loraSleepEnabled > 0) {
    LoRa.sleep();
  }
}

