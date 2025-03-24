/**
 * Printf redirection module implementation file
 */

 #include <Arduino.h>
 #include <stdio.h>
 #include <stdarg.h>
 #include "printf_redirect.h"
 
 /**
  * Initialize printf redirection to Serial
  */
 void init_printf_redirect(void) {
   // Redirect stdout to Serial
   fdevopen(&serial_putchar, NULL);
 }
 
 /**
  * Implementation of putchar for printf
  */
 int serial_putchar(char c, FILE *stream) {
   Serial.write(c);
   return 0;
 }
 
 /**
  * Custom implementation for printf that redirects to Serial
  * This is a backup method if fdevopen doesn't work
  */
 int serial_printf(const char *format, ...) {
   char buf[128]; // Buffer for formatted string
   va_list args;
   
   va_start(args, format);
   vsnprintf(buf, sizeof(buf), format, args);
   va_end(args);
   
   Serial.print(buf);
   return strlen(buf);
 }