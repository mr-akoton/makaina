#ifndef	TERRAIN_HPP
# define TERRAIN_HPP

# include <glm/glm.hpp>
# include <noise/FastNoiseLite.h>

# include <graphic/Mesh.hpp>


class	Terrain
{
	public	:
		int		width;
		int		height;
		int		gridSize;
		float	amplitude;

		Mesh			mesh;
		FastNoiseLite	noise;

		glm::mat4	model;
		glm::vec3	position;


	public	:
		Terrain(int width, int height, int gridSize, float amplitude);

		void	setPosition(glm::vec3 position);
		void	generateTerrain(void);

		void	render(Shader &shader, Camera &camera);
};

#endif // TERRAIN_HPP
