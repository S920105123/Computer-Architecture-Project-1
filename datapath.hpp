#ifndef DATAPATH_H
#define DATAPATH_H

#include "loader.hpp"
#include <queue>

/* Registers */
extern int reg[35], HI, LO, &PC;
extern int pre_reg[35], &pre_PC;
extern std::queue<int> change;

#endif
