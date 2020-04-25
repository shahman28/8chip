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
    decodeOpcode(opcode);

  }

  void decodeOpcode(unsigned short opcode){
    //compare only the frist byte; use the binary & operator to clear second byte
    switch (opcode & 0xF000){

      case(0xA000):

        break;
      //given that the first byte is empty more searching the second is necessary
      case(0x0000):
        switch(opcode & 0x000F){

          //disp_clear
          case(0x0000):
            for (int i = 0; i < 2048; ++i){
              gfx[i] = 0;
            }
            drawFlag = true;
            pc += 2;
            break;
          //00EE return from subroutine
          case (0x000E):
            --sp;
            pc = stack[sp];
            pc += 2;
            break;
          default:
            printf("invalid opcode");

        }
        break;
        //2NNN
        case (0x2000):
          stack[sp] = pc;
          ++sp;
          pc = opcode & 0x0FFF;
          break;
        //3XNN
        case (0x3000):
          if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)){
            pc += 4;
          }
          else{
            pc += 2;
          }
          break;


        //4XNN
        case (0x4000):
          if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)){
            pc += 4;
          }
          else{
            pc += 2;
          }
        break;

        //5XY0
        case (0x5000):
        if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
              pc += 4;
          else
              pc += 2;
          break;
        //6XNN
        case (0x6000):
          V[(opcode 7 0x0F00) >> 8] = opcode & 0x00FF;
          pc += 2;
          break;
        //7XNN
        case (0x7000):
          V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
          pc += 2;
          break;
        //there are multiple bytes that start with 8
        case (0x8000):
          switch(opcode & 0x000F){

            case (0x0000):
              V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4]
              pc += 2;
              break;
            case (0x0001):
              (V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4]);
              pc += 2;
              break;
            case (0x0002):
              (V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4]);
              pc += 2;
              break;
            case (0x0003):
              (V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4]);
              pc += 2;
              break;
            case (0x0004):
              (V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4]);
              if
              pc += 2;
              break;

          }



      default:
        printf("unknown opcode\n", );
    }

  }







}
