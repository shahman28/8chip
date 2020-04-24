
#ifndef ARCHITECTURE_H
#define ARCHITECTURE_H

  class architecture(){

    architecture(){

    }
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

    // initializes registers and memory
    void initialize (){


    }
    //runs the emulation cyle
    void emulateCycle(){
      opcode = memory[pc] << 8 | memory[pc+1]
      // Decode Opcode
      // Execute Opcode

      // Update timers
    }

    void loadGame(String s){
      //choose the game that will be played
    }

    //if set draw graphics
    boolean drawFlag(){

    }

    void setKeys(){
      //store input
    }

    void decodeOpcode(unsigned short i){
      if (i ==  )

    }


  };
