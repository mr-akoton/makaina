#include <engine/Water.hpp>

#include <iostream>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Water::Water(
	unsigned int	width,
	unsigned int	height,
	unsigned int	gridSize,
	Vector3			position,
	Vector3			color
):
	width(width),
	height(height),
	gridSize(gridSize),
	mesh(width, height, gridSize),
	color(color),
	position(position),
	model(1.0f)
{
	model = glm::translate(model, position);

	for (auto& vertex: mesh.vertices)
	{
		vertex.color = color;
	}

	mesh._assignBuffer();
}

Water::~Water()
{
	delete	reflectionTexture;
}

/* ========================================================================== */
/*                       REFLECTION AND REFRACTION LOGIC                      */
/* ========================================================================== */

void	Water::initReflection(Window& window)
{
	reflectionFBO.bind();
	reflectionTexture = new FramebufferTexture(window.width, window.height, 1, GL_RGB, GL_RGB, GL_FLOAT);
	reflectionTexture->setFilter(GL_LINEAR);
	reflectionFBO.attachTexture(*reflectionTexture, GL_COLOR_ATTACHMENT0);
	
	reflectionRBO.bind();
	reflectionRBO.setStorage(window.width, window.height);
	reflectionRBO.unbind();
	reflectionFBO.attachRenderbuffer(reflectionRBO);

	reflectionFBO.checkAttachements();
	reflectionFBO.unbind();
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Water::initNoiseTexture(unsigned int width, unsigned int height)
{
	noiseTexture = new NoiseTexture(noise, width, height, 0, GL_RED, GL_FLOAT);
	
	if (this->shader != nullptr)
	{
		noiseTexture->textureUnit(*shader, "heightMap", 0);
	}
}

void	Water::setNoiseType(FastNoiseLite::NoiseType type)
{
	noise.SetNoiseType(type);
}

void	Water::setNoiseFrequency(float frequency)
{
	noise.SetFrequency(frequency);
}

void	Water::setNoiseFractalType(FastNoiseLite::FractalType type)
{
	noise.SetFractalType(type);
}

void	Water::setNoiseFractalParameters(
	int		octaves,
	float	lacunarity,
	float	gain
)
{
	noise.SetFractalOctaves(octaves);
	noise.SetFractalLacunarity(lacunarity);
	noise.SetFractalGain(gain);
}

void	Water::setNoiseTextureUV(
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

void	Water::setShader(Shader* shader)
{
	this->shader = shader;
}


void	Water::draw(Camera& camera)
{
	if (shader != nullptr)
	{
		shader->enable();
		shader->setMat4("model", model);
		camera.updateShaderMatrix(*shader, "cameraMatrix");

		mesh.draw(*shader, camera);
	}
	else
	{
		std::cerr << "Warning: no shader was assign for this draw call" << std::endl;
	}
}