#include "../include/Client.h"

Client::Client(const std::string& name) : client_name(name)
{
}

bool Client::operator<(const Client& another_client) const
{
    std::string tmp = another_client.client_name;
    return client_name.compare(tmp) < 0 ? true : false;
}

bool Client::operator==(const Client& another_client) const
{
    return this->client_name == another_client.client_name;
}

std::string Client::get_name() const
{
    return client_name;
}
