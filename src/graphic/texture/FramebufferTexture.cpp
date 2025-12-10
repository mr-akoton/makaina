#include <graphic/Texture.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

FramebufferTexture::FramebufferTexture(
	int		width,
	int		height,
	GLuint	slot,
	GLenum	internalFormat,
	GLenum	format,
	GLenum	pixType
):
	ATexture(width, height, slot, "framebuffer")
{
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
	
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, pixType, nullptr);
}

FramebufferTexture::~FramebufferTexture()
{
	this->ATexture::~ATexture();
}
