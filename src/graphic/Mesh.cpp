#include <graphic/Mesh.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Mesh::Mesh(void):
	vertices(std::vector<Vertex>()),
	indices(std::vector<GLuint>()),
	textures(std::vector<Texture>())
{
	/* Do nothing */
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices,
		   std::vector<Texture> &textures):
	vertices(vertices), indices(indices), textures(textures)
{
	_assignBuffer();
}

/* ========================================================================== */
/*                                  OPERATOR                                  */
/* ========================================================================== */

Mesh	&Mesh::operator=(const Mesh &instance)
{
	if (this != &instance)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		_assignBuffer();
	}
	return *this;
}


/* ========================================================================== */
/*                                  METHODES                                  */
/* ========================================================================== */

void	Mesh::set(std::vector<Vertex> &vertices, std::vector<GLuint> &indices,
			 		std::vector<Texture> &textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	_assignBuffer();
}

void	Mesh::draw(Shader &shader, Camera &camera)
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

		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].bind();
	}

	shader.setVec3("camPos", camera.position);
	camera.updateShaderMatrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void	Mesh::destroy(void)
{
	vertices.clear();
	indices.clear();
	textures.clear();
	vao.destroy();
}


void	Mesh::_assignBuffer(void)
{
	vao.bind();

	VBO	vbo(vertices);
	EBO	ebo(indices);

	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);						// Position
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));	// Normal
	vao.linkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));	// Color
	vao.linkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(9 * sizeof(float)));	// Texture UV

	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	vbo.destroy();
	ebo.destroy();
}
