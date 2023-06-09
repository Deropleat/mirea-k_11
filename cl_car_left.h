#ifndef CL_CAR_LEFT_H
#define CL_CAR_LEFT_H

#include "cl_car.h"

class cl_car_left : public cl_car
{
public:
	cl_car_left(cl_base*, std::string, int, int, int);

	void update(int, std::vector<cl_car*>, int = 1);
	void static_update(int = 1);
	bool direction();
	bool is_crossed();
};

#endif
