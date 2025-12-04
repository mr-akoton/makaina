#include <core/Object.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

FBO::FBO(void)
{
	glGenFramebuffers(1, &id);
}

FBO::~FBO()
{
	glDeleteFramebuffers(1, &id);
}

/* ========================================================================== */
/*                                  OPERATOR                                  */
/* ========================================================================== */

FBO&	FBO::operator=(const FBO& instance)
{
	if (this != &instance)
	{
		glDeleteFramebuffers(1, &id);
		id = instance.id;
	}
	return *this;
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	FBO::attachTexture(Texture& texture)
{
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D,
		texture.id,
		0
	);
}

void	FBO::bind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void	FBO::unbind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
