#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include <glad/glad.h>
# include <noise/FastNoiseLite.h>

# include <core/Shader.hpp>

# include <algorithm>

class	Texture
{
	public	:
		int			width;
		int			height;
		int			channel;
		GLuint		id;
		GLuint		unit;
		const char*	type;

	
	public	:
		Texture(
			const char*	file,
			const char*	texType,
			GLuint		slot,
			GLenum		format,
			GLenum		pixType
		);
		Texture(
			FastNoiseLite const& noise,
			int		width,
			int		height,
			GLuint	slot,
			GLenum	format,
			GLenum	pixType
		);
		~Texture();
		
		void	textureUnit(Shader& shader, const char* uniform, GLuint unit);
		void	bind(void);
		void	unbind(void);
};

#endif /* TEXTURE_HPP ======================================================= */
