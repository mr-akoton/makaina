#include <engine/Engine.hpp>
#include <iostream>

const unsigned int	WINDOW_WIDTH = 1920;
const unsigned int	WINDOW_HEIGHT = 1080;
const char*			WINDOW_TITLE = "Makaina";

int	main(void)
{
	try
	{
		Engine	engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
		engine.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
