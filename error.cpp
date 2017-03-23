#include <fstream>
#include <string>

extern int cycle;
static std::ofstream ferr;
std::string err_str[5] = {
	"Write $0 Error\n",
	"Number Overflow\n",
	"Overwrite HI-LO registers\n",
	"Address Overflow\n",
	"Misalignment Error\n"
};

inline void error(int type)
{
	/* This function print error message in 
	   error_dump.rpt depends on error code "type" */
	ferr<<"In cycle"<<cycle<<": "<<err_str[type];
}

inline void error_init()
{
	/* Initialize */
	ferr.open("error_dump.rpt",std::ios_base::out);
}
