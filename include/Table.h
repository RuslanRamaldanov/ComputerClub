#ifndef TABLE_H
#define TABLE_H
/*
	����� ��������� "����������" �����.
	������������ �������.
	������ �������, ������� ����� ������ ����
*/
#include "Client.h"
#include "Time.h"
class Table
{
private:
	unsigned int id;	// id �����
	Client* owner;       // ������, �������� ����
	Time start_time;	// ����� ������ ������ �����
	static int cost_per_hour;  //���� �� ���
	int profit;
	Time summary_working_time;
public:
	Table(const int& table_id);

	static void set_cost_per_hour(const int& cost);
	void set_start_time(const Time& start);
	void set_client(Client& client);

	bool is_busy() const;
	Client* get_client() const;
	void calculate_profit(const Time& end_time);
	int get_profit() const;
	Time get_summary_working_time() const;
	unsigned int get_id() const;
};
#endif