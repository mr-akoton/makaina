#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <util/types.hpp>

class	VAO;
class	VBO;
class	EBO;

/* ========================================================================== */
/*                             VERTEX ARRAY OBJECT                            */
/* ========================================================================== */

class	VAO
{
	private	:
		GLuint	_id;

	public	:
		VAO(void);
		~VAO();

		void	bind(void) const;
		void	unbind(void) const;
		void	linkAttribute(
			VBO& vbo,
			GLuint layout,
			GLuint size,
			GLenum type,
			GLsizeiptr stride,
			void* offset
		) const;
};

/* ========================================================================== */
/*                            VERTEX BUFFER OBJECT                            */
/* ========================================================================== */

class	VBO
{
	private	:
		GLuint	_id;

	public	:
		VBO(const float* vertices, size_t size, GLenum usage);
		VBO(VertexList& vertices, GLenum usage);
		VBO(VertexFlatList& vertices, GLenum usage);
		~VBO();

		void	bind(void) const;
		void	unbind(void) const;
};

/* ========================================================================== */
/*                            ELEMENT BUFFER OBJECT                           */
/* ========================================================================== */

class	EBO
{
	private	:
		GLuint	_id;

	public	:
		EBO(IndiceList& indices);
		~EBO();

		void	bind(void) const;
		void	unbind(void) const;
};

#endif /* OBJECT_HPP ======================================================== */
