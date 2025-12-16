#ifndef MESH_HPP
# define MESH_HPP

# include <glm/glm.hpp>

# include <core/Object.hpp>
# include <core/Camera.hpp>
# include <core/Shader.hpp>

/* ========================================================================== */
/*                                    MESH                                    */
/* ========================================================================== */

class	Mesh
{
	protected	:
		VAO			_vao;
		IndiceList	_indices;
	
	public		:
		void			draw(Shader& shader, Camera& camera);
		virtual void	assignBuffer(void) = 0;
};

/* ========================================================================== */
/*                                STANDARD MESH                               */
/* ========================================================================== */

class	StandardMesh: public Mesh
{
	private	:
		VertexList	_vertices;

	public	:
		StandardMesh(void);
		StandardMesh(VertexList& vertices, IndiceList& indices);
		~StandardMesh();

		StandardMesh&	operator=(const StandardMesh& instance);

		void	assignBuffer(void);
};

/* ========================================================================== */
/*                                  FLAT MESH                                 */
/* ========================================================================== */

class	FlatMesh: public Mesh
{
	private	:
		VertexFlatList	_vertices;

	public	:
		FlatMesh(void);
		FlatMesh(VertexFlatList& vertices, IndiceList& indices);
		~FlatMesh();

		FlatMesh&	operator=(const FlatMesh& instance);

		void	assignBuffer(void);
};

#endif /* MESH_HPP ========================================================== */
