#ifndef WATER_HPP
# define WATER_HPP

# include <graphic/Mesh.hpp>

class	Water
{
	public	:
		int		width;
		int		height;
		float	gridSize;

		Mesh	mesh;

		Vector3 color;
		Vector3	position;
		Matrix4	model;

	public	:
		Water(int width, int height, float gridSize, Vector3 color);

		void	setPosition(Vector3 position);
		void	render(Shader& shader, Camera& camera);
};

#endif /* WATER_HPP ========================================================= */
