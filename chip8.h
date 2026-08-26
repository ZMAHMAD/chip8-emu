#include <cstdint>
#include <array>
#include <SDL3/SDL.h>

class chip8 {
public:
	// pixel states (64 x 32), 1 or 0
	std::array<unsigned char, 64*32> gfx;
	// keystate
	std::array<unsigned char, 16> key;

	bool drawFlag;		// if flag set, update screen

	void initialize();		// initialize memory
	int loadGame(char* filename);		// load program into memory
	void emulateCycle();	// emulate one cycle
	uint8_t scancodeToChip8(SDL_Scancode code);

private:
	// 2 byte opcode
	unsigned short opcode;
	// 15 general use regs, 1 carry reg
	std::array<unsigned char, 16> V;
	// Address reg+pc
	unsigned short I;
	unsigned short pc;

	// stack + sp
	std::array<unsigned char, 16> stack;
	unsigned short sp;

	// 4KB memory
	// 0x000 - 0x1FF - Interpreter/fonts
	// 0x050 - 0x0A0 - 4x5 pixel font set
	// 0x200 - 0xFFF - Program ROM and RAM
	std::array<unsigned char, 4096> memory;


	// hardware regs
	// when set above 0, counts down at 60Hz
	// buzzer when sound_timer nonzero. Write-only
	unsigned char delay_timer;
	unsigned char sound_timer;
};
