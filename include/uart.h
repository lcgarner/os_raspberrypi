#ifndef UART_H
#define UART_H

//send one char
void uart_putc(unsigned char c);

//read one char
unsigned char uart_getc(void);

//send full string
void uart_puts(const char *s);

//read full string
void uart_gets(char *buffer, int max_len);

#endif
