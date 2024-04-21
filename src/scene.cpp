#include "scene.hpp"
#include "util.hpp"

//float& SLM::Scene::cameraTranslateSpeed =

void SLM::Scene::DrawControlWindow()
{
	int activePropIndex = -1;

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
			PlaceProp(RE::TESForm::LookupByID(0xfe044800)->As<RE::TESBoundObject>());
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
		ImGui::Checkbox("Hide Menu", &hideMenu);
		auto& io = ImGui::GetIO();

		if (hideMenu)
		{
			//ImGui::GetStyle().Alpha = 0.1f;
			io.MouseDrawCursor      = false;
			io.WantCaptureMouse     = false;
		}
		else
		{
			//ImGui::GetStyle().Alpha = 1.0f;
			io.MouseDrawCursor      = true;
			io.WantCaptureMouse     = true;
		}

		if (ImGui::Button("Add Light"))
			PlaceProp(RE::TESForm::LookupByID(0xfe044800)->As<RE::TESBoundObject>());
	}
	ImGui::EndChild();
}

void SLM::Scene::PlaceProp(RE::TESBoundObject* obj)
{
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

	lightBaseObj->data = obj->As<RE::TESObjectLIGH>()->data;

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
