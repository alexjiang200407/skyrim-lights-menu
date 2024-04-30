#pragma once
#include "inputManager.hpp"
#include "scene.hpp"

namespace SLM
{
	class SkyrimLightsMenu :
		public SLM::Singleton<SkyrimLightsMenu>,
		public SLM::InputManager
	{
	public:
	public:
		SkyrimLightsMenu()                                   = default;
		SkyrimLightsMenu(const SkyrimLightsMenu&)            = delete;
		SkyrimLightsMenu& operator=(const SkyrimLightsMenu&) = delete;
		SkyrimLightsMenu& operator=(SkyrimLightsMenu&&)      = delete;

	public:
		void        Serialize(SKSE::SerializationInterface* intfc) const;
		void        Deserialize(SKSE::SerializationInterface* intfc);
		void        DoFrame();
		bool        IsMenuActive() const;
		void        Deactivate();
		void        ToggleMenu();
		void        SetMenuActive(bool setVisible);
		static void SetImGuiStyle();
		void        ToggleShowDemo();
		void        Revert();
		void        PostSaveLoad();
		void        HandleImGuiInput() override;
		void        HandleInputEvent(RE::InputEvent* const* ppEvent) override;
	public:
		bool AllowGameInput(RE::InputEvent* event) override;   // Allow input to passed to game
		bool AllowImGuiInput(RE::InputEvent* event) override;  // Allow input to be passed to ImGui

	private:
		Scene scene;
		bool  IsActive = false;
		bool  showDemo  = false;
	};
}