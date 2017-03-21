#ifndef DATAPATH_H
#define DATAPATH_H

#include "loader.hpp"

/* Memories */
int stack[1024];
Instruction inst[1024];

/* Registers */
int PC,HI,LO,reg[32],&sp=reg[29];

#endif
