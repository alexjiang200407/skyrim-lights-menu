#include "prop.hpp"

bool SLM::Prop::DrawTabItem()
{
	bool open = true;
	if (ImGui::BeginTabItem(std::format("{} 0x{:X}", ref->GetName(), ref->GetFormID()).c_str(), &open))
	{
		ImGui::EndTabItem();

		// User closes tab
		if (!open)
		{
			Remove();
		}
	}

	return open;
}

void SLM::Prop::Remove()
{
	ref->Disable();
	ref->SetDelete(true);
}
