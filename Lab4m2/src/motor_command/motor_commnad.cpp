#include "motor_command.h"
#include <string.h>

CommandParser::CommandParser(MotorControl& control) : _motor(control) {}

void CommandParser::handleSerialCommand() {
  static char cmd[32]; // buffer comenzi
  if (Serial.available()) {
    scanf("%31s", cmd);

    if (strcmp(cmd, "motor") == 0) {
      scanf("%31s", cmd); // următorul cuvânt

      if (strcmp(cmd, "set") == 0) {
        int val;
        scanf("%d", &val);
        _motor.setPower(val);
      } else if (strcmp(cmd, "stop") == 0) {
        _motor.stop();
      } else if (strcmp(cmd, "max") == 0) {
        bool dir = _motor.getDirection();
        _motor.setPower(dir ? 100 : -100);
      } else if (strcmp(cmd, "inc") == 0) {
        int current = _motor.getPower();
        if (abs(current) >= 100) {
          printf("Viteza maximă atinsă\r\n");
        } else {
          _motor.increment(_motor.getDirection() ? 10 : -10);
        }
      } else if (strcmp(cmd, "dec") == 0) {
        int current = _motor.getPower();
        if (current == 0) {
          printf("Motorul este deja oprit\r\n");
        } else {
          _motor.increment(_motor.getDirection() ? -10 : 10);
        }
      } else {
        printf("Comandă invalidă după 'motor'.\n");
      }
    } else {
      printf("Comandă necunoscută: %s\n", cmd);
    }
  }
}
