#pragma once
#include "palette.hpp"
#include "prop.hpp"

namespace SLM
{
	class Scene
	{
	public:
		Scene()                        = default;
		Scene(const Scene&)            = delete;
		Scene(const Scene&&)           = delete;
		Scene& operator=(const Scene&) = delete;

		// ImGui
	public:
		void DrawControlWindow();

	public:
		void               PlaceProp(RE::TESBoundObject* obj);
		void               ClearScene();
		std::vector<Prop>& GetProps() { return props; }
		void               ToggleAI();

	public:
		bool                              allowLookAround = false;
	private:
		std::vector<Prop>                 props;
		static constexpr ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDecoration;
		static constexpr ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_FittingPolicyScroll;
	};
}