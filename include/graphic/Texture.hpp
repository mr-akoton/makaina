#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include <glad/glad.h>
# include <noise/FastNoiseLite.h>

# include <core/Shader.hpp>

# include <algorithm>

/* ========================================================================== */
/*                                BASE TEXTURE                                */
/* ========================================================================== */

class	ATexture
{
	public	:
		int			width;
		int			height;
		int			channel;
		GLuint		id;
		GLuint		unit;
		const char*	type;

	public	:
		ATexture(int width, int height, GLuint slot, const char* type);
		virtual ~ATexture();

		void	setFilter(GLuint filter);
		void	setWrap(GLuint wrap);
		void	setWrapBorderColor(Vector4 color);
		void	textureUnit(Shader& shader, const char* uniform, GLuint unit);

		void	bind(void);
		void	unbind(void);
};

/* ========================================================================== */
/*                               GENERAL TEXTURE                              */
/* ========================================================================== */

class	Texture: public ATexture
{
	public	:
		Texture(
			const char*	file,
			const char*	type,
			GLuint		slot,
			GLenum		format,
			GLenum		pixType
		);

		~Texture();
};

/* ========================================================================== */
/*                                NOISE TEXTURE                               */
/* ========================================================================== */

class	NoiseTexture: public ATexture
{
	public	:
		NoiseTexture(
			const FastNoiseLite&	noise,
			int						width,
			int						height,
			GLuint					slot,
			GLenum					format,
			GLenum					pixType
		);

		~NoiseTexture();
};

/* ========================================================================== */
/*                             FRAMEBUFFER TEXTURE                            */
/* ========================================================================== */

class	FramebufferTexture: public ATexture
{
	public	:
		FramebufferTexture(
			int		width,
			int		height,
			GLuint	slot,
			GLenum	internalFormat,
			GLenum	format,
			GLenum	pixType
		);

		~FramebufferTexture();
};

#endif /* TEXTURE_HPP ======================================================= */
