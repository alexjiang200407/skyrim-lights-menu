

namespace ImGui
{

	void AlignForWidth(float width, float alignment = 0.5f)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		float       avail = ImGui::GetContentRegionAvail().x;
		float       off   = (avail - width) * alignment;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
	}

}