#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include "const.hpp"
#include "loader.hpp"

struct Instruction {
	int opcode, funct;
	int rs,rt,rd;
	int immediate;
};

/* Memories */
extern int mem[1024];
extern Instruction inst[1024];

inline int btol(int target);  // Convertion between big/little endian.
void parse(Instruction *inst, int word);    // Parse a word(big-endian) and store into *inst.
void print_inst(const Instruction *target); // Print an instruction. (for debugging)
void load_img(Instruction *inst, int *stk, int &PC, int &num_inst, int &num_word, int &sp); // Call this function to load images.

#endif
