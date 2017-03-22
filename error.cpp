#include <fstream>
#include <string>

static std::ofstream ferr;
std::string err_str[5] = {
	"Write $0 Error\n",
	"Number Overflow\n",
	"Overwrite HI-LO registers\n",
	"Address Overflow\n",
	"Misalignment Error\n"
};

inline void error(int cycle, int type)
{
	ferr<<"In cycle"<<cycle<<": "<<err_str[type];
}

inline void error_init()
{
	ferr.open("error_dump.rpt",std::ios_base::out);
}
