#include <fstream>
#include <iostream>
#include "const.h"
#include "decoder.h"
#define DECODER_TEST  // Enable debug mode.

static Instruction inst;

int ltob(int target)
{
	/* This function conducts the convertion between
	   big-endian numbers and little-endian numbers. */
	char *bytes=(char*)&target, temp;
	temp=bytes[0];
	bytes[0]=bytes[3];
	bytes[3]=temp;
	temp=bytes[1];
	bytes[1]=bytes[2];
	bytes[2]=temp;
	return *(int*)bytes;
}

const Instruction* parse(int word)
{
	/* This function parse a binary-formatted instruction and store its
	   operators/operands into struct "inst" then return its address. */
	int mask5=0x1F, mask6=0x3F, mask16=0xFFFF, mask26=0x3FFFFFF;
	inst.opcode=word>>26;
	if (inst.opcode==0) {
		inst.src1=(word>>21)&mask5;
		inst.src2=(word>>16)&mask5;
		inst.dest=(word>>11)&mask5;
		inst.immediate=(word>>6)&mask5;
		inst.funct=word&mask6;
	} else {
		if (inst.opcode==J || inst.opcode==JAL) {
			inst.immediate=word&mask26;
		} else if (inst.opcode!=HALT) {
			inst.src1=(word>>21)&mask5;
			inst.dest=(word>>16)&mask5;
			inst.immediate=word&mask16;
		}
	}
	return &inst;
}

void print_inst(const Instruction *target)
{
	if (target->opcode==0) {
		std::cout<<inst_str_r[target->funct];
		std::cout<<" "<<target->dest<<" "<<target->src1<<" "<<target->src2;
	} else {
		std::cout<<inst_str[target->opcode];
		if (target->opcode==J || target->opcode==JAL) {
			std::cout<<" "<<target->immediate;
		} else if (target->opcode!=HALT) {
			std::cout<<" "<<target->dest<<" "<<target->src1<<" "<<target->immediate;
		}
		std::cout<<std::endl; 
	}
}

#ifdef DECODER_TEST
int main()
{
	int num_inst, PC_init, word;
	std::ifstream d_img, i_img;
	
	init_const();
	d_img.open("dimage.bin",std::ios_base::in | std::ios_base::binary);
	i_img.open("iimage.bin",std::ios_base::in | std::ios_base::binary);
	
	i_img.read((char*)&PC_init,4);
	i_img.read((char*)&num_inst,4);
	PC_init=ltob(PC_init);
	num_inst=ltob(num_inst);
	std::cout<<"Initial value of PC = "<<PC_init<<std::endl;
	std::cout<<"Number of instructions = "<<num_inst<<std::endl;
	for (int i=0;i<num_inst;i++) {
		i_img.read((char*)&word,4);
		print_inst(parse(word));
	}
	i_img.close();
	d_img.close();
}
#endif
