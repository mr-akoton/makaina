#include <core/object/VBO.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VBO::VBO(std::vector<Vertex> &vertices)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
				 vertices.data(), GL_STATIC_DRAW);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	VBO::bind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void	VBO::unbind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	VBO::destroy(void)
{
	glDeleteBuffers(1, &id);
}
