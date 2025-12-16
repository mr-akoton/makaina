#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include <glad/glad.h>
# include <noise/FastNoiseLite.h>

# include <core/Shader.hpp>

# include <algorithm>

/* ========================================================================== */
/*                                BASE TEXTURE                                */
/* ========================================================================== */

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
		Texture(int width, int height, GLuint slot, const char* type);
		virtual ~Texture();

		void	setFilter(GLuint filter);
		void	setWrap(GLuint wrap);
		void	setWrapBorderColor(Color4 color);
		void	textureUnit(Shader& shader, const char* uniform, GLuint unit);

		void	bind(void);
		void	unbind(void);
};

/* ========================================================================== */
/*                               GENERAL TEXTURE                              */
/* ========================================================================== */

class	TextureBasic: public Texture
{
	public	:
		TextureBasic(
			const char*	file,
			const char*	type,
			GLuint		slot,
			GLenum		format,
			GLenum		pixType
		);

		~TextureBasic();
};

/* ========================================================================== */
/*                                NOISE TEXTURE                               */
/* ========================================================================== */

class	TextureNoise: public Texture
{
	public	:
		TextureNoise(
			const FastNoiseLite&	noise,
			int						width,
			int						height,
			GLuint					slot,
			GLenum					format,
			GLenum					pixType
		);

		~TextureNoise();
};

/* ========================================================================== */
/*                             FRAMEBUFFER TEXTURE                            */
/* ========================================================================== */

class	TextureFramebuffer: public Texture
{
	public	:
		TextureFramebuffer(
			int		width,
			int		height,
			GLuint	slot,
			GLenum	internalFormat,
			GLenum	format,
			GLenum	pixType
		);

		~TextureFramebuffer();
};

#endif /* TEXTURE_HPP ======================================================= */
