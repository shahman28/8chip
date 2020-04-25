#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "time.h"


#include "architecture.h"
using namespace architecture;

unsigned char chip8_fontset[80] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, //0
    0x20, 0x60, 0x20, 0x20, 0x70, //1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
    0x90, 0x90, 0xF0, 0x10, 0x10, //4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
    0xF0, 0x10, 0x20, 0x40, 0x40, //7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
    0xF0, 0x90, 0xF0, 0x90, 0x90, //A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
    0xF0, 0x80, 0x80, 0x80, 0xF0, //C
    0xE0, 0x90, 0x90, 0x90, 0xE0, //D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
    0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

architecture::architecture(){}
architecture::~architecture() {}

void init(){
  pc = 0x200;
  opcode = 0;
  I = 0;
  sp = 0;

  for (int i = 0; i < 2048; ++i){
    gfx[i] = 0;
  }

  for (int i = 0; i < 16; ++i){
    stack[i] = 0;
    V[i] = 0;
    key[i] = 0;
  }

  for (int i = 0; i < 4096; ++i){
    memory[i] = 0;
  }
  for(int i = 0; i < 80; ++i)
    memory[i] = chip8_fontset[i];

  delay_timer = 0;
  sound_timer = 0;
}
//took help from James Grffin on file buffer
bool load(const char *file_path){
  init();

  FILE *rom = fopen(file_path, "rb");
  // if the file is not valid return an error
  if (rom == NULL){
    std::cerr << "ROM NOT FOUND";
    return false;
  }
  //find rom size and save file into buffer
  rom = fopen(file_path, 0, SEEK_END);
  unsigned long rom_size = (unsigned long)ftell(f);
  char* rom_buffer = char* malloc(sizeof(char) * rom_size);

  if (rom_buffer == NULL){
    std::cerr << "Failed to Read ROM" << "\n";
    return false;
  }

  if ((4096 - 512) > rom_size){
    for (int i = 0; i < rom_size; ++i){
      memory[i+512] = (unsigned char)rom_buffer[i];
    }
  }
  else{
    std::std::cerr << "ROM TOO LARGE FOR MEMORY" << '\n';
    return false
  }



  fclose(f);
  free(rom_buffer);


  void emulate_cycle(){
    //Fetch opcode
    opcode = memory[pc] << 8 | memory[pc+1];

  }

  void decodeOpcode(){
    
  }







}
