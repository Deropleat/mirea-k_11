#include "cl_crossroad.h"

cl_crossroad::cl_crossroad(cl_base* p_head_object, cl_traffic_lights* traffic_lights) : cl_base(p_head_object, "cl_crossroad")
{
	this->traffic_lights = traffic_lights;
	this->length = length;
}

void cl_crossroad::setup_length(std::string& length)
{
	this->length = atoi(length.c_str());
}

void cl_crossroad::setup_car(std::string& info)
{
	std::string number = info.substr(0, info.find(' '));
	int x = atoi(info.substr(info.find(' ') + 1).substr(0, info.find(' ')).c_str());
	int y = atoi(info.substr(info.find_last_of(' ') + 1).c_str());
	push(number, x, y);
}

void cl_crossroad::update()
{
	for (size_t i = 0; i < cars.size(); i++)
	{
		if (traffic_lights->get_signal(cars.at(i)->direction()) == green || cars.at(i)->is_crossed()) cars.at(i)->update(i, cars);
		else cars.at(i)->static_update();
	}
}

std::string cl_crossroad::get_car_information(std::string number)
{
	std::string ret = "";
	for (size_t i = 0; i < cars.size(); i++) if (number == cars.at(i)->get_number())
	{
		if (!cars.at(i)->get_out_of_system()) ret += "Car ";
		ret += cars.at(i)->get_information(true);
	}

	return ret;
}

void cl_crossroad::push(std::string number, int x, int y)
{
	if (x == -1) cars.push_back(new cl_car_down(this, number, x, y, length));
	else if (x == 1) cars.push_back(new cl_car_up(this, number, x, y, length));
	else if (y == 1) cars.push_back(new cl_car_left(this, number, x, y, length));
	else if (y == -1) cars.push_back(new cl_car_right(this, number, x, y, length));

	sort();
}

void cl_crossroad::sort()
{
	for (int j = 1; j < cars.size(); j++)
	{
		for (int i = 0; i < cars.size() - 1; i++)
		{
			int first = atoi(cars.at(i)->get_number().substr(1, 3).c_str());
			int second = atoi(cars.at(i + 1)->get_number().substr(1, 3).c_str());

			if (first > second) std::swap(cars.at(i), cars.at(i + 1));
		}
	}
}

void cl_crossroad::commands_handler(std::string& message)
{
	if (message.find("Car") == 0) message = get_car_information(message.substr(message.find(' ') + 1));
	else if (message.find("Traffic light color is ") != std::string::npos) for (size_t i = 0; i < cars.size(); i++) if (!cars.at(i)->get_information().empty()) message += "\n" + cars.at(i)->get_information();
}