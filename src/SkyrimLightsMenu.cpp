#include "SkyrimLightsMenu.hpp"


void SLM::SkyrimLightsMenu::Init()
{
	//RE::BSInputDeviceManager::GetSingleton()->AddEventSink<RE::InputEvent*>(&this->inputManager);
}

void SLM::SkyrimLightsMenu::DoFrame()
{
	if (IsMenuVisible())
	{
		scene.DrawControlWindow();
	}

	// Show or Hide window
	if (ImGui::IsKeyPressed(ImGuiKey_End, false))
	{
		logger::info("Open skyrim lights menu");
		ToggleMenu();
	}
	else if (ImGui::IsKeyPressed(ImGuiKey_Escape, false))
	{
		logger::trace("Hiding menu");
		HideMenu();
	}
}

inline bool SLM::SkyrimLightsMenu::IsMenuVisible() const { return isVisible; }

inline void SLM::SkyrimLightsMenu::HideMenu() { isVisible = false; }

inline void SLM::SkyrimLightsMenu::ToggleMenu() { isVisible = !isVisible; }

SLM::InputManager& SLM::SkyrimLightsMenu::GetInputManager() { return inputManager; }
