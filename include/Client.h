#ifndef CLIENT_H
#define CLIENT_H
/*
	����� ������������ �������. �������� ��� �������.
*/
#include <string>
class Client
{
private:
	std::string client_name;
public:
	Client(const std::string& name);
	bool operator<(const Client& another_client) const;
	bool operator==(const Client& another_client) const;

	std::string get_name() const;
};

#endif