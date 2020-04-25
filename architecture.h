#ifndef ARCHITECTURE_H
#define ARCHITECTURE_H

#include <stdint.h>

class Chip8 {
  private:
    unsigned short stack[16];                 // Stack
    unsigned short sp;                        // Stack pointer

    unsigned char memory[4096];               // Memory (4k)
    unsigned char V[16];                      // V registers (V0-VF)

    unsigned short pc;                        // Program counter
    unsigned short opcode;                    // Current op code
    unsigned short I;                         // Index register

    unsigned char delay_timer;                // Delay timer
    unsigned char sound_timer;                // Sound timer

    void init();

    void decodeOpcode();               //helper method

  public:
    unsigned char  gfx[64 * 32];              // Graphics buffer
    unsigned char  key[16];                   // Keypad
    bool drawFlag;                      // Indicates a draw has occurred

    Chip8();
    ~Chip8();

    void emulate_cycle();           // Emulate one cycle
    bool load(const char *file_path);   // Load application
};

#endif // CHIP_8_H
