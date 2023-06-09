#include "cl_car_left.h"

cl_car_left::cl_car_left(cl_base* p_head_object, std::string number, int x, int y, int w) : cl_car(p_head_object, "Car (left) " + number)
{
	this->number = number;
	this->x = x;
	this->y = y;
	this->w = w;
}

void cl_car_left::update(int index, std::vector<cl_car*> list, int length)
{
	x -= length;
	if (x == 0) x -= 1;
	for (size_t i = 0; i < list.size(); i++) if (index != i && list.at(i)->get_pos() == x && list.at(i)->get_pos(false) == y) x -= 1;
	
	exit_road = x < -w;
	set_object_state(!exit_road);
}

void cl_car_left::static_update(int length)
{
	if (x > 2) x -= length;
}

bool cl_car_left::direction()
{
	return true;
}

bool cl_car_left::is_crossed()
{
	return x < 2;
}