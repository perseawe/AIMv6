ENTRY(start_kernel)

MEMORY
{
	Kern (rwx) :
		ORIGIN = 2M,
		LENGTH = 10M
}

SECTIONS
{
	.text : {
		*(.text .rodata)
	}
	.data : {
		*(.data)
	}
	.bss : {
		*(.bss)
	}
}
