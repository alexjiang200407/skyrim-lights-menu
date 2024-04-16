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

void SLM::Prop::DrawControlWindow()
{
	ImGui::BeginChild("##PropControlWindow", ImVec2(0, 150), true);
	{
		ImGui::Text("Choose Light Color");
		SLM::Rgb newColor = palette.DrawPaletteControlWindow();

		if (newColor != lightColor)
		{
			lightColor = newColor;

			lightBase->data.color.red = std::get<0>(newColor);
			lightBase->data.color.green = std::get<1>(newColor);
			lightBase->data.color.blue  = std::get<2>(newColor);

			// Reload the 3d
			Reload3D();
		}
	}
	ImGui::EndChild();
}
