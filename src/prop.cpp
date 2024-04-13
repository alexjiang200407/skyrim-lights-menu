#include "prop.hpp"

bool SLM::Prop::DrawTabItem()
{
	bool isSelected;
	return DrawTabItem(&isSelected);
}

bool SLM::Prop::DrawTabItem(bool* isSelected = nullptr)
{
	bool open = true;
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
		logger::info("Removing prop with ID 0x{:X}", ref->GetFormID());
		Remove();
	}

	return open;
}

void SLM::Prop::Remove()
{
	ref->Disable();
	ref->SetDelete(true);
}

void SLM::Prop::DrawControlWindow()
{
	 palette.DrawPaletteControlWindow();
}
