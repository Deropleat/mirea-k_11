#ifndef CL_TRAFFIC_LIGHTS_H
#define CL_TRAFFIC_LIGHTS_H

#include "cl_car_up.h"
#include "cl_car_down.h"
#include "cl_car_left.h"
#include "cl_car_right.h"

enum traffic_lights
{
	green = 0,
	yellow,
	red
};

class cl_traffic_lights : public cl_base
{
public:
	cl_traffic_lights(cl_base*);

	void update();
	void change_signal(traffic_lights, int);
	traffic_lights get_signal(bool);

	std::string get_signal_name();

	void commands_handler(std::string&);
private:
	int time = 4, current = 0;
	traffic_lights lights[2], last = green;
};

#endif