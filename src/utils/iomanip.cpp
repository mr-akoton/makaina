#include <string>
#include <fstream>

std::string	getFileContent(const char* file)
{
	std::ifstream	fd(file);
	std::string		content;

	if (fd.is_open())
	{
		fd.seekg(0, std::ios::end);
		content.resize(fd.tellg());
		fd.seekg(0, std::ios::beg);
		fd.read(&content[0], content.size());
		fd.close();
		return content;
	}

	throw std::runtime_error("Error: failed to open " + std::string(file));
}
