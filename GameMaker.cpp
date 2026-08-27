// Helper file to compile .ch8 files from hexcode written here.

#include <fstream>
#include <iostream>
#include <vector>

int main() {
    // CHIP-8 program:
    //
    // 6000       V0 = 0
    // 6100       V1 = 0
    // A050       I = 0x050 (font '0')
    // D015       Draw 5-byte sprite at (V0, V1)
    //
    // 6008       V0 = 8
    // 6108       V1 = 8
    // D015       Draw '0' at (8, 8)
    //
    // 6010       V0 = 16
    // 6110       V1 = 16
    // D015       Draw '0' at (16, 16)
    //
    // 00E0       Clear screen
    //
    // 6000       V0 = 0
    // 6100       V1 = 0
    // A050       I = 0x050
    // D015       Draw '0' again

    std::vector<unsigned char> program = {
        // Draw '0' at (0, 0)
        0x60, 0x00,       // V0 = 0
        0x61, 0x00,       // V1 = 0
        0xA0, 0x50,       // I = font '0'
        0xD0, 0x15,       // Draw 0

        // Draw '0' at (8, 8)
        0x60, 0x08,
        0x61, 0x08,
        0xD0, 0x15,

        // Draw '0' at (16, 16)
        0x60, 0x10,
        0x61, 0x10,
        0xD0, 0x15,

        // Infinite loop
        //0x12, 0x18
    };

    std::ofstream file("draw_test.ch8", std::ios::binary);

    if (!file) {
        std::cerr << "Could not create ROM\n";
        return 1;
    }

    file.write(
        reinterpret_cast<const char*>(program.data()),
        program.size()
    );

    file.close();

    std::cout << "Created draw_test.ch8\n";
    return 0;
}