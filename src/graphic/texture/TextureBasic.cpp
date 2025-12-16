#include <graphic/Texture.hpp>
#include <stb/stb_image.h>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

TextureBasic::TextureBasic(
	const char*	file,
	const char*	type,
	GLuint		slot,
	GLenum		format,
	GLenum		pixType
):
	Texture(0, 0, slot, type)
{
	unsigned char*	bytes;

	stbi_set_flip_vertically_on_load(true);
	bytes = stbi_load(file, &width, &height, &channel, 0);

	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + unit);
	this->bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		format,
		pixType,
		bytes
	);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	this->unbind();
}

TextureBasic::~TextureBasic()
{
	this->Texture::~Texture();
}
