#include "cl_input.h"

cl_input::cl_input(cl_base* p_head_object) : cl_base(p_head_object, "cl_input") 
{
}

void cl_input::read(std::string& line)
{
	std::getline(std::cin, line);
}