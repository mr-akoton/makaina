#ifndef VBO_HPP
# define VBO_HPP

# include <glad/glad.h>
# include <glm/glm.hpp>

# include <vector>


struct	Vertex
{
	glm::vec3	position;
	glm::vec3	normal;
	glm::vec3	color;
	glm::vec2	texUV;
};

class	VBO
{
	public	:
		GLuint	id;

	
	public	:
		VBO(std::vector<Vertex> &vertices);

		void	bind(void);
		void	unbind(void);
		void	destroy(void);
};

#endif // VBO_HPP
