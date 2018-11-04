#include <LoRa.h>

void loRa_setup(long freq, int sf, int cs, int rst, int irq, String key) {
  encryption_setup(key);
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

String loRa_receiveMessage() {
  int messageSize = LoRa.parsePacket();
  String message;

  if (messageSize) {
    if (debug > 0) {
      Serial.println("RECEIVED: ");
    }

    while (LoRa.available()) {
      message += (char)LoRa.read();
    }
  }

  return loRa_decrypt(message);
}

String loRa_receiveMessageAndConfirm() {
  String message = loRa_receiveMessage();

  if (message.length() > 0 && message != "-FAIL-" && message != "1" && message != "0") {
    loRa_sendMessage("1");
  }

  loRa_sleep();
  return message;
}

bool loRa_receiveConfirmMessage(String message) {
  bool properMessageReceived = false;

  unsigned long entry = millis();
  while (properMessageReceived == false && millis() - entry < 2000) {
    if (loRa_receiveMessage() == message) {
      properMessageReceived = true;
    }

    delay(50);
  }

  loRa_sleep();
  return properMessageReceived;
}


void loRa_sendMessage(String message) {
  message = loRa_encrypt(message);

  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  loRa_sleep();
}

void loRa_sendMessageWithConfirm(String message) {
  loRa_sendMessage(message);
  int notReceivedCount = 0;

  if (debug > 0) {
    Serial.println("Sending message");
  }

  while (!loRa_receiveConfirmMessage("1") && notReceivedCount < 4) {
    if (debug > 0) {
      Serial.println("Retrying sending message...");
    }

    loRa_sendMessage(message);
    notReceivedCount++;
  }

  if (notReceivedCount < 4) {
    Serial.print("DONE");
  } else {
    Serial.print("FAILED");
  }
}

void loRa_sleep() {
  if (loraSleepEnabled > 0) {
    LoRa.sleep();
  }
}

