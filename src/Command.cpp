#include "../include/Command.h"
Command::Command(const std::string& time, const int& event_id, const std::string& name, const std::string& init_string) :
	command_time(time), client_name(name), table_number(0), init_command_string(init_string)
{
	switch (event_id)
	{
	case 1:
		command_event = Event::CLIENT_ARRIVE;
		break;
	case 2:
		command_event = Event::CLIENT_TOOK_TABLE;
		break;
	case 3:
		command_event = Event::CLIENT_WAITING;
		break;
	case 4:
		command_event = Event::CLIENT_LEAVE;
		break;
	case 11:
		command_event = Event::GENERATED_CLIENT_LEAVE;
		break;
	case 12:
		command_event = Event::GENERATED_CLIENT_TOOK_TABLE;
		break;
	default:
		command_event = Event::GENERATED_ERROR;
		break;
	}
}

void Command::set_table_number(const int& number)
{
	table_number = number;
}

std::string Command::get_client_name() const
{
	return client_name;
}

Event Command::get_event() const
{
	return command_event;
}

Time Command::get_time() const
{
	return command_time;
}

int Command::get_table_number() const
{
	return table_number;
}

std::string Command::to_string() const
{
	return init_command_string;
}

