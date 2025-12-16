#include <core/Shader.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string	vertexFileContent = getFileContent(vertexFile);
	std::string	fragmentFileContent = getFileContent(fragmentFile);
	
	const char*	vertexSource = vertexFileContent.c_str();
	const char*	fragmentSource = fragmentFileContent.c_str();

	GLuint	vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	_debugShaderCompilation(vertexShader, vertexFile);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	_debugShaderCompilation(fragmentShader, fragmentFile);


	_id = glCreateProgram();
	glAttachShader(_id, vertexShader);
	glAttachShader(_id, fragmentShader);
	glLinkProgram(_id);
	_debugProgramLink(_id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


Shader::~Shader()
{
	glDeleteProgram(_id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* --------------------------------- State ---------------------------------- */

void	Shader::enable(void)
{
	glUseProgram(_id);
}

/* --------------------------------- setter --------------------------------- */

void	Shader::setInt(const std::string& uniform, int value) const
{
	glUniform1i(glGetUniformLocation(_id, uniform.c_str()), value);
}

void	Shader::setBool(const std::string& uniform, bool value) const
{
	glUniform1i(
		glGetUniformLocation(_id, uniform.c_str()),
		static_cast<int>(value)
	);
}

void	Shader::setFloat(const std::string& uniform, float value) const
{
	glUniform1f(
		glGetUniformLocation(_id, uniform.c_str()),
		value
	);
}

void	Shader::setVec2(const std::string& uniform, const Vector2& value) const
{
	glUniform2f(
		glGetUniformLocation(_id, uniform.c_str()),
		value.x, value.y
	);
}

void	Shader::setVec3(const std::string& uniform, const Vector3& value) const
{
	glUniform3f(
		glGetUniformLocation(_id, uniform.c_str()),
		value.x, value.y, value.z
	);
}

void	Shader::setVec4(const std::string& uniform, const Vector4& value) const
{
	glUniform4f(
		glGetUniformLocation(_id, uniform.c_str()),
		value.x, value.y, value.z, value.w
	);
}

void	Shader::setMat2(const std::string& uniform, const Matrix2& value) const
{
	glUniformMatrix2fv(
		glGetUniformLocation(_id, uniform.c_str()),
		1, GL_FALSE, glm::value_ptr(value)
	);
}

void	Shader::setMat3(const std::string& uniform, const Matrix3& value) const
{
	glUniformMatrix3fv(
		glGetUniformLocation(_id, uniform.c_str()),
		1, GL_FALSE, glm::value_ptr(value)
	);
}

void	Shader::setMat4(const std::string& uniform, const Matrix4& value) const
{
	glUniformMatrix4fv(
		glGetUniformLocation(_id, uniform.c_str()),
		1, GL_FALSE, glm::value_ptr(value)
	);
}

/* ========================================================================== */
/*                                   DEBUG                                    */
/* ========================================================================== */

void	Shader::_debugShaderCompilation(
	GLuint shaderId,
	const std::string shaderType
)
{
	int		success;
	char	infoLog[INFO_LOG_BUFFER_SIZE];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (not success)
	{
		glGetShaderInfoLog(shaderId, INFO_LOG_BUFFER_SIZE, nullptr, infoLog);
		std::cerr << "Error: " << shaderType << ": ShaderCompilationFailed\n"
				  << infoLog << std::endl;
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
