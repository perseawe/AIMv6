#define PRELOAD_VECTOR_BASE 0x1ff00000

void (*uart_spin_puts)(const char *) = (void *)(PRELOAD_VECTOR_BASE + 0x0C);
void (*reachELF)() = (void *)(PRELOAD_VECTOR_BASE + 0x10);

// before this, MBR already lay in mem 0x100000
void mbr(void)
{
	uart_spin_puts("Bootloader is running!\r\n");
	reachELF();

spin:
	while (1);
}

