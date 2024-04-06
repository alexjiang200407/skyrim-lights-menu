#pragma once
#include "inputManager.hpp"
#include "scene.hpp"

namespace SLM
{
	class SkyrimLightsMenu :
		public SLM::Singleton<SkyrimLightsMenu>
	{
	public:
	public:
		SkyrimLightsMenu()                                   = default;
		SkyrimLightsMenu(const SkyrimLightsMenu&)            = delete;
		SkyrimLightsMenu& operator=(const SkyrimLightsMenu&) = delete;
		SkyrimLightsMenu& operator=(SkyrimLightsMenu&&)      = delete;

	public:
		void          Init();
		void          DoFrame();
		bool          IsMenuVisible() const;
		void          HideMenu();
		void          ToggleMenu();
		InputManager& GetInputManager();

	private:
		Scene        scene;
		InputManager inputManager;
		bool         isVisible = false;
	};
}