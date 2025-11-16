#ifndef INTERFACE_HPP
# define INTERFACE_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <core/Window.hpp>

class	Interface
{
	public	:
		Window*		window;
		ImGuiIO*	io;


	public	:
		Interface(void);
		Interface(Window& window);
		
		void	init(Window& window);
		void	render(void);
		void	shutdown(void);
		
		bool	wantCaptureMouse(void) const;
		
		void	createNewFrame(void);
};

#endif /* INTERFACE_HPP ===================================================== */
