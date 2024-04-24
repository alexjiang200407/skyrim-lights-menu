#include "scene.hpp"
#include "util.hpp"

//float& SLM::Scene::cameraTranslateSpeed =

void SLM::Scene::DrawControlWindow()
{
	activePropIndex = -1;

	// Draw Tabs of all props
	ImGui::BeginTabBar("##propstabbar", ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_FittingPolicyScroll);
	{
		ImGui::TabItemButton("?", ImGuiTabItemFlags_Leading | ImGuiTabItemFlags_NoTooltip);
		int i = 0;

		for (auto prop = props.begin(); prop != props.end();)
		{
			bool activeProp = false;
			// check if user deleted prop
			if (!prop->DrawTabItem(&activeProp))
			{
				// Remove deleted prop from store
				prop = props.erase(props.begin() + i);
				continue;
			}

			prop++;

			if (activeProp)
				activePropIndex = i;

			i++;
		}

		if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
		{
			PlaceProp();
		}
	}
	ImGui::EndTabBar();

	// Draw prop control panel
	if (activePropIndex != -1)
		props[activePropIndex].DrawControlWindow();
	
	// Draw control panel
	ImGui::BeginChild("###SceneControlWindow", ImVec2(0, 150), true);
	{
		ImGui::Text("Scene Properties:");
		ImGui::Checkbox("Hide Menu", &lookAround);
		auto& io = ImGui::GetIO();

		if (lookAround || positioningProp)
		{
			io.MouseDrawCursor      = false;
			io.WantCaptureMouse     = false;
		}
		else
		{
			io.MouseDrawCursor      = true;
			io.WantCaptureMouse     = true;
		}

		if (ImGui::Button("Add Light"))
			PlaceProp();
	}
	ImGui::EndChild();

	//ImGui::BeginChild("##CurrentLightWindow", ImVec2(0, 200), true);
	//{
	//	ImGui::Text("Position:");

	//	ImGui::Checkbox("Follow cursor", &followCrosshair);
	//	if (followCrosshair && activePropIndex != -1)
	//	{
	//		props[activePropIndex].MoveToCameraLookingAt(crosshairDistance);
	//	}
	//	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Cursor Distance").x - ImGui::GetStyle().ItemSpacing.x);
	//	ImGui::SliderFloat("Cursor Distance", &crosshairDistance, 0.0f, 500.0f);
	//	ImGui::PopItemWidth();
	//}
	//ImGui::EndChild();

	if (positioningProp && activePropIndex != -1)
	{
		props[activePropIndex].MoveToCameraLookingAt(crosshairDistance);
	}
}

void SLM::Scene::Activate()
{
	lookAround      = false;
	positioningProp = false;

	// Enter free camera mode
	if (!RE::PlayerCamera::GetSingleton()->IsInFreeCameraMode())
	{
		previouslyInFreeCameraMode = false;
		RE::PlayerCamera::GetSingleton()->ToggleFreeCameraMode(false);
		SLM::PushInputContext(RE::ControlMap::InputContextID::kTFCMode);
	}
	else
		previouslyInFreeCameraMode = true;

	RE::Main::GetSingleton()->freezeTime = true;
}

void SLM::Scene::Deactivate()
{
	// Exit free camera mode
	if (RE::PlayerCamera::GetSingleton()->IsInFreeCameraMode() && !previouslyInFreeCameraMode)
	{
		RE::PlayerCamera::GetSingleton()->ToggleFreeCameraMode(false);
		SLM::PopInputContext(RE::ControlMap::InputContextID::kTFCMode);
	}

	RE::Main::GetSingleton()->freezeTime = false;
}

void SLM::Scene::PlaceProp()
{
	if (props.size() >= maxProps)
	{
		logger::warn("Reached maximum lights count");
		RE::DebugNotification("Reached maxmimum lights placed");
		return;
	}

	RE::TESObjectREFR* playerRef = RE::PlayerCharacter::GetSingleton()->AsReference();

	if (!playerRef)
	{
		logger::warn("Could not find player reference");
		return;
	}

	RE::NiPoint3 origin;

	if (RE::PlayerCamera::GetSingleton()->IsInFreeCameraMode())
		reinterpret_cast<RE::FreeCameraState*>(RE::PlayerCamera::GetSingleton()->currentState.get())->GetTranslation(origin);
	else
		origin = RE::PlayerCamera::GetSingleton()->pos;

	auto* factory      = RE::IFormFactory::GetFormFactoryByType(RE::FormType::Light);
	auto* lightBaseObj = factory->Create()->As<RE::TESObjectLIGH>();


	// lightBaseObj->SetFormID();
	RE::FormID id      = FindAvailableFormID();
	lightBaseObj->data = RE::TESForm::LookupByID(id)->As<RE::TESObjectLIGH>()->data;
	lightBaseObj->SetFormID(id, false);

	auto newPropRef = RE::TESDataHandler::GetSingleton()->CreateReferenceAtLocation(
		lightBaseObj->As<RE::TESBoundObject>(), origin, { 0.0f, 0.0f, 0.0f }, playerRef->GetParentCell(), playerRef->GetWorldspace(),
		nullptr, nullptr, {}, true, false);

	if (newPropRef)
		props.push_back({ lightBaseObj, newPropRef.get() });
	else
	{
		logger::error("Couldn't place new reference at location");
		RE::DebugNotification("Couldn't place light at location");
	}
}

void SLM::Scene::ClearScene()
{
	for (auto& prop : props)
		prop.Remove();

	props.clear();
}

void SLM::Scene::ToggleAI()
{
	REL::Relocation<void(RE::ProcessLists*)> func{ RELOCATION_ID(40317, 41327) };
	func(RE::ProcessLists::GetSingleton());
}

bool SLM::Scene::IsHidden() const
{
	return positioningProp || lookAround;
}

void SLM::Scene::Serialize(SKSE::SerializationInterface* intfc) const
{
	logger::trace("Serializing scene data");
	intfc->WriteRecordData(props.size());

	for (const auto& prop : props)
		prop.Serialize(intfc);
}

void SLM::Scene::Deserialize(SKSE::SerializationInterface* intfc)
{
	size_t savedPropsCount;
	intfc->ReadRecordData(savedPropsCount);
	logger::info("Found {} saved props", savedPropsCount);

	for (int i = 0; i < savedPropsCount; i++)
	{
		RE::FormID refId;
		intfc->ReadRecordData(refId);
		RE::TESObjectREFRPtr ref = RE::NiPointer{ RE::TESForm::LookupByID(refId)->As<RE::TESObjectREFR>() };

		Prop prop = { ref->GetBaseObject()->As<RE::TESObjectLIGH>(), ref };
		prop.Deserialize(intfc);

		props.push_back(prop);
	}
}

RE::FormID SLM::Scene::FindAvailableFormID()
{
	const auto dataHandler = RE::TESDataHandler::GetSingleton();
	const RE::FormID startID = dataHandler->LookupFormID(0x800, "SkyrimLightsMenu.esp");
	const RE::FormID endID  = startID + maxProps - 1;

	std::set<RE::FormID> usedIds{};

	for (const auto& prop : props)
		usedIds.insert(prop.GetBaseID());		

	for (RE::FormID i = startID; i <= endID; i++)
	{
		if (usedIds.find(i) == usedIds.end())
		{
			return i;
		}
	}

	logger::error("Could not find available id");
	return 0;
}

void SLM::Scene::ImGuiGoBack()
{
	positioningProp = false;
	lookAround      = false;
}
