#pragma once
#include "scene.hpp"
#include "inputManager.hpp"

namespace SLM
{
	class SkyrimLightsMenu :
		public SLM::Singleton<SkyrimLightsMenu>
	{
	public:
		class UI
		{
		public:
			UI()                     = default;
			UI(const UI&)            = delete;
			UI& operator=(const UI&) = delete;
			UI& operator=(UI&&)      = delete;

		public:
			void Draw();
		};

	public:
		SkyrimLightsMenu()                                   = default;
		SkyrimLightsMenu(const SkyrimLightsMenu&)            = delete;
		SkyrimLightsMenu& operator=(const SkyrimLightsMenu&) = delete;
		SkyrimLightsMenu& operator=(SkyrimLightsMenu&&)      = delete;
		
	public:
		void     Init();
		UI&      GetUI() { return ui; }

	private:
		Scene        scene;
		UI           ui;
		InputManager inputManager;
	};
}