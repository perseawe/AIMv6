#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int

// Format of an ELF executable file
// File header
typedef struct elfhdr {
    u32  magic;  // must equal ELF_MAGIC
    u8   elf[12];
    u16  type;
    u16  machine;
    u32  version;
    u32  entry;
    u32  phoff;
    u32  shoff;
    u32  flags;
    u16  ehsize;
    u16  phentsize;
    u16  phnum;
    u16  shentsize;
    u16  shnum;
    u16  shstrndx;
} elfhdr_t;
// Program section header
typedef struct proghdr {
    u32    type;
    u32    off;
    u32    vaddr;
    u32    paddr;
    u32    filesz;
    u32    memsz;
    u32    flags;
    u32    align;
} proghdr_t;

// Values for Proghdr type
#define ELF_PROG_LOAD           1

#define PRELOAD_VECTOR_BASE 0x1ff00000
#define MBR_BASE 0x100000 //1M

void (*uart_spin_puts)(const char *) = (void *)(PRELOAD_VECTOR_BASE + 0x0C);
void (*sd_dma_spin_read)(u32, u16, u32) = (void *)(PRELOAD_VECTOR_BASE + 0x10);

u32 readbytes(u32 addr, u32 bytesz) 
{
	u8 *paddr = (u8 *) addr;
	u32 res = 0;
	for (u32 i = 0; i < bytesz; ++i) {
		res += ((u32)paddr[i]) << (i*8);
	}
	return res;
}

#define size2count(x) (((x)>>9) + (((x) & 0x1ff) > 0))

// before this, MBR already lay in mem 0x100000
void mbr(void)
{
	uart_spin_puts("Boot.\r\n");
	
	u32 LBA = readbytes(MBR_BASE + 0x1b6, 4);
	u32 elf_base = 0x100200; //1.5M
	sd_dma_spin_read(elf_base, 1, LBA);
	elfhdr_t* elf_head = (elfhdr_t*) elf_base;	
	sd_dma_spin_read(0x100400, size2count(elf_head->phoff + elf_head->phentsize * elf_head->phnum), LBA);
	
	for (u32 i = 0; i < elf_head->phnum; ++i) {
		proghdr_t* prog_head = (proghdr_t*) (0x100400 + elf_head->phoff + i * elf_head->phentsize);
		if (prog_head->type == ELF_PROG_LOAD) {
			sd_dma_spin_read(prog_head->paddr, size2count(prog_head->filesz), LBA + (prog_head->off >> 9));
		}
	}

	uart_spin_puts("Boot Down.\r\n");
	
	int (*main)(void) = (int *) elf_head->entry;
	main();

spin:
	while (1);
}

