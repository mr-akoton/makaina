#include <core/Engine.hpp>
#include <iostream>

const int	WINDOW_WIDTH = 1280;
const int	WINDOW_HEIGHT = 720;
const char	*WINDOW_TITLE = "Makaina";

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
