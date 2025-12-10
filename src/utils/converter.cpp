#include <utils/utils.hpp>

Vector3	hexToRGB(std::string color)
{
	if (color.length() == 7 and color[0] == '#')
	{
		std::string	hexColor = color.substr(1);
		for (size_t i = 0; i < hexColor.length(); i++)
		{
			if (not std::isxdigit(hexColor[i]))
			{
				return Vector3(0.0f);
			}
		}

		std::string	r = hexColor.substr(0, 2);
		std::string	g = hexColor.substr(2, 2);
		std::string	b = hexColor.substr(4);

		return Vector3(
				(float)std::stoi(r, nullptr, 16) / 255,
				(float)std::stoi(g, nullptr, 16) / 255,
				(float)std::stoi(b, nullptr, 16) / 255
			);
	}
	else
	{
		return Vector3(0.0f);
	}
}
