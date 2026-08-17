#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

class chip8 {
public:
	// 2 byte opcode
	unsigned short opcode;
	// 15 general use regs, 1 carry reg
	unsigned char V[16];
	// Address reg+pc
	unsigned short I;
	unsigned short pc;

	// 4KB memory
	// 0x000 - 0x1FF - Interpreter/fonts
	// 0x050 - 0x0A0 - 4x5 pixel font set
	// 0x200 - 0xFFF - Program ROM and RAM
	unsigned char memory[4096];

	// Graphics in XOR mode: if pixel turns off, VF set for collision
	// A B O
	// 0 0 0
	// 0 1 1
	// 1 0 1
	// 1 1 0

	// pixel states (64 x 32), 1 or 0
	unsigned char gfx[64 * 32];

	// hardware regs
	// when set above 0, counts down at 60Hz
	// buzzer when sound_timer nonzero. Write-only
	unsigned char delay_timer;
	unsigned char sound_timer;

	// stack + sp
	unsigned short stack[16];
	unsigned short sp;

	// keystate
	unsigned char key[16];

	void initialize();		// initialize memory
	char loadGame(char* filename);		// load program into memory
	void emulateCycle();	// emulate one cycle
	bool drawFlag();		// if flag set, update screen
	void setKeys();			// store key press
};

char chip8::initialize(){
	pc = 0x200;
	opcode = 0;
	I = 0;
	sp = 0;

	fill(gfx.begin(), gfx.end(), 0);
	fill(stack.begin(), stack.end(), 0);
	fill(V.begin(), V.end(), 0);
	fill(memory.begin(), memory.end(), 0);

	// Load fontset
	copy(chip8_fontset.begin(), chip8_fontset.end(), memory.begin()+80);

	// Reset timers
	delay_timer = 0;
	sound_timer = 0;
}

char chip8::loadGame(char* filename){
	// Load program
	ifstream file(filename, ios::in | ios::binary | ios::ate);
	if(!file){
		cout << "Error opening program for reading!";
		return -1;
	}

	ifstream::pos_type size = file.tellg();
	if (size > (4096 - 0x200)) {
    	cout << "ROM too large to fit in memory!";
    	return -1;
	}

	file.seekg(0, ios::beg);
	file.read(reinterpret_cast<char*>(memory+0x200), size);
	file.close();
	return 0;
}

void chip8::emulateCycle(){
	// FDE opcode
	// Fetch opcode by ORing adjacent bytes
	opcode = (memory[pc] << 8) | memory[pc + 1];
	// Decode


	// Update timers
}

unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
