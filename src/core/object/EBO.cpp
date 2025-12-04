#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

EBO::EBO(IndiceList& indices)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		indices.data(),
		GL_STATIC_DRAW
	);
}

EBO::~EBO()
{
	glDeleteBuffers(1, &id);
}

/* ========================================================================== */
/*                                  OPERATOR                                  */
/* ========================================================================== */

EBO&	EBO::operator=(const EBO& instance)
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

void	EBO::bind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void	EBO::unbind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
