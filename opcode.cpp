#include <iostream>

using namespace std;


int main(){

  unsigned short opcode;
  unsigned short memory[4096];
  unsigned short I;
  unsigned short pc;
  //register position
  unsigned char V[16];
  //pixel display
  unsigned char gfx[64*32];
  unsigned char delay_timer;
  unsigned char sound_timer;

  //stack position
  unsigned short stack[16];
  unsigned short sp;

  //input
  unsigned char Key[16];

}
