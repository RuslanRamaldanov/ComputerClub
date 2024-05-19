#include "../include/Handler.h"

Handler::Handler(const std::string& path_to_file) : input_file(path_to_file)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Проверка входной строки на валидность. Используются регулярные выражения.
bool Handler::is_valid(const std::string& input_string)
{
	std::regex start_end_time_pattern("([01]?[0-9]|2[0-3]):[0-5][0-9] ([01]?[0-9]|2[0-3]):[0-5][0-9]");
	std::regex number_pattern("^[0-9]+");
	return
		std::regex_match(input_string, start_end_time_pattern) ||
		std::regex_match(input_string, number_pattern);
}
bool Handler::is_command_valid(const std::string& input_string)
{
	std::regex command_pattern("([01]?[0-9]|2[0-3]):[0-5][0-9] [0-9]* [a-zA-Z0-9_]* ?[0-9]*");
	return std::regex_match(input_string, command_pattern);
}
// Разбиение строки по разделителю (пробел).
std::vector<std::string> Handler::line_split(const std::string_view& line)
{
	std::vector<std::string> substrings;
	size_t startPos = 0;
	size_t endPos = line.find(" ");

	while (endPos != std::string_view::npos) {
		substrings.emplace_back(line.substr(startPos, endPos - startPos));
		startPos = endPos + 1;
		endPos = line.find(" ", startPos);
	}
	substrings.emplace_back(line.substr(startPos));
	return substrings;
}

Command Handler::create_command_from_string(const std::string& command_line)
{
	std::vector<std::string> split_command(line_split(command_line)); //разделяем комманду на составные части
	Command command(split_command[0], std::stoi(split_command[1]), split_command[2], command_line);
	if (command.get_event() == Event::CLIENT_TOOK_TABLE && split_command.size() == 4)
		command.set_table_number(std::stoi(split_command[3]));
	return command;
}

void Handler::start_processing()
{
	std::vector<std::string> club_init_parameters; // параметры, необходимые для инициализации клуба. Первые 3 строки входного файла
	std::string line;
	for (int i = 0; i < 3; i++)
	{
		std::getline(input_file, line); //считываем строку
		if (is_valid(line))
			club_init_parameters.push_back(line);
		else
		{
			std::cerr << "Invalid init line: " << line << std::endl;
			return;
		}
	}

	std::vector<std::string> start_end_time_vector(line_split(club_init_parameters[1])); // получаем время начала и конца работы клуба.
	//теперь у нас есть все, чтобы создать объект клуба
	club = std::make_unique<ComputerClub>(
		start_end_time_vector[0],
		start_end_time_vector[1],
		std::stoi(club_init_parameters[0]),
		std::stoi(club_init_parameters[2]));

	//начинаем считывать комманды
	std::cout << club->get_start_time().get_time() << std::endl;
	while (std::getline(input_file, line))
	{
		if (is_command_valid(line))
		{
			Command command = create_command_from_string(line);
			club->command_processing(command);
		}
		else
		{
			std::cerr << "Incorrcet line: " << line << std::endl;
			return;
		}
	}
	club->end_of_work();
}
