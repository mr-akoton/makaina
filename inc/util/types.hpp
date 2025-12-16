#ifndef TYPES_HPP
# define TYPES_HPP

# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <vector>

/* -------------------------------- Enumerate ------------------------------- */

enum FunctionReturn
{
	failure = -1,
	success = 0
};

/* -------------------------------- Variable -------------------------------- */

typedef glm::vec4	Vector2;
typedef glm::vec3	Vector3;
typedef glm::vec4	Vector4;
typedef glm::ivec2	Vectori2;
typedef glm::ivec3	Vectori3;
typedef glm::ivec4	Vectori4;
typedef glm::mat2	Matrix2;
typedef glm::mat3	Matrix3;
typedef glm::mat4	Matrix4;
typedef glm::vec3	Color3;
typedef glm::vec4	Color4;

struct Vertex
{
	Vector3	position;
	Vector3 normal;
	Color3	color;
	Vector2	textureUV;
};

struct VertexFlat
{
	Vector3 position;
	Vector2	noiseUV;
};

typedef std::vector<Vertex>		VertexList;
typedef std::vector<VertexFlat>	VertexFlatList;
typedef std::vector<GLuint>		IndiceList;

#endif /* TYPES_HPP ========================================================= */
