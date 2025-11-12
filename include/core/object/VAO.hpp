#ifndef VAO_HPP
# define VAO_HPP

# include <glad/glad.h>


class	VBO;

class	VAO
{
	public	:
		GLuint	id;

	
	public	:
		VAO(void);

		void	linkAttrib(VBO &vbo, GLuint layout, GLuint ncomp, GLenum type,
							GLsizeiptr stride, void *buffer);
		void	bind(void);
		void	unbind(void);
		void	destroy(void);
};

#endif // VAO_HPP
