#ifndef CL_CROSSROAD_H
#define CL_CROSSROAD_H

#include "cl_traffic_lights.h"

class cl_crossroad : public cl_base
{
public:
	cl_crossroad(cl_base*, cl_traffic_lights*);

	void update();
	std::string get_car_information(std::string);
	void setup_car(std::string&);
	void setup_length(std::string&);

	void push(std::string, int, int);
	void sort();

	void commands_handler(std::string&);
private:
	int length = 1;
	std::vector<cl_car*> cars;
	cl_traffic_lights* traffic_lights;
};

#endif
