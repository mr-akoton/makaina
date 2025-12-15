#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VAO::VAO(void)
{
	glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &_id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	VAO::bind(void) const
{
	glBindVertexArray(_id);
}

void	VAO::unbind(void) const
{
	glBindVertexArray(0);
}

void	VAO::linkAttribute(
	VBO& vbo,
	GLuint layout,
	GLuint size,
	GLenum type,
	GLsizeiptr stride,
	void* offset
) const
{
	vbo.bind();
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}
