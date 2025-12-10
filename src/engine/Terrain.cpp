#include <engine/Terrain.hpp>

#include <iostream>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Terrain::Terrain(
	unsigned int	width,
	unsigned int	height,
	unsigned int	gridSize,
	Vector3			position = Vector3(0.0f)
):
	width(width),
	height(height),
	gridSize(gridSize),
	mesh(width, height, gridSize),
	heightFactor(250),
	position(position),
	model(1.0f)
{
	model = glm::translate(model, position);
}

Terrain::~Terrain()
{
	delete noiseTexture;
}


/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Terrain::initNoiseTexture(unsigned int width, unsigned int height)
{
	noiseTexture = new NoiseTexture(noise, width, height, 0, GL_RED, GL_FLOAT);
	
	if (this->shader != nullptr)
	{
		noiseTexture->textureUnit(*shader, "heightMap", 0);
	}
}

void	Terrain::setNoiseType(FastNoiseLite::NoiseType type)
{
	noise.SetNoiseType(type);
}

void	Terrain::setNoiseFrequency(float frequency)
{
	noise.SetFrequency(frequency);
}

void	Terrain::setNoiseFractalType(FastNoiseLite::FractalType type)
{
	noise.SetFractalType(type);
}

void	Terrain::setNoiseFractalParameters(
	int		octaves,
	float	lacunarity,
	float	gain
)
{
	noise.SetFractalOctaves(octaves);
	noise.SetFractalLacunarity(lacunarity);
	noise.SetFractalGain(gain);
}

void	Terrain::setNoiseTextureUV(
	unsigned int	noiseWidth,
	unsigned int	noiseHeight
)
{
	for (unsigned int z = 0; z < height; z++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			unsigned int	i = (z * width) + x;
			
			mesh.vertices[i].textureUV = Vector2(
				static_cast<float>(x) / (noiseWidth - 1),
				static_cast<float>(z) / (noiseHeight - 1)
			);
		}
	}

	mesh._assignBuffer();
}

void	Terrain::setShader(Shader* shader)
{
	this->shader = shader;
}


void	Terrain::draw(Camera& camera, Vector4 clipPlane)
{
	if (shader != nullptr)
	{
		shader->enable();
		shader->setMat4("model", model);
		shader->setVec4("clipPlane", clipPlane);
		camera.updateShaderMatrix(*shader, "cameraMatrix");
		
		glEnable(GL_CLIP_DISTANCE0);
		mesh.draw(*shader, camera);
		glDisable(GL_CLIP_DISTANCE0);
	}
	else
	{
		std::cerr << "Warning: no shader was assign for this draw call" << std::endl;
	}
}
