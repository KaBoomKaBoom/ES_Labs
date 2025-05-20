#include "srv_serial_stdio.h"

static FILE serial_stdout;
static FILE serial_stdin;

static int serial_putchar(char c, FILE* stream) {
  Serial.write(c);
  return c;
}

static int serial_getchar(FILE* stream) {
  while (!Serial.available());
  return Serial.read();
}

void srvSerialSetup() {
  Serial.begin(9600);
  while (!Serial);
  
  fdev_setup_stream(&serial_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &serial_stdout;
  
  fdev_setup_stream(&serial_stdin, NULL, serial_getchar, _FDEV_SETUP_READ);
  stdin = &serial_stdin;
}