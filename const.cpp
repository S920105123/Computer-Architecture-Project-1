#include "const.h"
//#define CONST_TEST // Enable debug mode

void init_const()
{
	/* This function initialize inst_str with corresponding instructions' name. */
	for (int i=0;i<256;i++) {
		inst_str_r[i] = inst_str[i] = (char*)"undefined";
	}
	
	/* R-format */
	inst_str_r[ADD]=(char*)"add";
	inst_str_r[ADDU]=(char*)"addu";
	inst_str_r[SUB]=(char*)"sub";
	inst_str_r[AND]=(char*)"and";
	inst_str_r[OR]=(char*)"or";
	inst_str_r[XOR]=(char*)"xor";
	inst_str_r[NOR]=(char*)"nor";
	inst_str_r[NAND]=(char*)"nand";
	inst_str_r[SLT]=(char*)"slt";
	inst_str_r[SLL]=(char*)"sll";
    inst_str_r[SRL]=(char*)"srl";
    inst_str_r[SRA]=(char*)"sra";
    inst_str_r[JR]=(char*)"jr";
    inst_str_r[MULT]=(char*)"mult";
    inst_str_r[MULTU]=(char*)"multu";
    inst_str_r[MFHI]=(char*)"mfhi";
    inst_str_r[MFLO]=(char*)"mflo";
    
    /* Others */
    inst_str[ADDI]=(char*)"addi";
    inst_str[ADDU]=(char*)"addu";
    inst_str[LW]=(char*)"lw";
    inst_str[LH]=(char*)"lu";
    inst_str[LHU]=(char*)"lhu";
    inst_str[LB]=(char*)"lb";
    inst_str[LBU]=(char*)"lbu";
    inst_str[SW]=(char*)"sw";
    inst_str[SH]=(char*)"sh";
    inst_str[SB]=(char*)"sb";
    inst_str[LUI]=(char*)"lui";
    inst_str[ANDI]=(char*)"andi";
    inst_str[ORI]=(char*)"ori";
    inst_str[NORI]=(char*)"nori";
    inst_str[SLTI]=(char*)"slti";
    inst_str[BEQ]=(char*)"beq";
    inst_str[BNE]=(char*)"bne";
    inst_str[BGTZ]=(char*)"bgtz";
    inst_str[J]=(char*)"j";
    inst_str[JAL]=(char*)"jal";
    inst_str[HALT]=(char*)"halt";
}

#ifdef CONST_TEST
int main() {
	init_const();
	for (int i=0;i<256;i++) {
		std::cout<<inst_str_r[i]<<' '<<inst_str[i]<<"\n";
	}
}
#endif
