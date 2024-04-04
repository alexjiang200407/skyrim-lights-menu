#pragma once
#include "scene.hpp"

namespace SLM
{
	class SkyrimLightsMenu :
		public RE::BSTEventSink<RE::InputEvent*>
	{
	public:
		SkyrimLightsMenu()                                   = default;
		SkyrimLightsMenu(const SkyrimLightsMenu&)            = delete;
		SkyrimLightsMenu& operator=(const SkyrimLightsMenu&) = delete;
		SkyrimLightsMenu& operator=(SkyrimLightsMenu&&)      = delete;

	public:
		static void              Init();
		RE::BSEventNotifyControl ProcessEvent(
			RE::InputEvent* const* event,
			RE::BSTEventSource<RE::InputEvent*>*) override;

	private:
		Scene                             scene;
		bool                              isMenuHidden;
		static SkyrimLightsMenu           singleton;
	};
}