#include <graphic/Texture.hpp>
#include <stb/stb_image.h>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Texture::Texture(
	const char*	file,
	const char*	texType,
	GLuint		slot,
	GLenum		format,
	GLenum		pixType
):
	unit(slot),
	type(texType)
{
	unsigned char*	bytes;

	stbi_set_flip_vertically_on_load(true);
	bytes = stbi_load(file, &width, &height, &channel, 0);

	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixType, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(
	const FastNoiseLite&	noise,
	int						width,
	int						height,
	GLuint					slot,
	GLenum					format,
	GLenum					pixType
):
	width(width),
	height(height),
	unit(slot),
	type("noise")
{
	std::vector<float>	noiseData;
	
	for	(int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			noiseData.push_back(noise.GetNoise((float)x, (float)y));
		}
	}

	float	minNoiseValue = *std::min_element<std::vector<float>::iterator>(noiseData.begin(), noiseData.end());
	float	maxNoiseValue = *std::max_element<std::vector<float>::iterator>(noiseData.begin(), noiseData.end());

	for (float& noiseValue: noiseData)
	{
		noiseValue = (noiseValue - minNoiseValue) / (maxNoiseValue - minNoiseValue);
	}

	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, format, pixType, noiseData.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Texture::textureUnit(Shader& shader, const char* uniform, GLuint unit)
{
	shader.enable();
	shader.setInt(uniform, unit);
}

void	Texture::bind(void)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void	Texture::unbind(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
