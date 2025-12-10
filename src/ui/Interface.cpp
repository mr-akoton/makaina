#include <ui/Interface.hpp>

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Interface::Interface(void):
	window(nullptr),
	io(nullptr)
{
	/* Do nothing */
}

Interface::Interface(Window& window):
	window(&window),
	io(nullptr)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	ImGui::StyleColorsDark();
	window.initImGui();
	ImGui_ImplOpenGL3_Init("#version 330");
}

/* ========================================================================== */
/*                                   METHOD                                   */
/* ========================================================================== */

/* ---------------------------------- State --------------------------------- */

void	Interface::init(Window& window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();
	ImGui::StyleColorsDark();
	window.initImGui();
	ImGui_ImplOpenGL3_Init("#version 330");
}

void	Interface::render(void)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void	Interface::shutdown(void)
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

/* --------------------------------- Getter --------------------------------- */

bool	Interface::wantCaptureMouse(void) const
{
	return io->WantCaptureMouse;
}

/* ========================================================================== */
/*                                 UI CREATION                                */
/* ========================================================================== */

void	Interface::createNewFrame(void)
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}
