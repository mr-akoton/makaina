#include <core/object/VAO.hpp>
#include <core/object/VBO.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VAO::VAO(void)
{
	glGenVertexArrays(1, &id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	VAO::linkAttrib(VBO &vbo, GLuint layout, GLuint ncomp, GLenum type,
						 GLsizeiptr stride, void *offset)
{
	vbo.bind();
	glVertexAttribPointer(layout, ncomp, type, GL_FALSE, stride, offset);
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

void	VAO::destroy(void)
{
	glDeleteVertexArrays(1, &id);
}
