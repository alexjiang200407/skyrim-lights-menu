#include "prop.hpp"

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

void SLM::Prop::Remove()
{
	ref->Disable();
	ref->SetDelete(true);
	lightBase->SetDelete(true);

	logger::info("Deleting ref 0x{:X}", ref->GetFormID());
	logger::info("Deleting base object 0x{:X}", lightBase->GetFormID());
}

void SLM::Prop::Reload3D()
{
	// Reloads the 3D light model
	// Hopefully it doesn't leak memory
	ref->Release3DRelatedData();
	ref->ClearData();
	ref->Load3D(false);
}

bool SLM::Prop::DrawLightIntensityControlWindow()
{
	bool        changed = false;
	ImGuiStyle* style   = &ImGui::GetStyle();

	ImGui::BeginChild("##LightDataControlWindow", ImVec2(0, 125), true);
	ImGui::Text("Light Intensity:");

	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Radius").x - style->ItemSpacing.x);
	changed |= ImGui::SliderInt("Radius", reinterpret_cast<int*>(&lightBase->data.radius), 32, 1024);
	ImGui::PopItemWidth();

	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Strength").x - style->ItemSpacing.x);
	changed |= ImGui::SliderFloat("Strength", &lightBase->fade, 0.0f, 5.0f);
	ImGui::PopItemWidth();

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
	{
		Reload3D();
	}

	ImGui::BeginChild("##LightPlacementWindow", ImVec2(0, 200), true);
	{
		bool changed = false;
		ImGui::Text("Position:");
		changed |= ImGui::DragFloat("x:", &movePos.x, 1.0f, -100.0f, 100.0f);
		changed |= ImGui::DragFloat("y:", &movePos.y, 1.0f, -100.0f, 100.0f);
		changed |= ImGui::DragFloat("z:", &movePos.z, 1.0f, -100.0f, 100.0f);

		if (ImGui::Button("Reset Position"))
		{
			movePos = { 0.0f, 0.0f, 0.0f };
			changed = true;
		}

		if (changed)
		{
			ref->SetPosition(startingPos + movePos);
		}
	}
	ImGui::EndChild();
}
