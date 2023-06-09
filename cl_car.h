#ifndef CL_CAR_H
#define CL_CAR_H

#include "cl_input.h"

class cl_car : public cl_base
{
public:
	cl_car(cl_base*, std::string);

	virtual void update(int, std::vector<cl_car*>, int = 1) = 0;
	virtual void static_update(int = 1) = 0;
	virtual bool direction() = 0;
	virtual bool is_crossed() = 0;

	int get_pos(bool = true);
	bool get_out_of_system();
	std::string get_number();
	std::string get_information(bool = false);
protected:
	int x, y, w;
	std::string number;
	bool exit_road = false;
};

#endif
