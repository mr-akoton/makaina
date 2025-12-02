#ifndef FLAT_MESH_HPP
# define FLAT_MESH_HPP

# include <graphic/Mesh.hpp>


class	FlatMesh: public Mesh
{
	public	:
		unsigned int	width;
		unsigned int	height;
		unsigned int	gridSize;

	public	:
		FlatMesh(void);
		FlatMesh(
			unsigned int	width,
			unsigned int	height,
			unsigned int	gridSize
		);
		~FlatMesh();
		
		FlatMesh&	operator=(const FlatMesh& instance);

	private	:
		void	_initMesh(void);
};

#endif /* FLAT_MESH_HPP ===================================================== */
