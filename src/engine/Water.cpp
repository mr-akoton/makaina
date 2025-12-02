#include <engine/Water.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Water::Water(
	unsigned int	width,
	unsigned int	height,
	unsigned int	gridSize,
	Vector3			position = Vector3(0.0f)
):
	width(width),
	height(height),
	gridSize(gridSize),
	mesh(width, height, gridSize),
	position(position),
	model(1.0f)
{
	model = glm::translate(model, position);
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Water::draw(Shader& shader, Camera& camera)
{
	shader.enable();
	shader.setMat4("model", model);
	camera.updateShaderMatrix(shader, "cameraMatrix");

	mesh.draw(shader, camera);
}