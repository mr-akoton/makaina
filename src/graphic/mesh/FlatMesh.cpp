#include <graphic/FlatMesh.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESCRUCTOR                         */
/* ========================================================================== */

FlatMesh::FlatMesh(void):
	Mesh(),
	width(1),
	height(1),
	gridSize(1)
{
	_initMesh();
}

FlatMesh::FlatMesh(
	unsigned int	width,
	unsigned int	height,
	unsigned int	gridSize	
):
	Mesh(),
	width(width),
	height(height),
	gridSize(gridSize)
{
	_initMesh();
}

FlatMesh::~FlatMesh()
{
	/* Do nothing */
}

FlatMesh&	FlatMesh::operator=(const FlatMesh& instance)
{
	if (this != &instance)
	{
		this->Mesh::operator=(instance);
		width = instance.width;
		height = instance.height;
		gridSize = instance.gridSize;
	}
	return *this;
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

void	FlatMesh::_initMesh(void)
{
	for (unsigned int z = 0; z < width; z++)
	{
		for (unsigned int x = 0; x < height; x++)
		{
			vertices.push_back({
				Vertex({
					Vector3(x * gridSize, 0.0f, z * gridSize),
					Vector3(0.0f, 1.0f, 0.0f),
					Vector3(0.36f, 0.36f, 0.49f),
					Vector2(0.0f)
				})
			});


			if (x != width - 1 and z != height - 1)
			{
				int	i = (z * width) + x;

				indices.push_back(i);
				indices.push_back(i + width);
				indices.push_back(i + 1);

				indices.push_back(i + 1);
				indices.push_back(i + width);
				indices.push_back(i + width + 1);
			}
		}
	}

	_assignBuffer();
}
