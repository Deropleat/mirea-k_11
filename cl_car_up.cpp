#include "cl_car_up.h"

cl_car_up::cl_car_up(cl_base* p_head_object, std::string number, int x, int y, int w) : cl_car(p_head_object, "Car (up) " + number)
{
	this->number = number;
	this->x = x;
	this->y = y;
	this->w = w;
}

void cl_car_up::update(int index, std::vector<cl_car*> list, int length)
{
	y += length;
	if (y == 0) y += 1;
	for (size_t i = 0; i < list.size(); i++) if (index != i && list.at(i)->get_pos() == x && list.at(i)->get_pos(false) == y) y += 1;
	
	exit_road = y > w;
	set_object_state(!exit_road);
}

void cl_car_up::static_update(int length)
{
	if (y < -2) y += length;
}

bool cl_car_up::direction()
{
	return false;
}

bool cl_car_up::is_crossed()
{
	return y > -2;
}