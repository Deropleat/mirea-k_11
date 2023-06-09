#include "cl_base.h"

cl_base::cl_base(cl_base* p_head_object, std::string s_object_name)
{
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;

	if (p_head_object) p_head_object->subordinate_objects.push_back(this);
}

void cl_base::set_state_all(int state)
{
	set_object_state(state);
	if (subordinate_objects.size() > 0) for (int i = 0; i < subordinate_objects.size(); i++) subordinate_objects.at(i)->set_state_all(state);
}

void cl_base::set_object_state(int state)
{
	i_object_state = state;
}

void cl_base::show_object_tree(int level)
{
	std::cout << std::endl << std::string(level * 4, ' ').c_str() << this->s_object_name << " is " << (i_object_state == 0 ? "not " : "") << "ready";
	if (subordinate_objects.size() > 0) for (int i = 0; i < subordinate_objects.size(); i++) subordinate_objects.at(i)->show_object_tree(level + 1);
}

void cl_base::setup_object_connection(cl_object_signal p_object_signal, cl_object_handler p_object_handler, cl_base* p_target_object)
{
	if (!p_target_object) p_target_object = this;
	for (size_t i = 0; i < object_connections.size(); i++) if (object_connections.at(i)->p_signal == p_object_signal && object_connections.at(i)->p_target == p_target_object && object_connections.at(i)->p_handler == p_object_handler) return;

	cl_object_connection* connection;
	connection = new cl_object_connection();
	connection->p_signal = p_object_signal;
	connection->p_target = p_target_object;
	connection->p_handler = p_object_handler;
	object_connections.push_back(connection);
}

void cl_base::send_object_signal(cl_object_signal p_object_signal, std::string& s_signal)
{
	if (i_object_state == 0) return;

	cl_object_handler p_handler;
	cl_base* p_target;

	(this->*p_object_signal)(s_signal);

	for (size_t i = 0; i < object_connections.size(); i++)
	{
		if (object_connections.at(i)->p_signal == p_object_signal);
		{
			p_handler = object_connections.at(i)->p_handler;
			p_target = object_connections.at(i)->p_target;
			if (p_target->i_object_state != 0) (p_target->*p_handler)(s_signal);
		}
	}
}

void cl_base::delete_object_connection(cl_object_signal p_object_signal, cl_object_handler p_object_handler, cl_base* p_target_object)
{
	if (!p_target_object) p_target_object = this;
	for (size_t i = 0; i < object_connections.size(); i++) if (object_connections.at(i)->p_signal == p_object_signal && object_connections.at(i)->p_target == p_target_object && object_connections.at(i)->p_handler == p_object_handler) object_connections.erase(object_connections.begin() + i);
}