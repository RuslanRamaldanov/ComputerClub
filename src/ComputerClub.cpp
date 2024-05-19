#include "../include/ComputerClub.h"

ComputerClub::ComputerClub(const std::string& start, const std::string& end, const int& count, const int& cost) :
	start_time(start), end_time(end), all_clients(), clients_in_queue()
{
	Table::set_cost_per_hour(cost); //устанавливаем цену за час
	tables.reserve(count); //резервируем место для хранения объектов Table
	for (int i = 0; i < count; i++)
		tables.emplace_back(i);   //создаем объекты Table, передаем в коструктор номер очередного стола.
}

bool ComputerClub::is_there_free_table()
{
	for (const Table& table : tables)
		if (!table.is_busy())
			return true;
	return false;
}

void ComputerClub::add_client(Client& client)
{
	all_clients.push_back(std::move(client));
	if(!is_there_free_table())
		clients_in_queue.push_back(--all_clients.end());
}

void ComputerClub::set_client_to_table(const int& table_number, const Client& current_client, const Time& time)
{
	tables.at(table_number).set_start_time(time);
	tables.at(table_number).set_client(*std::find(all_clients.begin(), all_clients.end(), current_client));
	//удаляем клиента из очереди ожидания
	for (auto it = clients_in_queue.begin(); it != clients_in_queue.end(); it++)
	{
		if (**it == current_client)
		{
			clients_in_queue.erase(it);
			break;
		}
	}
}

bool ComputerClub::client_leave(const Client& client) //Клиент уходит, когда очередь ожидания уже заполнена
{
	for (auto it = clients_in_queue.begin(); it != clients_in_queue.end(); it++)
	{
		if (**it == client)
		{
			all_clients.erase(*it);
			clients_in_queue.erase(it);
			return true;
		}
	}
	return false;
}

std::vector<Table>::iterator ComputerClub::client_leave_from_club(const Client& client, const Time& time)
{
	auto it = tables.begin();
	for (; it != tables.end(); it++)
	{
		if (it->get_client() != nullptr && *(it->get_client()) == client)
		{
			it->calculate_profit(time);
			break;
		}
	}

	if (clients_in_queue.size() > 0 && client_leave(client))
	{}
	else
		all_clients.erase(std::find(all_clients.begin(), all_clients.end(), client));

	return it;
}

void ComputerClub::end_of_work()
{
	while (all_clients.size() != 0)
	{
		GeneratedEvent::generate(end_time, Event::GENERATED_CLIENT_LEAVE, all_clients.back().get_name());
		client_leave_from_club(all_clients.back(), end_time);
	}
	std::cout << end_time.get_time() << std::endl;
	for (const Table& table : tables)
		std::cout << table.get_id() + 1 << " " << table.get_profit() << " " << table.get_summary_working_time().get_time() << std::endl;
}

Time ComputerClub::get_start_time() const
{
	return start_time;
}

Time ComputerClub::get_end_time() const
{
	return end_time;
}

//обработка поступившей команды
void ComputerClub::command_processing(const Command& incoming_command)
{
	std::string client_name = incoming_command.get_client_name();
	Time command_time = incoming_command.get_time();
	int table_number = incoming_command.get_table_number() - 1;

	Client current_client = Client(client_name);

	std::cout << incoming_command.to_string() << std::endl;

	switch (incoming_command.get_event())
	{

	//Обработка события первого типа: ID = 1 - КЛИЕНТ ПРИШЕЛ. Структура команды: <время> 1 <имя клиента>
	case Event::CLIENT_ARRIVE:
		if (start_time > command_time) //проверяем, чтобы время прибытия клиента было не меньше времени открытия клуба
			GeneratedEvent::generate(incoming_command, Event::GENERATED_ERROR, "NotOpenYet");

		else if (std::find(all_clients.begin(), all_clients.end(), current_client) != all_clients.end())
			GeneratedEvent::generate(incoming_command, Event::GENERATED_ERROR, "YouShallNotPath");

		else
			add_client(current_client);
		break;

	//Обработка события первого типа: ID = 2 - КЛИЕНТ ЗАНЯЛ СТОЛ. Структура команды: <время> 2 <имя клиента> <номер стола>
	case Event::CLIENT_TOOK_TABLE:
		if (tables.at(table_number).is_busy())
			GeneratedEvent::generate(incoming_command, Event::GENERATED_ERROR, "PlaceIsBusy");

		else if (std::find(all_clients.begin(), all_clients.end(), current_client) == all_clients.end())
			GeneratedEvent::generate(incoming_command, Event::GENERATED_ERROR, "ClientUnknown");

		else
			set_client_to_table(table_number, current_client, command_time);
		break;

	//Обработка события первого типа: ID = 3 - КЛИЕНТ ОЖИДАЕТ. Структура команды: <время> 3 <имя клиента>
	case Event::CLIENT_WAITING:
		if (is_there_free_table())
			GeneratedEvent::generate(incoming_command, Event::GENERATED_ERROR, "ICantWaitNoLonger!");
		else if (clients_in_queue.size() > tables.size())
		{
			//GENERATE EVENT: ID = 11
			client_leave(current_client);
			GeneratedEvent::generate(incoming_command, Event::GENERATED_CLIENT_LEAVE, current_client.get_name());
		}
		break;

	//Обработка события первого типа: ID = 4 - КЛИЕНТ УШЕЛ. Структура команды: <время> 4 <имя клиента>
	case Event::CLIENT_LEAVE:
		if (std::find(all_clients.begin(), all_clients.end(), current_client) == all_clients.end())
			GeneratedEvent::generate(incoming_command, Event::GENERATED_ERROR, "ClientUnknown");
		else
		{
			auto it = client_leave_from_club(current_client, command_time);
			if (it != tables.end() && clients_in_queue.size() != 0)
			{
				GeneratedEvent::generate(incoming_command, Event::GENERATED_CLIENT_TOOK_TABLE, "", it->get_id() + 1);
				set_client_to_table(it->get_id(), *clients_in_queue.front(), command_time);
			}

		}
	}
}

