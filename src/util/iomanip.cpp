#include <util/utils.hpp>

std::string	getFileContent(const char* path)
{
	std::string		content;
	std::ifstream	file(path);

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		content.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&content[0], content.size());
		file.close();
		return content;
	}

	throw std::runtime_error("Error: failed to open " + std::string(path));
}
