#include <graphic/Texture.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

NoiseTexture::NoiseTexture(
	const FastNoiseLite&	noise,
	int						width,
	int						height,
	GLuint					slot,
	GLenum					format,
	GLenum					pixType
):
	ATexture(width, height, slot, "noise")
{
	std::vector<float>	noiseData;
	
	for	(int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			noiseData.push_back(noise.GetNoise((float)x, (float)y));
		}
	}

	float	minNoiseValue = *std::min_element<std::vector<float>::iterator>(
		noiseData.begin(),
		noiseData.end()
	);
	float	maxNoiseValue = *std::max_element<std::vector<float>::iterator>(
		noiseData.begin(),
		noiseData.end()
	);

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

NoiseTexture::~NoiseTexture()
{
	this->ATexture::~ATexture();
}
