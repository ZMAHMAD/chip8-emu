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