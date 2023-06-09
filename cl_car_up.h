#ifndef CL_CAR_UP_H
#define CL_CAR_UP_H

#include "cl_car.h"

class cl_car_up : public cl_car
{
public:
	cl_car_up(cl_base*, std::string, int, int, int);

	void update(int, std::vector<cl_car*>, int = 1);
	void static_update(int = 1);
	bool direction();
	bool is_crossed();
};

#endif
