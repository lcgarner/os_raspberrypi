//INPUT/OUTPUT
#include <stdint.h>

#define UART0_BASE 0x101f1000  // UART address, specific to qemu versatilePB
#define UART0_DR   (*(volatile uint32_t *)(UART0_BASE)) //pointer to uart data register

//write byte to uart (prints in terminal in qemu)
void uart_putc(unsigned char c) {
    UART0_DR = c;
}

//reads byte from uart (reads from terminal in qemu)
unsigned char uart_getc(void) {
    return UART0_DR;  
}

//sends entire string over uart 
void uart_puts(const char *s) {
    while (*s) {
        //printing one byte at a time
        uart_putc(*s++);
    }
}

//reads entire string from uart
void uart_gets(char *buffer, int max_len) {
    int i = 0;
    while (i < max_len - 1) {
        char c = uart_getc();

        //echoes character back to terminal, otherwise user can't see what they're typing
        uart_putc(c);

        //stop on newline or carriage return
        if (c == '\r' || c == '\n') {
            break;
        }

        buffer[i++] = c;
    }

    buffer[i] = '\0'; //null-terminate
}
