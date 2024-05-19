#ifndef TIME_H
#define TIME_H

#include <string>
class Time
{
private:
	unsigned char hours;
	unsigned char minutes;
	std::string init_time_string; 
	
public:
	Time();
	Time(const std::string& time_string);
	Time(const int& hour, const int& min);

	bool operator>(const Time& time);
	bool operator<(const Time& time);
	bool operator==(const Time& time);

	Time& operator=(const Time& time);
	Time operator-(const Time& time) const;
	Time operator+(const Time& time) const;

	int get_hours() const;
	int get_minutes() const;
	std::string get_time() const;
};
#endif