#include <iostream>
#include <iomanip>
#include <fstream>
#include "const.hpp"
#include "loader.hpp"
#include "datapath.hpp"
#include "error.hpp"

std::ofstream fout;
int num_inst, num_word, cycle;

inline void print_reg(int idx, bool &first) {
	static std::string reg_str[3]={"$HI","$LO","PC"};
	if (first) {
		fout<<std::dec<<"cycle "<<cycle<<std::endl;
		first=false;
	}
	if (idx>31) {
		fout<<reg_str[idx-32];
	} else {
		fout<<"$"<<std::dec<<std::setw(2)<<std::setfill('0')<<idx;
	}
	fout<<": 0x"<<std::hex<<std::uppercase<<std::setw(8)<<std::setfill('0')<<reg[idx]<<std::endl;
}

void output()
{
	bool first=true;
	while (!change.empty()) {
		int idx=change.front();
		change.pop();
		if (reg[idx]!=pre_reg[idx]) {
			print_reg(idx,first);
			pre_reg[idx]=reg[idx];
		}
	}
	/* Check PC */
	if (PC!=pre_PC) {
		print_reg(34,first);
		pre_PC=PC;
	}
	if (!first) {
		fout<<"\n\n";
	}
}

void simulate()
{	
	init_str_const();
	int idx=(PC>>2), opcode=inst[idx].opcode, funct=inst[idx].funct;
	while (opcode!=HALT) {
		cycle++;
		std::cerr<<"cycle "<<std::dec<<cycle<<": ";
		std::cerr<<reg[4]<<" ";
		print_inst(&inst[idx]);
		if (opcode==0) {
			//fout<<inst_str_r[funct]<<"\n";
			(*R_func[funct])();
		} else {
			//fout<<inst_str[opcode]<<"\n";
			(*func[opcode])();
		}
		output();
		
		idx=PC>>2;
		opcode=inst[idx].opcode;
		funct=inst[idx].funct;
	}
}

int main()
{	
	bool first=true;
	fout.open("my_snapshot.rpt",std::ios_base::out);
	load_img(PC,num_inst,num_word,sp);
	init_error();
	init_datapath();
	for (int i=PC>>2;i<(PC>>2)+num_inst;i++) {
		print_inst(&inst[i]);
	}
	for (int i=0;i<num_word;i++) {
		std::cerr<<std::hex<<mem[i]<<std::endl;
	}
	for (int i=0;i<35;i++) {
		print_reg(i,first);
	}
	fout<<"\n\n";
	simulate();
	btol(100);
}
