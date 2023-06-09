#include "cl_output.h"

cl_output::cl_output(cl_base* p_head_object) : cl_base(p_head_object, "cl_output")
{
}

void cl_output::print(std::string& message)
{
	if (!message.empty()) std::cout << std::endl << message;
}