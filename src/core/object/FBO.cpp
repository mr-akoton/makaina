#include <core/Object.hpp>
#include <iostream>

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

void	FBO::bind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void	FBO::unbind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void	FBO::attachTexture(FramebufferTexture& texture, GLenum attachment)
{
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		attachment,
		GL_TEXTURE_2D,
		texture.id,
		0
	);
}

void	FBO::attachRenderbuffer(RBO& rbo)
{
	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER,
		GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER,
		rbo.id
	);
}

void	FBO::checkAttachements(void) const
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
}