#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <imgui/imgui.h>
# include <imgui/imgui_impl_glfw.h>
# include <imgui/imgui_impl_opengl3.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

# include <core/Window.hpp>
# include <core/Camera.hpp>
# include <util/types.hpp>

# include <exception>
# include <string>

constexpr GLuint			WINDOW_WIDTH = 1080;
constexpr GLuint			WINDOW_HEIGHT = 720;
constexpr std::string_view	WINDOW_TITLE = "Makaina";


class	Engine
{
	private	:
		Window	_window;
		Camera	_camera;


	public	:
		Engine(void);
		~Engine();

		void	run(void);

	private	:
		void	_input(void) const;


	public	:
		class	WindowInitFailedException: public std::exception {
			const char*	what(void) const noexcept;
		};

		class	GladLoadFailedException: public std::exception {
			const char*	what(void) const noexcept;
		};
};

#endif /* ENGINE_HPP ======================================================== */
