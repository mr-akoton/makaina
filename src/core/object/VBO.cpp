#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VBO::VBO(const float* vertices, size_t size, GLenum usage)
{
	glGenBuffers(1, &_id);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	this->unbind();
}

VBO::VBO(VertexList& vertices, GLenum usage)
{
	glGenBuffers(1, &_id);
	this->bind();
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		vertices.data(),
		usage
	);
	this->unbind();
}

VBO::VBO(VertexFlatList& vertices, GLenum usage)
{
	glGenBuffers(1, &_id);
	this->bind();
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(VertexFlat),
		vertices.data(),
		usage
	);
	this->unbind();
}

VBO::~VBO()
{
	glDeleteBuffers(1, &_id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	VBO::bind(void) const
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void	VBO::unbind(void) const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
