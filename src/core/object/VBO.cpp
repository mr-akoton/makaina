#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VBO::VBO(const float* vertices, size_t size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

VBO::VBO(VertexList& vertices)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		vertices.data(),
		GL_DYNAMIC_DRAW
	);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &id);
}

/* ========================================================================== */
/*                                  OPERATOR                                  */
/* ========================================================================== */

VBO&	VBO::operator=(const VBO& instance)
{
	if (this != &instance)
	{
		glDeleteBuffers(1, &id);
		id = instance.id;
	}
	return *this;
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
