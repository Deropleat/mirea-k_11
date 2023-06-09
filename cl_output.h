#ifndef CL_OUTPUT_H
#define CL_OUTPUT_H

#include "cl_base.h"

class cl_output : public cl_base
{
public:
	cl_output(cl_base*);

	void print(std::string&);
};

#endif
