#include <core/Engine.hpp>
#include <iostream>

int main(void)
{
	try
	{
		Engine	app;
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
