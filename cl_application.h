#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include "cl_crossroad.h"

class cl_application : public cl_base
{
public:
	cl_application(cl_base* = nullptr);

	void build_tree_objects();
	int exec_app();

	void get_command(std::string&);
	void push_command(std::string&);
	void get_callback(std::string&);
private:
	int ticks = 0;
	size_t index = 0;
	std::vector<std::string> commands, callback;

	cl_input* input;
	cl_output* output;
	cl_crossroad* crossroad;
	cl_traffic_lights* traffic_lights;
};

#endif
