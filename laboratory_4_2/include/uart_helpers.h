#ifndef UART_HELPERS_H
#define UART_HELPERS_H

#include <Arduino.h>
#include <stdio.h>

// Setup printf to use Arduino Serial
#ifndef PRINTF_BUF_SIZE
#define PRINTF_BUF_SIZE 64
#endif

// Function to redirect printf to Serial
int uart_putchar(char c, FILE *stream);

// Function to redirect stdin to Serial
int uart_getchar(FILE *stream);

// Initialize stdio for uart
void setup_uart_stdio();

extern FILE uart_output;
extern FILE uart_input;

#endif // UART_HELPERS_H 