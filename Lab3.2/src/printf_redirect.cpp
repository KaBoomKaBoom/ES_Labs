
/**
 * Printf Redirection Module Implementation (printf_redirect.cpp)
 */
#include <Arduino.h>
#include <stdio.h>
#include "printf_redirect.h"

// Static FILE object for printf redirection
static FILE serial_stdout;

/**
 * Initialize printf redirection to Serial
 */
void init_printf_redirect(void) {
  // Initialize the FILE stream for stdout
  fdev_setup_stream(&serial_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &serial_stdout;
}

/**
 * Implementation of putchar for printf
 */
int serial_putchar(char c, FILE *stream) {
  Serial.write(c);
  return c;
}