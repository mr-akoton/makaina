#ifndef WORLD_HPP
# define WORLD_HPP

# include <graphic/Mesh.hpp>
# include <core/Camera.hpp>
# include <core/Shader.hpp>
# include <vector>

class	World
{
	public	:
		Camera				camera;
		Shader				shader;
		std::vector<Mesh>	objectList;


	public	:
		World(Camera &camera, Shader &shader);

		void	addObject(Mesh &object);
		void	addObject(std::vector<Mesh> &objects);
		void	clear(void);
		void	render(void);
};

Mesh	getRandomTerrainMesh(int width, int height, int gridSize);

# endif // WORLD_HPP
