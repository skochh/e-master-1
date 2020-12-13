#ifndef Z80CPU_H_
#define Z80CPU_H_
#include "Memory.h"
#include <iostream>
#include "Z80/API/emulation/CPU/Z80.h"





unsigned char In_memo(void* context, unsigned short address);
void Out_memo(void* context, unsigned short address, unsigned char data);
unsigned char In_inpout(void* context, unsigned short address);
void Out_inpout(void* context, unsigned short address, unsigned char data);
zuint32 int_datar(void* context);

class Z80CPU
{
protected:
	AddressSpace & _bus;
	Z80 _context { };
	friend unsigned char In_memo(void* context, unsigned short address);
	friend void Out_memo(void* context, unsigned short address, unsigned char data);
	friend unsigned char In_inpout(void* context, unsigned short address);
	friend void Out_inpout(void* context, unsigned short address, unsigned char data);
	friend zuint32 int_datar(void* context);

public:
	Z80CPU(AddressSpace & bus): _bus(bus) {
		_context.read = In_memo;
		_context.write = Out_memo;
		_context.in = In_inpout;
		_context.out = Out_inpout;
		_context.context = this;
		_context.int_data = 0;
		z80_power(&_context, true);
	}

	void tick()
	{
	}
	void ticks(unsigned ticks)
	{
		z80_run(&_context, ticks);
	}

	void reset()
	{
		z80_reset(&_context);
	}

	void intr(zboolean value)
	{
		z80_int(&_context, value);
	}

	void nmi()
	{
		z80_nmi(&_context);
	}

	void save_state_sna(const char * filename);
	void load_state_sna(const char * filename);
	void load_state_z80(const char * filename);

	void load_state_sna_libspectrum(const char * filename);
	void load_state_z80_libspectrum(const char * filename);

};

#endif /* Z80CPU_H_ */
