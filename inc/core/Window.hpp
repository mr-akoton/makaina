#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <glad/glad.h>

# include <util/types.hpp>

class	Window
{
	private	:
		bool		_isInitialized;
		GLFWwindow*	_id;

	public	:
		GLuint	width;
		GLuint	height;

	public	:
		Window(void);
		~Window();

		int		init(
			GLuint width,
			GLuint height,
			const char* title = "Untitled"
		);
		void	update(void) const;
		void	pollEvents(void) const;
		void	clear(Color3 color, GLbitfield mask);
		void	close(void) const;
		void	destroy(void);

		bool	isOpen(void) const;
		bool	isKeyPressed(int key) const;
		bool	isKeyReleased(int key) const;
		bool	isButtonPressed(int button) const;
		bool	isButtonReleased(int button) const;
		void	getCursorPosition(double& x, double& y) const;
		
		void	setCursorPosition(double x, double y) const;
		void	hideCursor(void) const;
		void	resetCursor(void) const;
};

#endif /* WINDOW_HPP ======================================================== */
