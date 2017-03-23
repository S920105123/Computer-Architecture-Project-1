#include "error.hpp"
#include "datapath.hpp"
#include <queue>

/* Registers */
int reg[35], HI=32, LO=33, &PC=reg[34];
int pre_reg[35], &pre_PC=pre_reg[34];
std::queue<int> change;

/* Function pointers */
void (*R_func[64])();
void (*func[64])();

/* R-format instructions */
void inst_add() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=reg[rs]+reg[rt];
	change.push(rd);
	PC=PC+4;
}
void inst_addu() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=reg[rs]+reg[rt];
	change.push(rd);
	PC=PC+4;
}
void inst_sub() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=reg[rs]-reg[rt];
	change.push(rd);
	PC=PC+4;
}
void inst_and() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=reg[rs]&reg[rt];
	change.push(rd);
	PC=PC+4;
}
void inst_or() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=reg[rs]|reg[rt];
	change.push(rd);
	PC=PC+4;
}
void inst_xor() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=reg[rs]^reg[rt];
	change.push(rd);
	PC=PC+4;
}
void inst_nor() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=~(reg[rs]|reg[rt]);
	change.push(rd);
	PC=PC+4;
}
void inst_nand() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=!(reg[rs]&reg[rt]);
	change.push(rd);
	PC=PC+4;
}
void inst_slt() {
	int rd=inst[PC].rd, rs=inst[PC].rs, rt=inst[PC].rt;
	reg[rd]=reg[rs]<reg[rt];
	change.push(rd);
	PC=PC+4;
}
void inst_sll() {
	int rd=inst[PC].rd, rt=inst[PC].rt, immediate=inst[PC].immediate;
	reg[rd]=reg[rt]<<immediate;
	change.push(rd);
	PC=PC+4;
}
void inst_srl() {
	int rd=inst[PC].rd, rt=inst[PC].rt, immediate=inst[PC].immediate;
	if (immediate!=0) {
		change.push(rd);
		reg[rd]=reg[rt]>>1;
		reg[rd]=reg[rd]&0x7FFFFFFF;
		reg[rd]=reg[rd]>>(immediate-1);
	}
	PC=PC+4;
}
void inst_sra() {
	int rd=inst[PC].rd, rt=inst[PC].rt, immediate=inst[PC].immediate;
	reg[rd]=reg[rt]>>immediate;
	change.push(rd);
	PC=PC+4;
}
void inst_jr() {
	int rs=inst[PC].rs;
	PC=reg[rs];
	PC=PC+4;
}
void inst_mult() {
	int rs=inst[PC].rs, rt=inst[PC].rt;
	long long res=reg[rs];
	res=res*reg[rt];
	reg[HI]=res&0xFFFFFFFF00000000;
	reg[LO]=res&0x00000000FFFFFFFF;
	change.push(HI);
	change.push(LO);
	PC=PC+4;
}
void inst_multu() {
	int rs=inst[PC].rs, rt=inst[PC].rt;
	unsigned long long res=(unsigned long long)reg[rs]*(unsigned long long)reg[rt];
	reg[HI]=res&0xFFFFFFFF00000000;
	reg[LO]=res&0x00000000FFFFFFFF;
	change.push(HI);
	change.push(LO);
	PC=PC+4;
}
void inst_mfhi() {
	int rd=inst[PC].rd;
	reg[rd]=reg[HI];
	change.push(rd);
	PC=PC+4;
}
void inst_mflo() {
	int rd=inst[PC].rd;
	reg[rd]=reg[LO];
	change.push(rd);
	PC=PC+4;
}

/* I-format instructions */
void inst_addi() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=reg[rs]+immediate;
	change.push(rt);
	PC=PC+4;
}
void inst_addiu() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=reg[rs]+immediate;
	change.push(rt);
	PC=PC+4;
}
void inst_lw() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=mem[reg[rs]+immediate];
	change.push(rt);
	PC=PC+4;
}
void inst_lh() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=*((short*)mem+reg[rs]+immediate);
	change.push(rt);
	PC=PC+4;
}
void inst_lhu() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=*((unsigned short*)mem+reg[rs]+immediate);
	change.push(rt);
	PC=PC+4;
}
void inst_lb() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=*((char*)mem+reg[rs]+immediate);
	change.push(rt);
	PC=PC+4;
}
void inst_lbu() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=*((unsigned char*)mem+reg[rs]+immediate);
	change.push(rt);
	PC=PC+4;
}
void inst_sw() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	mem[reg[rs]+immediate]=reg[rt];
	PC=PC+4;
}
void inst_sh() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	*((short*)mem+reg[rs]+immediate)=reg[rt]&0x0000FFFF;
	PC=PC+4;
}
void inst_sb() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	*((char*)mem+reg[rs]+immediate)=reg[rt]&0x000000FF;
	PC=PC+4;
}
void inst_lui() {
	int rt=inst[PC].rt, immediate=inst[PC].immediate;
	reg[rt]=immediate<<16;
	change.push(rt);
	PC=PC+4;
}
void inst_andi() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=reg[rs]&immediate;
	change.push(rt);
	PC=PC+4;
}
void inst_ori() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=reg[rs]|immediate;
	change.push(rt);
	PC=PC+4;
}
void inst_nori() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=~(reg[rs]|immediate);
	change.push(rt);
	PC=PC+4;
}
void inst_slti() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	reg[rt]=reg[rs]<immediate;
	change.push(rt);
	PC=PC+4;
}
void inst_beq() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	if (reg[rs]==reg[rt]) {
		PC=PC+4*immediate;
	}
	PC=PC+4;
}
void inst_bne() {
	int rt=inst[PC].rt, rs=inst[PC].rs, immediate=inst[PC].immediate;
	if (reg[rs]!=reg[rt]) {
		PC=PC+4*immediate;
	}
	PC=PC+4;
}
void inst_bgtz() {
	int rs=inst[PC].rs, immediate=inst[PC].immediate;
	if (reg[rs]>0) {
		PC=PC+4*immediate;
	}
	PC=PC+4;
}
void inst_j() {
	int immediate=inst[PC].immediate;
	PC=((PC+4)&0xF0000000)|(4*immediate);
}
void inst_jal() {
	int immediate=inst[PC].immediate;
	reg[31]=PC+4;
	PC=((PC+4)&0xF0000000)|(4*immediate);
}

void init_datapath() {
	/* Init function pointers. */
	
	/* R-format */
	R_func[ADD]=&inst_add;
	R_func[ADDU]=&inst_addu;
	R_func[SUB]=&inst_sub;
	R_func[AND]=&inst_and;
	R_func[OR]=&inst_or;
	R_func[XOR]=&inst_xor;
	R_func[NOR]=&inst_nor;
	R_func[NAND]=&inst_nand;
	R_func[SLT]=&inst_slt;
	R_func[SLL]=&inst_sll;
	R_func[SRL]=&inst_srl;
	R_func[SRA]=&inst_sra;
	R_func[JR]=&inst_jr;
	R_func[MULT]=&inst_mult;
	R_func[MULTU]=&inst_multu;
	R_func[MFHI]=&inst_mfhi;
	R_func[MFLO]=&inst_mflo;
	
	/* I-format and J-format */
	func[ADDI]=&inst_addi;
	func[ADDIU]=&inst_addiu;
	func[LW]=&inst_lw;
	func[LH]=&inst_lh;
	func[LHU]=&inst_lhu;
	func[LB]=&inst_lb;
	func[LBU]=&inst_lbu;
	func[SW]=&inst_sw;
	func[SH]=&inst_sh;
	func[SB]=&inst_sb;
	func[LUI]=&inst_lui;
	func[ANDI]=&inst_andi;
	func[ORI]=&inst_ori;
	func[NORI]=&inst_nori;
	func[SLTI]=&inst_slti;
	func[BEQ]=&inst_beq;
	func[BNE]=&inst_bne;
	func[BGTZ]=&inst_bgtz;
	func[J]=&inst_j;
	func[JAL]=&inst_jal;
}
