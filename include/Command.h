#ifndef COMMAND_H
#define COMMAND_H
/*
	Класс описывает тело команды из входного файла

	Структура команды:
		
		<время события N> <идентификатор события N> <тело события N> <номер стола для ID = 2>


*/
#include <string>
#include "Event.h"
#include "Time.h"
#include <vector>

class Command
{
private:
	Time command_time;
	Event command_event;
	std::string client_name;
	int table_number;

	std::string init_command_string;
public:
	Command(const std::string& time, const int& event_id, const std::string& name, const std::string& init_string);

	void set_table_number(const int& number);

	std::string get_client_name() const;
	Event get_event() const;
	Time get_time() const;
	int get_table_number() const;
	std::string to_string() const;
};
#endif