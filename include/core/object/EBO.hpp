#ifndef EBO_HPP
# define EBO_HPP

# include <glad/glad.h>
# include <vector>


class	EBO
{
	public	:
		GLuint	id;

	
	public	:
		EBO(std::vector<GLuint> &indices);
		
		void	bind(void);
		void	unbind(void);
		void	destroy(void);
};

#endif // EBO_HPP
