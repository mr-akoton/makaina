#include <graphic/ScreenMesh.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

const static float	screenVertices[] = {
	-1.0f,  1.0f,		0.0f, 1.0f,
	-1.0f, -1.0f,		0.0f, 0.0f,
	 1.0f, -1.0f,		1.0f, 0.0f,
	 
	 1.0f,  1.0f,		1.0f, 1.0f,
	-1.0f,  1.0f,		0.0f, 1.0f,
	 1.0f, -1.0f,		1.0f, 0.0f,
};

ScreenMesh::ScreenMesh(void)
{
	vao.bind();

	VBO	vbo(screenVertices, sizeof(screenVertices));

	vao.linkAttribute(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void *)0);
	vao.linkAttribute(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void *)(2 * sizeof(float)));

	vao.unbind();
	vbo.unbind();
}

ScreenMesh::~ScreenMesh()
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	ScreenMesh::draw(Shader& shader, Camera&)
{
	vao.bind();
	shader.enable();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
