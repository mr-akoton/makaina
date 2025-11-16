#ifndef MESH_HPP
# define MESH_HPP

# include <core/Object.hpp>
# include <core/Camera.hpp>
# include <core/Shader.hpp>
# include <graphic/Texture.hpp>

typedef std::vector<Texture>	TextureList;


class	Mesh
{
	public	:
		VAO	vao;

		VertexList	vertices;
		IndiceList	indices;
		TextureList	textures;
	
	public	:
		Mesh(void);
		Mesh(VertexList& vertices, IndiceList& indices, TextureList& textures);
		~Mesh();

		Mesh&	operator=(const Mesh& instance);

		void	set(
			VertexList& vertices,
			IndiceList& indices,
			TextureList& textures
		);
		void	draw(
			Shader& shader,
			Camera& camera,
			const char* renderType = "element"
		);
	
	public	:
		void	assignBuffer(void);
};

#endif /* MESH_HPP ========================================================== */
