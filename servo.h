#ifdef useServo
  #include <Servo.h>
  #include <TaskScheduler.h>

  Servo servo;
  Task* stopTask;

  void servo_stop() {
    servo.write(90);
  }

  void servo_setup(Scheduler* scheduler) {
    servo.attach(2);
    servo.write(90);

    stopTask = new Task(10000, 1, servo_stop, scheduler, false);
  }

  void servo_interact(String message) {
    stopTask->disable();

    if (message == "open") {
      servo.write(180);
    }

    if (message == "close") {
      servo.write(0);
    }

    if (message == "stop") {
      servo_stop();
    } else {
      stopTask->enableDelayed();
    }
  }
#endif
