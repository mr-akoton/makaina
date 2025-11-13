#include <gui/Gui.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

GUI::GUI(void):
	window(nullptr), io(NULL)
{
	/* Do nothing */
}

GUI::GUI(Window &window):
	window(&window), io(NULL)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.id, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}


/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */


/* ---------------------------------- State --------------------------------- */

void	GUI::init(Window &window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.id, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void	GUI::render(void)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void	GUI::shutdown(void)
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

/* --------------------------------- Getter --------------------------------- */

bool	GUI::wantCaptureMouse(void) const
{
	return io->WantCaptureMouse;
}


/* ========================================================================== */
/*                                 UI CREATION                                */
/* ========================================================================== */

void	GUI::createNewFrame(void)
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}