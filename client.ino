#include "globals.h"
#include <TaskScheduler.h>

#ifdef useServo
  #include "servo.h"
#endif

Scheduler scheduler;

void setup() {
  Serial.begin(9600);

  loRa_setup(freq, sf, cs, rst, irq, key);

  #ifdef useServo
    servo_setup(&scheduler);
  #endif
}

void loop() {
  String loRaMessage = loRa_receiveMessage();
  if (loRaMessage != "") {
    Serial.print(loRaMessage);

    if (loRaMessage != "1") {
      String message = "";
      
      #ifdef useServo
        servo_interact(loRaMessage);
        message = "1";
      #endif

      if (message != "") {
        loRa_sendMessage(message);
      }
    }
  }

  String serialMessage = "";
  if (Serial.available()) {
    serialMessage = Serial.readString();

    if (serialMessage) {
       loRa_sendMessage(serialMessage);
    }
  }

  scheduler.execute();
}

