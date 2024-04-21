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
		void        DoFrame();
		bool        IsMenuVisible() const;
		void        HideMenu();
		void        ToggleMenu();
		void        SetMenuVisibility(bool setVisible);
		static void SetImGuiStyle();
		void        ToggleShowDemo();

	public:
		bool AllowGameInput(RE::InputEvent* event) override;   // Allow input to passed to game
		bool AllowImGuiInput(RE::InputEvent* event) override;  // Allow input to be passed to ImGui

	private:
		Scene scene;
		bool  isVisible = false;
		bool  showDemo  = false;
	};
}