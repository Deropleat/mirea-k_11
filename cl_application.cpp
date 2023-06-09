#include "cl_application.h"

cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object, "cl_application")
{
	input = new cl_input(this);
	traffic_lights = new cl_traffic_lights(this);
	crossroad = new cl_crossroad(this, traffic_lights);
	output = new cl_output(this);
}

void cl_application::build_tree_objects()
{
	set_state_all(1);

	std::string message;

	crossroad->setup_object_connection(SIGNALFN(cl_input::read), HANDLERFN(cl_crossroad::setup_length));
	crossroad->send_object_signal(SIGNALFN(cl_input::read), message);
	crossroad->delete_object_connection(SIGNALFN(cl_input::read), HANDLERFN(cl_crossroad::setup_length));

	crossroad->setup_object_connection(SIGNALFN(cl_input::read), HANDLERFN(cl_crossroad::setup_car));
	while (true)
	{
		crossroad->send_object_signal(SIGNALFN(cl_input::read), message);
		if (message == "End of cars") break;
	}
	crossroad->delete_object_connection(SIGNALFN(cl_input::read), HANDLERFN(cl_crossroad::setup_car));

	setup_object_connection(SIGNALFN(cl_input::read), HANDLERFN(cl_application::push_command));
	while (true)
	{
		send_object_signal(SIGNALFN(cl_input::read), message);
		if (message == "Turn off the system") break;
	}
	delete_object_connection(SIGNALFN(cl_input::read), HANDLERFN(cl_application::push_command));

	setup_object_connection(SIGNALFN(cl_application::get_command), HANDLERFN(cl_traffic_lights::commands_handler), traffic_lights);
	setup_object_connection(SIGNALFN(cl_application::get_command), HANDLERFN(cl_crossroad::commands_handler), crossroad);
}

int cl_application::exec_app()
{
	std::string message;

	std::cout << "Ready to work";

	while (true)
	{
		traffic_lights->update();

		send_object_signal(SIGNALFN(cl_application::get_command), message);
		callback.push_back(message);

		ticks++;
		crossroad->update();

		if (message == "Turn off the system" || message == "SHOWTREE") break;
	}
	delete_object_connection(SIGNALFN(cl_application::get_command), HANDLERFN(cl_traffic_lights::commands_handler));
	delete_object_connection(SIGNALFN(cl_application::get_command), HANDLERFN(cl_crossroad::commands_handler));

	setup_object_connection(SIGNALFN(cl_application::get_callback), HANDLERFN(cl_output::print));
	for (size_t i = 0; i < callback.size(); i++) send_object_signal(SIGNALFN(cl_application::get_callback), message);
	delete_object_connection(SIGNALFN(cl_application::get_callback), HANDLERFN(cl_output::print));

	return 0;
}

void cl_application::get_command(std::string& message)
{
	message = commands.at(ticks);
}

void cl_application::push_command(std::string& message)
{
	commands.push_back(message);
}

void cl_application::get_callback(std::string& message)
{
	if (callback.at(index) == "SHOWTREE")
	{
		show_object_tree();
		message = "";
		return;
	}
	message = callback.at(index);
	index++;
}