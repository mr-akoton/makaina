#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

RBO::RBO(void)
{
	glGenRenderbuffers(1, &id);
}

RBO::~RBO()
{
	glDeleteRenderbuffers(1, &id);
}

/* ========================================================================== */
/*                                  OPERATOR                                  */
/* ========================================================================== */

RBO&	RBO::operator=(const RBO& instance)
{
	if (this != &instance)
	{
		glDeleteRenderbuffers(1, &id);
		id = instance.id;
	}
	return *this;
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	RBO::bind(void)
{
	glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void	RBO::unbind(void)
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void	RBO::setStorage(unsigned int width, unsigned int height)
{
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}
