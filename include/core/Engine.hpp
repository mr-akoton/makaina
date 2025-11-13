#ifndef ENGINE_HPP
# define ENGINE_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <core/Window.hpp>
# include <scene/Terrain.hpp>
# include <gui/Gui.hpp>

# include <exception>


class	Engine
{
	// Variable
	public	:
		int		windowWidth;
		int		windowHeight;
		Window	window;
		GUI		gui;

		float	deltaTime;
		float	lastFrame;


	// Method
	public	:
		Engine(int windowWidth, int windowHeight, const char *windowTitle);
		~Engine();

		void	run(void);

	private	:
		void	_initGlfw(void);
		void	_initGlad(void);
		void	_renderGUI(void);
		void	_updateDeltaTime(void);
		void	_handleInput(void);


	// Exception
	public	:
		class	WindowInitFailedException: std::exception
		{
			public	:
				const char	*what(void) const throw();
		};

		class	GladLoadFailedException: std::exception
		{
			public	:
				const char	*what(void) const throw();
		};
};

#endif // ENGINE_HPP
