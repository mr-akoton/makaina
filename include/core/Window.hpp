#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <util.hpp>


class	Window
{
	public	:
		int			width;
		int			height;
		GLFWwindow	*id;

	
	public	:
		Window(void);
		~Window(void);

		int		init(int width, int height, const char *title);
		void	close(void);
		void	update(void);
		void	destroy(void);

		bool	shouldClose(void) const;
		bool	isKeyPressed(int key) const;
		bool	isKeyReleased(int key) const;
		bool	isButtonPressed(int button) const;
		bool	isButtonReleased(int button) const;

		void	setCursorPos(double x, double y);
		void	getCursorPos(double &x, double &y);
		void	hideCursor(void);
		void	resetCursor(void);
};

#endif // WINDOW_HPP
