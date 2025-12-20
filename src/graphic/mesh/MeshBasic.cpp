#include <graphic/Mesh.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

MeshBasic::MeshBasic(void):
	Mesh()
{
	/* Do nothing */
}

MeshBasic::MeshBasic(VertexList& vertices, IndiceList& indices):
	Mesh(indices),
	_vertices(vertices)
{
	this->assignBuffer();
}

MeshBasic::~MeshBasic()
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	MeshBasic::assignBuffer(void)
{
	_vao.bind();

	VBO vbo(_vertices, GL_STATIC_DRAW);
	vbo.bind();
	EBO ebo(_indices);
	ebo.bind();

	_vao.linkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex),
		(void *)0);
	_vao.linkAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex),
		(void *)(3 * sizeof(float)));
	_vao.linkAttribute(vbo, 2, 3, GL_FLOAT, sizeof(Vertex),
		(void *)(6 * sizeof(float)));
	_vao.linkAttribute(vbo, 3, 2, GL_FLOAT, sizeof(Vertex),
		(void *)(9 * sizeof(float)));

	_vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

void	MeshBasic::draw(Shader& shader, Camera& camera)
{
	_vao.bind();
	shader.enable();

	shader.setVec3("u_viewPosition", camera.position);
	camera.updateShaderMatrix(shader, "u_projection");

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}
