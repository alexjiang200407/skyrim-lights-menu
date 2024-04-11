#include "scene.hpp"

void SLM::Scene::DrawControlWindow()
{
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
	const auto viewportSz = ImGui::GetMainViewport()->Size;
	ImGui::SetNextWindowSize(ImVec2{ viewportSz.x * 0.4f, viewportSz.y });

	ImGui::Begin("$PM_Title_Menu", nullptr, windowFlags);
	{		
		// Draw Tabs of all props
		ImGui::BeginTabBar("##propstabbar");
		{
			ImGui::TabItemButton("?", ImGuiTabItemFlags_Leading | ImGuiTabItemFlags_NoTooltip);
			int i = 0;
			for (auto& prop : props)
			{
				if (!prop.DrawTabItem())
				{
					props.erase(props.begin() + i);
				}

				i++;
			}
			
			if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
			{
				PlaceProp(RE::TESForm::LookupByID(0xfe044800)->As<RE::TESBoundObject>());
			}
		}
		ImGui::EndTabBar();

		// Draw prop info



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
	RE::NiPoint3 lookingAt = origin + directionVec;

	auto newPropRef = RE::TESDataHandler::GetSingleton()->CreateReferenceAtLocation(
		obj, lookingAt, { 0.0f, 0.0f, 0.0f }, playerRef->GetParentCell(), nullptr,
		nullptr, nullptr, {}, true, false).get();

	props.push_back(newPropRef);
}

void SLM::Scene::ClearScene()
{
	for (auto& prop : props)
		prop.Remove();

	props.clear();
}
