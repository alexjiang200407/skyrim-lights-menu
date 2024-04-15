

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

	class CenteredControlWrapper
	{
	public:
		explicit CenteredControlWrapper(bool result) :
			result_(result) {}

		operator bool() const
		{
			return result_;
		}

	private:
		bool result_;
	};

	class ControlCenterer
	{
	public:
		ControlCenterer(ImVec2 windowSize) :
			windowSize_(windowSize) {}

		template <typename Func>
		CenteredControlWrapper operator()(Func control) const
		{
			ImVec2 originalPos = ImGui::GetCursorPos();

			// Draw offscreen to calculate size
			ImGui::SetCursorPos(ImVec2(-10000.0f, -10000.0f));
			control();
			ImVec2 controlSize = ImGui::GetItemRectSize();

			ImGui::SetCursorPos(originalPos);

			// Draw at centered position
			AlignForWidth(controlSize.x);
			control();



			return CenteredControlWrapper(ImGui::IsItemClicked());
		}

	private:
		ImVec2 windowSize_;
	};

	}
#define CENTERED_CONTROL(control)                                 \
	ImGui::ControlCenterer{ ImGui::GetWindowSize() }([&]() { control; })