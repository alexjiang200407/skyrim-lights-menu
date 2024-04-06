#include "SkyrimLightsMenu.hpp"
#include "logger.hpp"

void SLM::SkyrimLightsMenu::Init()
{
	RE::BSInputDeviceManager::GetSingleton()->AddEventSink<RE::InputEvent*>(&this->inputManager);
}

void SLM::SkyrimLightsMenu::UI::Draw()
{
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
	ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);

	//ImGui::Begin("##Main", nullptr, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);

	ImGui::ShowDemoWindow();
	
	if (ImGui::IsKeyReleased(ImGuiKey_A))
	{
		logger::info("A has been pressed");
	}

	if (ImGui::IsMouseClicked(0, false))
	{
		logger::info("Left mouse click");
	}

	if (ImGui::IsMouseClicked(1, false))
	{
		logger::info("Right mouse click");
	}

	//ImGui::End();
}
