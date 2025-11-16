#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VBO::VBO(VertexList& vertices)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		vertices.data(),
		GL_STATIC_DRAW
	);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &id);
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
