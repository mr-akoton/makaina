#include <graphic/Mesh.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

MeshFlat::MeshFlat(void):
	Mesh()
{

	this->setData(10, 10, 1.0f);
}

MeshFlat::MeshFlat(int width, int height, float gridScale)
{
	this->setData(width, height, gridScale);
}

MeshFlat::~MeshFlat()
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	MeshFlat::assignBuffer(void)
{
	_vao.bind();

	VBO	vbo(_vertices, GL_DYNAMIC_DRAW);
	vbo.bind();
	EBO	ebo(_indices);
	ebo.bind();

	_vao.linkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(VertexFlat),
		(void *)0);
	_vao.linkAttribute(vbo, 1, 2, GL_FLOAT, sizeof(VertexFlat), 
		(void *)(3 * sizeof(float)));
	
	_vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

#include <iostream>

void	MeshFlat::setData(int row, int col, float distance)
{
	for (int z = 0; z < col; z++)
	{
		for (int x = 0; x < row; x++)
		{
			_vertices.push_back(
				VertexFlat({
					Vector3(x * distance, 0.0f, z * distance),
					Vector2(0.0f)
				})
			);


			if (x < col - 1 and z < row - 1)
			{
				int	i = (z * col) + x;

				std::cout << _vertices[i].position.x << " " << _vertices[i].position.z << std::endl;

				_indices.push_back(i);
				_indices.push_back(i + row);
				_indices.push_back(i + 1);

				_indices.push_back(i + 1);
				_indices.push_back(i + row);
				_indices.push_back(i + row + 1);
			}
		}
	}

	this->assignBuffer();
}

void	MeshFlat::setNoiseUV(size_t vertexIndex, Vector2 noiseUV)
{
	if (vertexIndex < _vertices.size())
		_vertices[vertexIndex].noiseUV = noiseUV;
}

void	MeshFlat::draw(Shader& shader, Camera& camera)
{
	_vao.bind();
	shader.enable();

	shader.setVec3("u_viewPosition", camera.position);
	camera.updateShaderMatrix(shader, "u_projection");

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}
