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
		void               Activate();
		void               Deactivate();
		void               PlaceProp(RE::TESBoundObject* obj);
		void               ClearScene();
		std::vector<Prop>& GetProps() { return props; }
		void               ToggleAI();
		bool               IsHidden() const;
		void               Serialize(SKSE::SerializationInterface* intfc) const;
		void               Deserialize(SKSE::SerializationInterface* intfc);
		RE::FormID         FindAvailableFormID();
		void               ImGuiGoBack();
		void               StartPositioning() { positioningProp = true; }
		void               StopPositioning() { positioningProp = false; }

	public:
	private:
		bool                              lookAround      = false;
		bool                              positioningProp = false;
		std::vector<Prop>                 props;
		int                               activePropIndex   = -1;
		float                             crosshairDistance = 50.0f;
		static constexpr int              maxProps          = 7;
		static constexpr ImGuiWindowFlags windowFlags       = ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDecoration;
		static constexpr ImGuiTabBarFlags tabBarFlags       = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_FittingPolicyScroll;
	};
}