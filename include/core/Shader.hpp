#ifndef SHADER_HPP
# define SHADER_HPP

# include <glad/glad.h>
# include <util.hpp>
# include <glm/glm.hpp>

# define INFO_LOG_BUFFER_SIZE	512


class	Shader
{
	public	:
		GLuint	id;

	
	public	:
		Shader(const char *vertexFile, const char *fragmentFile);

		void	enable(void);
		void	destroy(void);
		void	setInt(const std::string &name, int value) const;
		void	setBool(const std::string &name, bool value) const;
		void	setFloat(const std::string &name, float value) const;
		void	setVec2(const std::string &name, const glm::vec2 &value) const;
		void	setVec3(const std::string &name, const glm::vec3 &value) const;
		void	setVec4(const std::string &name, const glm::vec4 &value) const;
		void	setMat2(const std::string &name, const glm::mat2 &value) const;
		void	setMat3(const std::string &name, const glm::mat3 &value) const;
		void	setMat4(const std::string &name, const glm::mat4 &value) const;

	private	:
		void	_debugShaderCompilation(GLuint shaderId);
		void	_debugProgramLink(GLuint programId);
};

#endif // SHADER_HPP
