#include "cl_traffic_lights.h"

cl_traffic_lights::cl_traffic_lights(cl_base* p_head_object) : cl_base(p_head_object, "cl_traffic_lights")
{
	lights[0] = red;
	lights[1] = green;
}

void cl_traffic_lights::update()
{
	if (lights[0] == yellow && lights[1] == yellow)
	{
		if (current == 1)
		{
			if (last == green) lights[0] = red;
			else if (last == red) lights[0] = green;

			lights[1] = last;
			current = 0;
		}
		else current++;
	}
	else if (current >= time)
	{
		last = lights[0];
		lights[0] = yellow;
		lights[1] = yellow;
		current = 0;
	}
	else current++;
}

void cl_traffic_lights::change_signal(traffic_lights new_signal, int play)
{
	if (current != 2)
	{
		lights[1] = new_signal;
		last = new_signal;

		if (new_signal == green) lights[0] = red;
		else lights[0] = green;

		time = play;
		current = play + 1;
	}
}

traffic_lights cl_traffic_lights::get_signal(bool horizontal)
{
	return lights[horizontal];
}

std::string cl_traffic_lights::get_signal_name()
{
	if (lights[1] == green) return "green";
	else if (lights[1] == red) return "red";
	return "yellow";
}

void cl_traffic_lights::commands_handler(std::string& message)
{
	if (message.find("Switching traffic lights") == 0)
	{
		if (message.find("green") != std::string::npos) change_signal(green, atoi(message.substr(message.find_last_of(' ') + 1).c_str()));
		else if (message.find("red") != std::string::npos) change_signal(red, atoi(message.substr(message.find_last_of(' ') + 1).c_str()));
		message = "";
	}
	else if (message == "Display the system status") message = "Traffic light color is " + get_signal_name();
	else if (message == " ") message = "";
}