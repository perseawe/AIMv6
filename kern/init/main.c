#include <drivers/serial/uart.h>

int start_kernel(void)
{
	uart_spin_puts("Hello from kernel!\r\n");
	while(1);
}

