#include "SkyrimLightsMenu.hpp"
#include "logger.hpp"

void SLM::SkyrimLightsMenu::Init()
{
	RE::BSInputDeviceManager::GetSingleton()->AddEventSink<RE::InputEvent*>(&this->inputManager);
}

void SLM::SkyrimLightsMenu::DoFrame()
{
	scene.DrawControlWindow();
}
