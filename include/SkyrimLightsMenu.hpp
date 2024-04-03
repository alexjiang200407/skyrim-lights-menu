#pragma once

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
		std::vector<RE::TESObjectREFRPtr> refs;
		static SkyrimLightsMenu* GetSingleton();
	};
}