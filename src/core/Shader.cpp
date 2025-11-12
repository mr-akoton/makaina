#include <core/Shader.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <util.hpp>

#include <iostream>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
	std::string	vertexFileContent = getFileContent(vertexFile);
	std::string	fragmentFileContent = getFileContent(fragmentFile);
	
	const char	*vertexSource = vertexFileContent.c_str();
	const char	*fragmentSource = fragmentFileContent.c_str();

	GLuint	vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	_debugShaderCompilation(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	_debugShaderCompilation(fragmentShader);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	_debugProgramLink(id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* --------------------------------- State ---------------------------------- */

void	Shader::enable(void)
{
	glUseProgram(id);
}

void	Shader::destroy(void)
{
	glDeleteProgram(id);
}

/* --------------------------------- setter --------------------------------- */

void	Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void	Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()),
				static_cast<int>(value));
}

void	Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void	Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()),
				value.x, value.y
	);
}

void	Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()),
				value.x, value.y, value.z
	);
}

void	Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()),
				value.x, value.y, value.z, value.w
	);
}

void	Shader::setMat2(const std::string &name, const glm::mat2 &value) const
{
	glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()),
					   1, GL_FALSE, glm::value_ptr(value)
	);
}

void	Shader::setMat3(const std::string &name, const glm::mat3 &value) const
{
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()),
					   1, GL_FALSE, glm::value_ptr(value)
	);
}

void	Shader::setMat4(const std::string &name, const glm::mat4 &value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()),
					   1, GL_FALSE, glm::value_ptr(value)
	);
}

/* ========================================================================== */
/*                                   DEBUG                                    */
/* ========================================================================== */

void	Shader::_debugShaderCompilation(GLuint shader_id)
{
	int		success;
	char	infoLog[INFO_LOG_BUFFER_SIZE];

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (not success)
	{
		glGetShaderInfoLog(shader_id, INFO_LOG_BUFFER_SIZE, NULL, infoLog);
		std::cerr << "Error: ShaderVertexCompilationFailed\n" << infoLog
				  << std::endl;
	}
}

void	Shader::_debugProgramLink(GLuint program_id)
{
	int		success;
	char	infoLog[INFO_LOG_BUFFER_SIZE];

	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (not success)
	{
		glGetProgramInfoLog(program_id, INFO_LOG_BUFFER_SIZE, NULL, infoLog);
		std::cerr << "Error: ProgramLinkFailed\n" << infoLog << std::endl;
	}
}

