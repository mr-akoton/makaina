#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

EBO::EBO(IndiceList& indices)
{
	glGenBuffers(1, &_id);
	this->bind();
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		indices.data(),
		GL_STATIC_DRAW
	);
	this->unbind();
}

EBO::~EBO()
{
	glDeleteBuffers(1, &_id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	EBO::bind(void) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void	EBO::unbind(void) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
