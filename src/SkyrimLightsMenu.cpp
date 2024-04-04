#include "SkyrimLightsMenu.hpp"
#include "logger.hpp"

SLM::SkyrimLightsMenu SLM::SkyrimLightsMenu::singleton;

void SLM::SkyrimLightsMenu::Init()
{
	RE::BSInputDeviceManager::GetSingleton()->AddEventSink<RE::InputEvent*>(&singleton);
}

RE::BSEventNotifyControl SLM::SkyrimLightsMenu::ProcessEvent(RE::InputEvent* const* ppEvent, RE::BSTEventSource<RE::InputEvent*>*)
{
	if (!ppEvent || !(*ppEvent) || (*ppEvent)->GetEventType() != RE::INPUT_EVENT_TYPE::kButton)
		return RE::BSEventNotifyControl::kContinue;

	RE::InputEvent*  event      = *ppEvent;
	RE::ButtonEvent* buttonEvt  = event->AsButtonEvent();
	uint32_t         dxScancode = buttonEvt->GetIDCode();
	const auto       keyboard   = RE::BSInputDeviceManager::GetSingleton()->GetKeyboard();

	if (dxScancode == keyboard->GetMappingKey("END") && buttonEvt->heldDownSecs >= 0.5f && buttonEvt->IsUp())
	{
		scene.PlaceProp(RE::TESForm::LookupByID(0xfe044800)->As<RE::TESBoundObject>());
	}
	else if (dxScancode == keyboard->GetMappingKey("DELETE") && buttonEvt->heldDownSecs >= 0.5f && buttonEvt->IsUp())
	{
		scene.ClearScene();
	}

	return RE::BSEventNotifyControl::kContinue;
}
