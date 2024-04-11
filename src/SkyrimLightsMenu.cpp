#include "SkyrimLightsMenu.hpp"

void SLM::SkyrimLightsMenu::DoFrame()
{
	if (IsMenuVisible())
	{
		if (showDemo)
		{
			// Show ImGui documentation instead
			ImGui::ShowDemoWindow();
		}
		else
		{
			ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
			ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);

			// Draw main window
			ImGui::Begin("##Main", nullptr, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
			{
				scene.DrawControlWindow();
			}
			ImGui::End();
		}
	}

	// Show or Hide window
	if (ImGui::IsKeyPressed(ImGuiKey_End, false))
	{
		logger::trace("Toggle menu");
		ToggleMenu();
	}
	else if (ImGui::IsKeyPressed(ImGuiKey_Escape, false))
	{
		logger::trace("Hiding menu");
		HideMenu();
	}
#ifdef  DEBUG
	else if (ImGui::IsKeyPressed(ImGuiKey_H) && IsMenuVisible())
	{
		ToggleShowDemo();
	}
#endif
}

inline bool SLM::SkyrimLightsMenu::IsMenuVisible() const { return isVisible; }

void SLM::SkyrimLightsMenu::HideMenu()
{
	SetMenuVisibility(false);
}

void SLM::SkyrimLightsMenu::ToggleMenu()
{
	SetMenuVisibility(!isVisible);
}

void SLM::SkyrimLightsMenu::SetMenuVisibility(bool setVisible)
{
	auto& io = ImGui::GetIO();

	if (setVisible)
	{
		RE::PlaySound("UIJournalTabsSD");
		io.MouseDrawCursor = true;
	}
	else
	{
		RE::PlaySound("UIMenuCancel");
		io.MouseDrawCursor = false;
	}

	isVisible = setVisible;
}

SLM::InputManager& SLM::SkyrimLightsMenu::GetInputManager() { return inputManager; }

inline void SLM::SkyrimLightsMenu::ToggleShowDemo() { showDemo = !showDemo; }
