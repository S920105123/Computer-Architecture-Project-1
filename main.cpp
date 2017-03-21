#include "const.hpp"
#include "loader.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

int num_inst;

int stack[1024];
Instruction inst[1024];

int PC,sp;

int main()
{
	load_img(inst,stack,PC,num_inst,sp);
	std::cout<<num_inst<<" "<<PC<<'\n';
	for (int i=PC;i<PC+num_inst;i++) {
		print_inst(&inst[i]);
	}
	std::cout<<"sp="<<sp<<'\n';
	for (int i=0;i<10;i++) {
		std::cout<<stack[i]<<std::endl;
	}
}
