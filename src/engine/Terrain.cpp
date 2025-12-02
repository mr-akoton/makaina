#include <engine/Terrain.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Terrain::Terrain(
	unsigned int	width,
	unsigned int	height,
	unsigned int	gridSize
):
	width(width),
	height(height),
	gridSize(gridSize),
	shader(
		"shader/terrain-vertex.glsl",
		"shader/terrain-fragment.glsl",
		"shader/terrain-geometry.glsl"
	)
{

}
