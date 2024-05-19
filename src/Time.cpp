#include "../include/Time.h"

Time::Time() : hours(0), minutes(0), init_time_string()
{
}

Time::Time(const std::string& time_string)
{
	size_t position = time_string.find(":");
	hours = std::stoi(time_string.substr(0, position));
	minutes = std::stoi(time_string.substr(position + 1));
	init_time_string = time_string;
}

Time::Time(const int& hour, const int& min)
{
	hours = hour;
	minutes = min;
	init_time_string = std::to_string(hour) + ":" + std::to_string(minutes);
	if (hours < 10)
		init_time_string = "0" + init_time_string;
	if (minutes < 10)
		init_time_string.insert(init_time_string.find(":")+1, "0");
}

bool Time::operator>(const Time& time)
{
	return this->hours == time.hours ? this->minutes > time.minutes : this->hours > time.hours;
}

bool Time::operator<(const Time& time)
{
	return this->hours == time.hours ? this->minutes < time.minutes : this->hours < time.hours;
}

bool Time::operator==(const Time& time)
{
	return this->hours == time.hours && this->minutes == time.minutes;
}

Time& Time::operator=(const Time& time)
{
	this->hours = time.hours;
	this->minutes = time.minutes;
	this->init_time_string = time.init_time_string;
	return *this;
}

Time Time::operator-(const Time& time) const
{
	int total_minutes = (this->hours * 60 + this->minutes) - (time.hours * 60 + time.minutes);
	int total_hours = total_minutes / 60;
	int total_minutes_remaining = total_minutes % 60;
	return Time(total_hours, total_minutes_remaining);
}

Time Time::operator+(const Time& time) const
{
	int total_minutes = (this->hours * 60 + this->minutes) + (time.hours * 60 + time.minutes);
	int total_hours = total_minutes / 60;
	int total_minutes_remaining = total_minutes % 60;
	return Time(total_hours, total_minutes_remaining);
}

int Time::get_hours() const
{
	return hours;
}

int Time::get_minutes() const
{
	return minutes;
}

std::string Time::get_time() const
{
	return init_time_string;
}
