#ifndef ERROR_H
#define ERROR_H

#include <string>

enum { WRITE_ZERO, NUM_OVF, OVERWRITE_HILO, MEM_ADDR_OVF, DATA_MISALIGNED };
extern std::string err_str[5];

void init_error();
void error(int cycle,int type);

#endif
