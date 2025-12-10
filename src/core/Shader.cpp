#include <core/Shader.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Shader::Shader(
	const char* vertexFile,
	const char* fragmentFile,
	const char* geometryFile
)
{
	std::string	vertexFileContent = getFileContent(vertexFile);
	std::string	fragmentFileContent = getFileContent(fragmentFile);
	
	const char*	vertexSource = vertexFileContent.c_str();
	const char*	fragmentSource = fragmentFileContent.c_str();

	GLuint	vertexShader, fragmentShader, geometryShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	_debugShaderCompilation(vertexShader, vertexFile);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	_debugShaderCompilation(fragmentShader, fragmentFile);

	if (geometryFile != nullptr)
	{
		std::string	geometryFileContent = getFileContent(geometryFile);
		const char*	geometrySource = geometryFileContent.c_str();

		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometrySource, nullptr);
		glCompileShader(geometryShader);
		_debugShaderCompilation(geometryShader, geometryFile);
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	if (geometryFile != nullptr)
	{
		glAttachShader(id, geometryShader);
	}
	glLinkProgram(id);
	_debugProgramLink(id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryFile != nullptr)
	{
		glDeleteShader(geometryShader);
	}
}


Shader::~Shader()
{
	glDeleteProgram(id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* --------------------------------- State ---------------------------------- */

void	Shader::enable(void)
{
	glUseProgram(id);
}

/* --------------------------------- setter --------------------------------- */

void	Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void	Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(
		glGetUniformLocation(id, name.c_str()),
		static_cast<int>(value)
	);
}

void	Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(
		glGetUniformLocation(id, name.c_str()),
		value
	);
}

void	Shader::setVec2(const std::string& name, const Vector2& value) const
{
	glUniform2f(
		glGetUniformLocation(id, name.c_str()),
		value.x, value.y
	);
}

void	Shader::setVec3(const std::string& name, const Vector3& value) const
{
	glUniform3f(
		glGetUniformLocation(id, name.c_str()),
		value.x, value.y, value.z
	);
}

void	Shader::setVec4(const std::string& name, const Vector4& value) const
{
	glUniform4f(
		glGetUniformLocation(id, name.c_str()),
		value.x, value.y, value.z, value.w
	);
}

void	Shader::setMat2(const std::string& name, const Matrix2& value) const
{
	glUniformMatrix2fv(
		glGetUniformLocation(id, name.c_str()),
		1, GL_FALSE, glm::value_ptr(value)
	);
}

void	Shader::setMat3(const std::string& name, const Matrix3& value) const
{
	glUniformMatrix3fv(
		glGetUniformLocation(id, name.c_str()),
		1, GL_FALSE, glm::value_ptr(value)
	);
}

void	Shader::setMat4(const std::string& name, const Matrix4& value) const
{
	glUniformMatrix4fv(
		glGetUniformLocation(id, name.c_str()),
		1, GL_FALSE, glm::value_ptr(value)
	);
}

/* ========================================================================== */
/*                                   DEBUG                                    */
/* ========================================================================== */

void	Shader::_debugShaderCompilation(
	GLuint				shaderId,
	const std::string	shaderType
)
{
	int		success;
	char	infoLog[INFO_LOG_BUFFER_SIZE];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (not success)
	{
		glGetShaderInfoLog(shaderId, INFO_LOG_BUFFER_SIZE, nullptr, infoLog);
		std::cerr << "Error: " << shaderType << ": ShaderCompilationFailed\n" << infoLog << std::endl;
	}
}

void	Shader::_debugProgramLink(GLuint programId)
{
	int		success;
	char	infoLog[INFO_LOG_BUFFER_SIZE];

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (not success)
	{
		glGetProgramInfoLog(programId, INFO_LOG_BUFFER_SIZE, nullptr, infoLog);
		std::cerr << "Error: ProgramLinkFailed\n" << infoLog << std::endl;
	}
}
