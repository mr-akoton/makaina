#ifndef SCREEN_MESH_HPP
# define SCREEN_MESH_HPP

# include <core/Object.hpp>
# include <core/Shader.hpp>
# include <core/Camera.hpp>


class	ScreenMesh
{
	public	:
		VAO	vao;

	public	:
		ScreenMesh(void);
		~ScreenMesh();

		void	draw(Shader& shader, Camera& camera);
};

#endif /* SCREEN_MESH_HPP =================================================== */
