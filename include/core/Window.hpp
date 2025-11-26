#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>

# include <string>


class	Window
{
	private	:
		GLFWwindow*		_id;

	public	:
		unsigned int	width;
		unsigned int	height;
 
	public	:
		Window(void);
		~Window();

		int		init(unsigned int width, unsigned int height, const char* title);
		void	close(void) const;
		void	update(void) const;
		void	destroy(void);

		bool	shouldClose(void) const;
		bool	isKeyPressed(int key) const;
		bool	isKeyReleased(int key) const;
		bool	isButtonPressed(int button) const;
		bool	isButtonReleased(int button) const;

		void	setCursorPos(double x, double y) const;
		void	getCursorPos(double& x, double& y) const;
		void	setWindowTitle(const std::string& title) const;
		void	hideCursor(void) const;
		void	resetCursor(void) const;

		void	initImGui(void) const;
};


#endif /* WINDOW_HPP ======================================================== */
