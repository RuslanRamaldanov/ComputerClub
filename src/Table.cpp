#include "../include/Table.h"
int Table::cost_per_hour = 0;
Table::Table(const int& table_id) : owner(nullptr), id(table_id), profit(0), start_time()
{
}


void Table::set_cost_per_hour(const int& cost)
{
	cost_per_hour = cost;
}

void Table::set_start_time(const Time& start)
{
	this->start_time = start;
}

int Table::get_profit() const
{
	return profit;
}

unsigned int Table::get_id() const
{
	return id;
}


void Table::set_client(Client& client)
{
	this->owner = &client;
}

bool Table::is_busy() const
{
	return owner == nullptr ? false : true;
}

void Table::calculate_profit(const Time& end_time) //считаем выручку и освобождаем стол
{
	Time time_diff = std::move(end_time - start_time);
	summary_working_time = summary_working_time + time_diff;
	int work_hours = time_diff.get_hours();
	if (time_diff.get_minutes() != 0)
		work_hours += 1;
	profit += work_hours * cost_per_hour;
	owner = nullptr;
}

Client* Table::get_client() const
{
	return owner;
}

Time Table::get_summary_working_time() const
{
	return summary_working_time;
}
