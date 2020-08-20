#pragma once
#include <stdint.h>
#define X64

#ifdef X64


inline void outb(uint16_t port, uint8_t value)
{
	asm volatile("out  dx, al"::"a"(value), "d"(port));
}
inline void outw(uint16_t port, uint16_t value)
{
	asm volatile("out  dx, ax"::"a"(value), "d"(port));
}
inline void outl(uint16_t port, uint32_t value)
{
	asm volatile("out  dx, eax"::"a"(value), "d"(port));
}
inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile("in al, dx"
		: "=a"(ret)
		: "d"(port)
		);
	return ret;
}
inline uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile ("in ax, dx"
		: "=a"(ret)
		: "d"(port));
	return ret;
}
#endif // DEBUG