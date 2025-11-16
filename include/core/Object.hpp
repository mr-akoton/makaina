#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <glad/glad.h>
# include <utils/types.hpp>

# include <vector>

/* ========================================================================== */
/*                                  VARIABLES                                 */
/* ========================================================================== */

class	VAO;
class	VBO;
class	EBO;

struct	Vertex
{
	Vector3	position;
	Vector3	normal;
	Vector3	color;
	Vector2	textureUV;
};

typedef	std::vector<Vertex>	VertexList;
typedef std::vector<GLuint>	IndiceList;

/* ========================================================================== */
/*                             VERTEX ARRAY OBJECT                            */
/* ========================================================================== */

class	VAO
{
	public	:
		GLuint	id;
	
	public	:
		VAO(void);
		~VAO();

		void	bind(void);
		void	unbind(void);
		void	linkAttribute(
			VBO&		vbo,
			GLuint		layout,
			GLuint		size,
			GLenum		type,
			GLsizeiptr	stride,
			void*		offset
		);
};

/* ========================================================================== */
/*                            VERTEX BUFFER OBJECT                            */
/* ========================================================================== */

class	VBO
{
	public	:
		GLuint	id;
	
	public	:
		VBO(VertexList& vertices);
		~VBO();

		void	bind(void);
		void	unbind(void);
};

/* ========================================================================== */
/*                            ELEMENT VERTEX OBJECT                           */
/* ========================================================================== */

class	EBO
{
	public	:
		GLuint	id;
	
	public	:
		EBO(IndiceList& indices);
		~EBO();

		void	bind(void);
		void	unbind(void);
};

#endif /* OBJECT_HPP ======================================================== */
