#include "const.hpp"
#include "loader.hpp"
#include "datapath.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

int num_inst;

void simulate()
{
	
}

int main()
{
	load_img(inst,stack,PC,num_inst,sp);
	simulate();
	for (int i=PC;i<PC+num_inst;i++) {
		print_inst(&inst[i]);
	}
}
