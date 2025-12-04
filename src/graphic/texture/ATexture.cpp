#include <graphic/Texture.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

ATexture::ATexture(int width, int height, GLuint slot, const char* type):
	width(width),
	height(height),
	unit(slot),
	type(type)
{

}

ATexture::~ATexture()
{
	glDeleteTextures(1, &id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	ATexture::textureUnit(Shader& shader, const char* uniform, GLuint unit)
{
	shader.enable();
	shader.setInt(uniform, unit);
}

void	ATexture::bind(void)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void	ATexture::unbind(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
