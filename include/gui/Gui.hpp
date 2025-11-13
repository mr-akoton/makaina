#ifndef GUI_HPP
# define GUI_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <core/Window.hpp>

class	GUI
{
	public	:
		Window	*window;
		ImGuiIO	*io;


	public	:
		GUI(void);
		GUI(Window &window);
		
		void	init(Window &window);
		void	render(void);
		void	shutdown(void);
		
		bool	wantCaptureMouse(void) const;
		
		void	createNewFrame(void);
};

#endif // GUI_HPP
