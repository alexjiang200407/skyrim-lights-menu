#include "scene.hpp"

void SLM::Scene::DrawControlWindow()
{
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
	const auto viewportSz = ImGui::GetMainViewport()->Size;
	ImGui::SetNextWindowSize(ImVec2{ viewportSz.x * 0.4f, viewportSz.y });

	ImGui::Begin("$PM_Title_Menu", nullptr, windowFlags);
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
	}
	ImGui::End();
}

void SLM::Scene::PlaceProp(RE::TESBoundObject* obj)
{
	RE::TESObjectREFR* playerRef = RE::PlayerCharacter::GetSingleton()->AsReference();

	if (!playerRef)
	{
		logger::warn("Could not find player reference");
		return;
	}

	RE::NiPoint3 collision = RE::CrosshairPickData::GetSingleton()->collisionPoint;
	RE::NiPoint3 origin;
	RE::NiPoint3 directionVec;

	RE::PlayerCharacter::GetSingleton()->GetEyeVector(origin, directionVec, false);

	directionVec *= 50.0f;

	// X metres ahead of player
	RE::NiPoint3 lookingAt    = origin + directionVec;
	auto*        factory      = RE::IFormFactory::GetFormFactoryByType(RE::FormType::Light);
	auto*        lightBaseObj = factory->Create()->As<RE::TESObjectLIGH>();

	lightBaseObj->data = obj->As<RE::TESObjectLIGH>()->data;

	auto newPropRef = RE::TESDataHandler::GetSingleton()->CreateReferenceAtLocation(
		lightBaseObj->As<RE::TESBoundObject>(), lookingAt, { 0.0f, 0.0f, 0.0f }, playerRef->GetParentCell(), nullptr,
		nullptr, nullptr, {}, true, false);

	if (newPropRef)
		props.push_back({ lightBaseObj, newPropRef.get() });
	else
		logger::error("Couldn't place new reference at location");
}

void SLM::Scene::ClearScene()
{
	for (auto& prop : props)
		prop.Remove();

	props.clear();
}