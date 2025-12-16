#include <graphic/Mesh.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Mesh::Mesh(void)
{
	/* Do nothing */
}

Mesh::Mesh(IndiceList& indices):
	_indices(indices)
{
	/* Do nothing */
}

Mesh::~Mesh()
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	Mesh::draw(Shader& shader, Camera& camera)
{
	_vao.bind();
	shader.enable();

	shader.setVec3("u_viewPosition", camera.position);
	camera.updateShaderMatrix(shader, "u_projection");

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}
