#include <engine/Water.hpp>
#include <iostream>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Water::Water(
	int		width,
	int		height,
	int		gridSize,
	Shader&	shader,
	Vector3	position,
	Vector3	color
):
	width(width),
	height(height),
	gridSize(gridSize),
	shader(shader),
	mesh(width, height, gridSize),
	position(position),
	color(color),
	model(1.0f)
{
	model = glm::translate(model, position);

	for (Vertex& vertex: mesh.vertices)
	{
		vertex.color = color;
	}

	mesh._assignBuffer();
}

Water::~Water()
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Water::draw(Camera& camera)
{
	shader.enable();
	shader.setMat4("u_model", model);
	mesh.draw(shader, camera);
}


