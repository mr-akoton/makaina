#ifndef MESH_HPP
# define MESH_HPP

# include <glad/glad.h>
# include <vector>

# include <core/object/VAO.hpp>
# include <core/object/VBO.hpp>
# include <core/object/EBO.hpp>
# include <core/Camera.hpp>
# include <core/Shader.hpp>
# include <graphic/Texture.hpp>

class	Mesh
{
	public	:
		VAO	vao;

		std::vector<Vertex>		vertices;
		std::vector<GLuint>		indices;
		std::vector<Texture>	textures;

	
	public	:
		Mesh(void);
		Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices,
			 std::vector<Texture> &textures);

		Mesh	&operator=(const Mesh &instance);

		void	set(std::vector<Vertex> &vertices, std::vector<GLuint> &indices,
			 		std::vector<Texture> &textures);
		void	draw(Shader &shader, Camera &camera);
		void	destroy(void);
	
	public	:
		void	_assignBuffer(void);
};

#endif // MESH_HPP
