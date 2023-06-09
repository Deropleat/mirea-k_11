#ifndef CL_INPUT_H
#define CL_INPUT_H

#include "cl_output.h"

class cl_input : public cl_base
{
public:
	cl_input(cl_base*);

	void read(std::string&);
};

#endif
