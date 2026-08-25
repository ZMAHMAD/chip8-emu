class chip8 {
public:
	// pixel states (64 x 32), 1 or 0
	unsigned char gfx[64 * 32];
	// keystate
	unsigned char key[16];

	bool drawFlag;		// if flag set, update screen

	char loadGame(char* filename);		// load program into memory
	void emulateCycle();	// emulate one cycle
	//void setKeys();			// store key press

private:
	// 2 byte opcode
	unsigned short opcode;
	// 15 general use regs, 1 carry reg
	unsigned char V[16];
	// Address reg+pc
	unsigned short I;
	unsigned short pc;

	// stack + sp
	unsigned short stack[16];
	unsigned short sp;

	// 4KB memory
	// 0x000 - 0x1FF - Interpreter/fonts
	// 0x050 - 0x0A0 - 4x5 pixel font set
	// 0x200 - 0xFFF - Program ROM and RAM
	unsigned char memory[4096];

	// hardware regs
	// when set above 0, counts down at 60Hz
	// buzzer when sound_timer nonzero. Write-only
	unsigned char delay_timer;
	unsigned char sound_timer;

	void initialize();		// initialize memory
};
