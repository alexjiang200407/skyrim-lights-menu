#pragma once
#include "scene.hpp"
#include "inputManager.hpp"

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
		void     Init();
		void     DoFrame();
	private:
		Scene        scene;
		InputManager inputManager;
	};
}