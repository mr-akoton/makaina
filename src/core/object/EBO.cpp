#include <core/object/EBO.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

EBO::EBO(std::vector<GLuint> &indices):
	id(-1)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
				 indices.data(), GL_STATIC_DRAW);
}


/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	EBO::bind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void	EBO::unbind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void	EBO::destroy(void)
{
	glDeleteBuffers(1, &id);
}
