#include <component/Mesh.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

StandardMesh::StandardMesh(void)
{
	/* Do nothing */
}

StandardMesh::StandardMesh(VertexList& vertices, IndiceList& indices):
	_indices(indices),
	_vertices(vertices)
{

}
