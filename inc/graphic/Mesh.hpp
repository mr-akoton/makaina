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
		Mesh(void);
		Mesh(IndiceList& indices);
		~Mesh();

		virtual void	draw(Shader& shader, Camera& camera) = 0;
		virtual void	assignBuffer(void) = 0;
};

/* ========================================================================== */
/*                                STANDARD MESH                               */
/* ========================================================================== */

class	MeshBasic: public Mesh
{
	private	:
		VertexList	_vertices;

	public	:
		MeshBasic(void);
		MeshBasic(VertexList& vertices, IndiceList& indices);
		~MeshBasic();

		void	assignBuffer(void);
		void	draw(Shader& shader, Camera& camera);
};

/* ========================================================================== */
/*                                  FLAT MESH                                 */
/* ========================================================================== */

class	MeshFlat: public Mesh
{
	private	:
		VertexFlatList	_vertices;

	public	:
		MeshFlat(void);
		MeshFlat(
			int width,
			int height,
			float gridScale = 1.0f
		);
		~MeshFlat();

		void	setData(int row, int col, float distance);
		void	setNoiseUV(size_t vertexIndex, Vector2 noiseUV);
		void	assignBuffer(void);
		void	draw(Shader& shader, Camera& camera);
};

#endif /* MESH_HPP ========================================================== */
