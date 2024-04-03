#include "SkyrimLightsMenu.hpp"
#include "logger.hpp"


void SLM::SkyrimLightsMenu::Init()
{
	RE::BSInputDeviceManager::GetSingleton()->AddEventSink<RE::InputEvent*>(GetSingleton());
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
		RE::TESObjectREFR* playerRef = RE::PlayerCharacter::GetSingleton()->AsReference();

		if (!playerRef)
		{
			return RE::BSEventNotifyControl::kContinue;
		}

		auto light = RE::TESForm::LookupByID(0xfe044800)->As<RE::TESBoundObject>();

		RE::NiPoint3 collision = RE::CrosshairPickData::GetSingleton()->collisionPoint;
		RE::NiPoint3 origin;
		RE::NiPoint3 directionVec;

		RE::PlayerCharacter::GetSingleton()->GetEyeVector(origin, directionVec, false);

		directionVec *= 50.0f;

		// X metres ahead of player
		RE::NiPoint3 lookingAt = origin + directionVec;

		auto newPropRef = RE::TESDataHandler::GetSingleton()->CreateReferenceAtLocation(
			light, lookingAt, { 0.0f, 0.0f, 0.0f }, playerRef->GetParentCell(), nullptr,
			nullptr, nullptr, {}, true, false).get();

		refs.push_back(newPropRef);
	}
	else if (dxScancode == keyboard->GetMappingKey("DELETE") && buttonEvt->heldDownSecs >= 0.5f && buttonEvt->IsUp())
	{
		for (const auto& ref : refs)
		{
			ref->Disable();
			ref->SetDelete(true);
		}
	}

	return RE::BSEventNotifyControl::kContinue;
}

SLM::SkyrimLightsMenu* SLM::SkyrimLightsMenu::GetSingleton()
{
	static SkyrimLightsMenu singleton{};
	return &singleton;
}
