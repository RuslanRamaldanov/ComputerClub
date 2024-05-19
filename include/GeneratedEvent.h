#ifndef GENERATEDEVENT_H
#define GENERATEDEVENT_H

#include <iostream>
#include "Command.h"
#include "Event.h"
#include "Time.h"
#include <string_view>
class GeneratedEvent
{
public:
	static void generate(const Command& command, const Event& generated_event, const std::string_view& message, const int& table = 0);
	static void generate(const Time& time, const Event& generated_event, const std::string_view& name);
};

#endif