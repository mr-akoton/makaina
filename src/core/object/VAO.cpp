#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VAO::VAO(void)
{
	glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void VAO::linkAttribute(
	VBO&		vbo,
	GLuint		layout,
	GLuint		size,
	GLenum		type,
	GLsizeiptr	stride,
	void*		offset
)
{
	vbo.bind();
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}

void	VAO::bind(void)
{
	glBindVertexArray(id);
}

void	VAO::unbind(void)
{
	glBindVertexArray(0);
}
