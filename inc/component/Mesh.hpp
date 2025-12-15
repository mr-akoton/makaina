#ifndef MESH_HPP
# define MESH_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <core/Object.hpp>

/* ========================================================================== */
/*                                    MESH                                    */
/* ========================================================================== */

class	Mesh
{
	private	:
		VAO			_vao;
		VertexList	_vertices;
		IndicesList	_indices;
	
	public	:
		Mesh(void);
		Mesh(VertexList& vertices, IndicesList& indices);
		~Mesh();

		void	assignBuffer(void);
		void	draw(Camera& camera);
};

/* ========================================================================== */
/*                                  FLAT MESH                                 */
/* ========================================================================== */

class	FlatMesh: public Mesh
{
	private	:
		VAO				_vao;
		VertexFlatList	_vertices;
		IndicesList		_indices;

	public	:
		FlatMesh(void);
		FlatMesh(VertexFlatList& vertices, IndicesList& indices);
		~FlatMesh();
	
		void	assignBuffer(void);
		void	draw(Camera& camera);
};

#endif /* MESH_HPP ========================================================== */
