#include "cl_car.h"

cl_car::cl_car(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) 
{
}

std::string cl_car::get_information(bool ignore)
{
	if (ignore)
	{
		if (exit_road) return number + " the car left the road section";
		else return number + " ( " + std::to_string(x) + ", " + std::to_string(y) + " )";
	}
	else if (!exit_road) return number + " ( " + std::to_string(x) + ", " + std::to_string(y) + " )";
	return "";
}

int cl_car::get_pos(bool xAxis)
{
	if (xAxis) return x;
	else return y;
}

bool cl_car::get_out_of_system()
{
	return exit_road;
}

std::string cl_car::get_number()
{
	return number;
}