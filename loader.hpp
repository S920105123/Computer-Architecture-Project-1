#ifndef DECODER_H
#define DECODER_H

struct Instruction {
	int opcode, funct;
	int dest, src1, src2;
	int immediate;
};

#endif
