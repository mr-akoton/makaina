#ifndef TYPES_HPP
# define TYPES_HPP

# include <glm/glm.hpp>

enum FunctionReturn
{
	failure = -1,
	success = 0
};

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

#endif /* TYPES_HPP ========================================================= */
