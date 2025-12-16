#ifndef SHADER_HPP
# define SHADER_HPP

# include <glad/glad.h>
# include <glm/glm.hpp>

# include <util/utils.hpp>
# include <util/types.hpp>

# define INFO_LOG_BUFFER_SIZE	512


class	Shader
{
	private	:
		GLuint	_id;
	
	public	:
		Shader(const char* vertexFile, const char* fragmentFile);
		~Shader();

		void	enable(void);
		void	setInt(const std::string& uniform, int value) const;
		void	setBool(const std::string& uniform, bool value) const;
		void	setFloat(const std::string& uniform, float value) const;
		void	setVec2(const std::string& uniform, const Vector2& value) const;
		void	setVec3(const std::string& uniform, const Vector3& value) const;
		void	setVec4(const std::string& uniform, const Vector4& value) const;
		void	setMat2(const std::string& uniform, const Matrix2& value) const;
		void	setMat3(const std::string& uniform, const Matrix3& value) const;
		void	setMat4(const std::string& uniform, const Matrix4& value) const;
 
	private	:
		void	_debugShaderCompilation(
			GLuint shaderId,
			const std::string shaderName
		);
		void	_debugProgramLink(GLuint programId);
};

#endif /* SHADER_HPP ======================================================== */
