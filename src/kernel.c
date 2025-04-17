#include <uart.h> 

// kernel entry point, called from boot.S
void kernel_main(void) {
    uart_puts("welcome to wonderland\r\n");

    while (1) {
        //cpu hangs here
    }
}
