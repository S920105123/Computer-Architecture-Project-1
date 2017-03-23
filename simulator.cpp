#include "const.hpp"
#include "loader.hpp"
#include "datapath.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

std::ofstream fout;
int num_inst, num_word, cycle;

inline void print_reg(int idx, bool &first) {
	if (first) {
		fout<<"cycle "<<cycle<<"\n";
		first=false;
	}
	fout<<"$"<<std::dec<<std::setw(2)<<std::setfill('0')<<idx;
	fout<<": 0x"<<std::hex<<std::setw(8)<<std::setfill('0')<<reg[idx]<<"\n";
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
}

void simulate()
{
	
}

int main()
{	
	fout.open("my_snapshot.rpt",std::ios_base::out);
	load_img(inst,mem,PC,num_inst,num_word,sp);
	init_datapath();
	for (int i=PC;i<PC+num_inst;i++) {
		print_inst(&inst[i]);
	}
	simulate();
}
