#include <graphic/Texture.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void	ATexture::setFilter(GLuint filter)
{
	this->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	this->unbind();
}

void	ATexture::setWrap(GLuint wrap)
{
	this->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	this->unbind();
}

void	ATexture::setWrapBorderColor(Vector4 color)
{
	this->bind();
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(color));
	this->unbind();
}

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