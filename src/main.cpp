#include "../include/Handler.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	std::string file = argv[1];
	if (std::fstream(file).good())
	{
		Handler handler(file);
		handler.start_processing();
	}
	return 0;
}
