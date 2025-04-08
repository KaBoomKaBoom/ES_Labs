#include "uart_helpers.h"

// Setup FILE streams for stdin and stdout
FILE uart_output;
FILE uart_input;

// Function to redirect printf to Serial
int uart_putchar(char c, FILE *stream) {
  Serial.write(c);
  return 0;
}

// Function to redirect stdin to Serial
int uart_getchar(FILE *stream) {
  while (!Serial.available());
  return Serial.read();
}

void setup_uart_stdio() {
  // Initialize stdio
  fdev_setup_stream(&uart_output, uart_putchar, NULL, _FDEV_SETUP_WRITE);
  fdev_setup_stream(&uart_input, NULL, uart_getchar, _FDEV_SETUP_READ);
  stdout = &uart_output;
  stdin = &uart_input;
} 