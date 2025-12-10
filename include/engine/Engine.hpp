#ifndef ENGINE_HPP
# define ENGINE_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

# include <core/Window.hpp>
# include <engine/Terrain.hpp>
# include <engine/Water.hpp>
# include <ui/Interface.hpp>
# include <utils/types.hpp>

# include <exception>


class	Engine
{
	public	:
		Window			window;
		Interface		UI;
		Camera			camera;
		
		Vector3			lightPosition;
		Vector3			lightColor;

		float			deltaTime;
		double			previousTime;
		double			currentTime;
		double			timeDifference;
		unsigned int	counter;

	public	:
		Engine(
			unsigned int	windowWidth,
			unsigned int	windowHeight,
			const char*		windowTitle
		);
		~Engine();

		void	run(void);

	private	:
		void	_initGlfw(void);
		void	_initGlad(void);

		void	_displayFPS(void);
		void	_updateDeltaTime(void);
		
		void	_handleInput(void);
		void	_renderUI(Terrain& terrain, Water& water);

		void	_renderScene(Terrain& terrain, Water& water);
		void	_renderSceneForWater(Terrain& terrain, Water& water);

	public	:
		class	WindowInitFailedException: std::exception
		{
			public	:
				const char*	what(void) const noexcept;
		};

		class	GladLoadFailedException: std::exception
		{
			public	:
				const char*	what(void) const noexcept;
		};
};

#endif /* ENGINE_HPP ======================================================== */
