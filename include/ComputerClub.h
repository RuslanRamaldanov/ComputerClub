#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H
/*
	Класс представляет компьютерный клуб.
*/
#include <string>
#include "Time.h"
#include "Table.h"
#include "Client.h"
#include "Command.h"
#include "Event.h"
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include "GeneratedEvent.h"

class ComputerClub
{
private:
	Time start_time;
	Time end_time;

	std::vector<Table> tables;
	std::list<Client> all_clients;
	std::vector<std::list<Client>::iterator> clients_in_queue;


	bool is_there_free_table();
	void add_client(Client& client);
	void set_client_to_table(const int& table_number, const Client& current_client, const Time& time);
	bool client_leave(const Client& client); //клиент уходит, когда очередь ожидания уже заполенена
	std::vector<Table>::iterator client_leave_from_club(const Client& client, const Time& time); //клиент уходит, id = 4
public:
	ComputerClub(const std::string& start, const std::string& end, const int& count, const int& cost);
	void command_processing(const Command& incoming_command);
	void end_of_work();

	Time get_start_time() const;
	Time get_end_time() const;
};
#endif