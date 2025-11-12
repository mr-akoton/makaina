#include <world/World.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

World::World(Camera &camera, Shader &shader):
	camera(camera), shader(shader)
{
	/* Do nothing */
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	World::addObject(Mesh &object)
{
	objectList.push_back(object);
}

void	World::addObject(std::vector<Mesh> &objects)
{
	objectList.insert(objectList.end(), objects.begin(), objects.end());
}

void	World::clear(void)
{
	objectList.clear();
}

void	World::render(void)
{
	for (std::vector<Mesh>::iterator it = objectList.begin();
		 it != objectList.end(); it++)
	{
		it->draw(shader, camera);
	}
}

