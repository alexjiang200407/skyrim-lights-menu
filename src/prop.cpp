#include "prop.hpp"
#include "util.hpp"

bool SLM::Prop::DrawTabItem(bool* isSelected = nullptr)
{
	bool open     = true;
	bool selected = false;
	if (selected = ImGui::BeginTabItem(std::format("{} 0x{:X}", ref->GetName(), ref->GetFormID()).c_str(), &open))
	{
		if (isSelected)
			*isSelected = selected;

		ImGui::EndTabItem();
	}
	// User closes tab
	if (!open)
	{
		Remove();
	}

	return open;
}

void SLM::Prop::Serialize(SKSE::SerializationInterface* intfc) const
{
	intfc->WriteRecordData(ref->GetFormID());
	palette.Serialize(intfc);
	intfc->WriteRecordData(lightBase->data);
	intfc->WriteRecordData(lightBase->fade);
}

void SLM::Prop::Deserialize(SKSE::SerializationInterface* intfc)
{
	palette.Deserialize(intfc);
	intfc->ReadRecordData(lightBase->data);
	lightType = &lightBase->data.flags;
	intfc->ReadRecordData(lightBase->fade);

	const auto newColor = palette.GetCurrentColor();
	lightColor          = newColor;


	lightBase->data.color.red   = std::get<0>(newColor);
	lightBase->data.color.green = std::get<1>(newColor);
	lightBase->data.color.blue  = std::get<2>(newColor);
	logger::info("Light color r: {}, g: {}, b: {}", lightBase->data.color.red, lightBase->data.color.green, lightBase->data.color.blue);

	// Load 3D Model now
	if (!ref->Is3DLoaded())
		ref->Load3D(false);
	else
		Reload3D();
}

void SLM::Prop::Remove()
{
	ref->Disable();
	ref->SetDelete(true);

	logger::info("Deleting ref 0x{:X}", ref->GetFormID());
}

void SLM::Prop::Reload3D()
{
	// This reloads the 3d
	// Maybe change later
	ref->SetPosition(ref->GetPosition());
	//ref->Disable();
	//ref->Enable(false);
	//ref->Update3DPosition(true);
}

void SLM::Prop::MoveToCameraLookingAt(float distanceFromCamera)
{
	auto cameraNode = RE::PlayerCamera::GetSingleton()->cameraRoot.get()->AsNode();
	auto cameraNI   = reinterpret_cast<RE::NiCamera*>((cameraNode->children.size() == 0) ? nullptr : cameraNode->children[0].get());
	ref->SetPosition(GetCameraPosition() + (cameraNI->world.rotate * RE::NiPoint3{ distanceFromCamera, 0.0f, 0.0f }));
}

bool SLM::Prop::DrawLightIntensityControlWindow()
{
	bool        changed = false;
	ImGuiStyle* style   = &ImGui::GetStyle();

	ImGui::BeginChild("##LightDataControlWindow", ImVec2(0, 175), true);
	{
		ImGui::Text("Light Intensity:");

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Radius").x - style->ItemSpacing.x);
		changed |= ImGui::SliderInt("Radius", reinterpret_cast<int*>(&lightBase->data.radius), 32, 1024);
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Strength").x - style->ItemSpacing.x);
		changed |= ImGui::SliderFloat("Strength", &lightBase->fade, 0.0f, 5.0f);
		ImGui::PopItemWidth();

		if (ImGui::Checkbox("Hide Light", &isHidden))
		{
			if (isHidden)
				ref->Disable();
			else
				ref->Enable(false);
		}
	}
	ImGui::EndChild();

	return changed;
}

void SLM::Prop::DrawControlWindow()
{
	bool changed = false;

	ImGui::BeginChild("##LightColorControlWindow", ImVec2(0, 150), true);
	{
		ImGui::Text("Choose Light Color:");
		SLM::Rgb newColor = palette.DrawControlWindow();

		if (newColor != lightColor)
		{
			lightColor = newColor;

			lightBase->data.color.red   = std::get<0>(newColor);
			lightBase->data.color.green = std::get<1>(newColor);
			lightBase->data.color.blue  = std::get<2>(newColor);

			changed = true;
		}
	}
	ImGui::EndChild();

	changed |= lightType.DrawLightTypeControlWindow();
	changed |= DrawLightIntensityControlWindow();

	// Reload the 3d
	if (changed)
		Reload3D();
}
