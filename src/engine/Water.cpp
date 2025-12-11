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
	delete noiseTexture;
	delete reflectionTexture;
	delete refractionTexture;
}

/* ========================================================================== */
/*                       REFLECTION AND REFRACTION LOGIC                      */
/* ========================================================================== */

void	Water::initEffects(Window& window)
{
	// Reflection //
	reflectionFBO.bind();
	
	reflectionTexture = new FramebufferTexture(window.width, window.height, 1, GL_RGB, GL_RGB, GL_FLOAT);
	reflectionTexture->setFilter(GL_LINEAR);
	reflectionFBO.attachTexture(*reflectionTexture, GL_COLOR_ATTACHMENT0);

	reflectionDepthTexture = new FramebufferTexture(window.width, window.height, 0, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT);
	reflectionDepthTexture->setFilter(GL_NEAREST);
	reflectionDepthTexture->setWrap(GL_CLAMP_TO_BORDER);
	reflectionDepthTexture->setWrapBorderColor(Vector4(0.0f));
	reflectionFBO.attachTexture(*reflectionDepthTexture, GL_DEPTH_ATTACHMENT);

	reflectionFBO.checkAttachements();
	reflectionFBO.unbind();

	// Refraction //
	refractionFBO.bind();

	refractionTexture = new FramebufferTexture(window.width, window.height, 2, GL_RGB, GL_RGB, GL_FLOAT);
	refractionTexture->setFilter(GL_LINEAR);
	refractionFBO.attachTexture(*refractionTexture, GL_COLOR_ATTACHMENT0);

	refractionDepthTexture = new FramebufferTexture(window.width, window.height, 0, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT);
	refractionDepthTexture->setFilter(GL_NEAREST);
	refractionDepthTexture->setWrap(GL_CLAMP_TO_BORDER);
	refractionDepthTexture->setWrapBorderColor(Vector4(0.0f));
	refractionFBO.attachTexture(*refractionDepthTexture, GL_DEPTH_ATTACHMENT);

	refractionFBO.checkAttachements();
	refractionFBO.unbind();
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