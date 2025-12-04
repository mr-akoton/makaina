#include <graphic/Mesh.hpp>


/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Mesh::Mesh(void)
{
	
}

Mesh::Mesh(VertexList& vertices, IndiceList& indices, TextureList& textures):
	vertices(vertices),
	indices(indices),
	textures(textures)
{
	_assignBuffer();
}

Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
	textures.clear();
}

/* ========================================================================== */
/*                                  OPERATOR                                  */
/* ========================================================================== */

Mesh&	Mesh::operator=(const Mesh& instance)
{
	if (this != &instance)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->_assignBuffer();
	}
	return *this;
}

/* ========================================================================== */
/*                                  METHODES                                  */
/* ========================================================================== */

void	Mesh::draw(Shader& shader, Camera& camera, const char* renderType)
{
	shader.enable();
	vao.bind();

	unsigned int	ndiffuse = 0;
	unsigned int	nspecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string	num;
		std::string	type = textures[i].type;
		
		if (type == "diffuse")
		{
			num = std::to_string(ndiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(nspecular++);
		}

		textures[i].textureUnit(shader, (type + num).c_str(), i);
		textures[i].bind();
	}

	shader.setVec3("cameraPosition", camera.position);
	camera.updateShaderMatrix(shader, "cameraMatrix");

	if (std::string(renderType) == "element")
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else if (std::string(renderType) == "buffer")
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
}

void	Mesh::_assignBuffer(void)
{
	vao.bind();

	VBO vbo(vertices);
	EBO ebo(indices);

	vao.linkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex),
		(void *)0);
	vao.linkAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex),
		(void *)(3 * sizeof(float)));
	vao.linkAttribute(vbo, 2, 3, GL_FLOAT, sizeof(Vertex),
		(void *)(6 * sizeof(float)));
	vao.linkAttribute(vbo, 3, 2, GL_FLOAT, sizeof(Vertex),
		(void *)(9 * sizeof(float)));

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}
