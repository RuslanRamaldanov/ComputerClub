#include "../include/GeneratedEvent.h"

void GeneratedEvent::generate(const Command& command, const Event& generated_event, const std::string_view& message, const int& table)
{
	std::cout << command.get_time().get_time() << " " << static_cast<int>(generated_event) << " ";
	if (generated_event != Event::GENERATED_CLIENT_TOOK_TABLE)
		std::cout << message << std::endl;
	else
		std::cout << command.get_client_name() << " " << table << std::endl;
}

void GeneratedEvent::generate(const Time& time, const Event& generated_event, const std::string_view& name)
{
	std::cout << time.get_time() << " " << static_cast<int>(generated_event) << " " << name << std::endl;
}
