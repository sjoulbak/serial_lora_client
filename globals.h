#ifndef GLOBALS_H
  #define GLOBALS_H

  int debug=1; // 0 is off, 1 is on

  #define useServo // comment to not use the servo part

  // LoRa settings
  long freq=8681E5;
  int sf=9;

  // LoRa pins
  int cs=16;
  int rst=17;
  int irq=15;

  // LoRa sleepmode enabled: 0 is off, 1 is on
  int loraSleepEnabled=0;

  // key
  String key = "secret";
#endif

