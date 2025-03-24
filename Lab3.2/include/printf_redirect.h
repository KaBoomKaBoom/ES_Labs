/**
 * Printf redirection module header file
 */

 #ifndef PRINTF_REDIRECT_H
 #define PRINTF_REDIRECT_H
 
 // Function prototypes
 void init_printf_redirect(void);
 int serial_putchar(char c, FILE *stream);
 int serial_printf(const char *format, ...);
 
 #endif /* PRINTF_REDIRECT_H */