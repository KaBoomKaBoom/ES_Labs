// stdio_redirect.cpp
#include "stdioRedirect.h"
#include <Arduino.h>

// Redirect stdout to Serial
static int uart_putchar(char c, FILE* stream) {
    Serial.write(c);
    return 0;
}

// Redirect stdin to Serial
static int uart_getchar(FILE* stream) {
    while (!Serial.available());
    return Serial.read();
}

void initializeStdio() {
    // Set up stdout and stdin
    static FILE uart_stdout;
    static FILE uart_stdin;
    
    fdev_setup_stream(&uart_stdout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream(&uart_stdin, NULL, uart_getchar, _FDEV_SETUP_READ);
    
    stdout = &uart_stdout;
    stdin = &uart_stdin;
}