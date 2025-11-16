#ifndef TYPES_HPP
# define TYPES_HPP

# include <glm/glm.hpp>

/* ========================================================================== */
/*                                  CONSTANT                                  */
/* ========================================================================== */

enum FunctionReturn
{
	failure	= -1,
	success	=  0,
};

/* ========================================================================== */
/*                                 MATHEMATIC                                 */
/* ========================================================================== */

typedef glm::vec2	Vector2;
typedef glm::vec3	Vector3;
typedef glm::vec4	Vector4;

typedef glm::mat2	Matrix2;
typedef glm::mat3	Matrix3;
typedef glm::mat4	Matrix4;

#endif /* TYPES_HPP ========================================================= */
