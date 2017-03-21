#include <fstream>
#include <iostream>
#include <iomanip>
#include "const.hpp"
#include "loader.hpp"

inline int btol(int target)
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

void parse(Instruction *inst, int word)
{
	/* This function parse a binary-formatted big-endian 
	   instruction and store all the information into *inst. */
	word=btol(word);
	int mask5=0x1F, mask6=0x3F, mask16=0xFFFF, mask26=0x3FFFFFF;
	inst->opcode=(word>>26)&mask6;
	if (inst->opcode==0) {
		inst->src1=(word>>21)&mask5;
		inst->src2=(word>>16)&mask5;
		inst->dest=(word>>11)&mask5;
		inst->immediate=(word>>6)&mask5;
		inst->funct=word&mask6;
	} else {
		if (inst->opcode==J || inst->opcode==JAL) {
			inst->immediate=word&mask26;
		} else if (inst->opcode!=HALT) {
			inst->src1=(word>>21)&mask5;
			inst->dest=(word>>16)&mask5;
			inst->immediate=word&mask16;
		}
	}
}

void print_inst(const Instruction *target)
{
	/* This function print an instruction. (for debugging) */
	init_const();
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
	}
	std::cout<<std::endl;
}

void load_img(Instruction *inst, int *stk, int &PC, int &num_inst, int &sp)
{
	/* This function load iimage & dimage then reset instruction set(inst),
	   stack(stk), initial PC, number of instructions and stack pointer(sp).  */
	int word,num_word,i;
	std::ifstream d_img, i_img;
	
	d_img.open("dimage.bin",std::ios_base::in | std::ios_base::binary);
	i_img.open("iimage.bin",std::ios_base::in | std::ios_base::binary);
	
	/* Load instruction image. */
	i_img.read((char*)&PC,4);
	i_img.read((char*)&num_inst,4);
	PC=btol(PC);
	num_inst=btol(num_inst);
	for (i=0;i<PC;i++) {
		inst[i].opcode=inst[i].src1=inst[i].src2=inst[i].dest=inst[i].funct=inst[i].immediate=0;
	}
	for (;i<PC+num_inst;i++) {
		i_img.read((char*)&word,4);
		parse(&inst[i],word);
	}
	for (;i<1024;i++) {
		inst[i].opcode=inst[i].src1=inst[i].src2=inst[i].dest=inst[i].funct=inst[i].immediate=0;
	}
	
	/* Load stack data image. */
	d_img.read((char*)&sp,4);
	d_img.read((char*)&num_word,4);
	sp=btol(sp);
	num_word=btol(num_word);
	for (i=0;i<num_word;i++) {
		d_img.read((char*)&stk[i],4);
		stk[i]=btol(stk[i]);
	}
	for (;i<1024;i++) {
		stk[i]=0;
	}
	
	i_img.close();
	d_img.close();
}
