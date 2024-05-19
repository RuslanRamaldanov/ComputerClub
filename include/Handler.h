#ifndef HANDLER_H
#define HANDLER_H
/*
	Основной класс - обработчик.
*/
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include <memory>
#include "ComputerClub.h"
#include "Command.h"

class Handler
{
private:
	std::ifstream input_file; //входной файл
	bool is_valid(const std::string& input_string); //проверка валидности строки
	bool is_command_valid(const std::string& input_string); //проверка валидности строки
	std::vector<std::string> line_split(const std::string_view& line); //разделение строки по пробелам
	Command create_command_from_string(const std::string& command_line);
	std::unique_ptr<ComputerClub> club;
	
public:
	Handler(const std::string& path_to_file);
	void start_processing();
	
};
#endif