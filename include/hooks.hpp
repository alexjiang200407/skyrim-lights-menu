#pragma once
#include "SkyrimLightsMenu.hpp"

namespace SLM
{
	/**
	*	Hooks class to setup ImGui
	*/
	class Hooks :
		Singleton<Hooks>
	{
	private:
		struct WndProc
		{
			static LRESULT        thunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			static inline WNDPROC func;
		};

		struct CreateD3DAndSwapChain
		{
			static void                                    thunk();
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct StopTimer
		{
			static void                                    thunk(std::uint32_t a_timer);
			static inline REL::Relocation<decltype(thunk)> func;
		};

		struct SendInputEvent
		{
			static void                                    thunk(RE::BSTEventSource<RE::InputEvent*>* a_dispatcher, RE::InputEvent* const* a_events);
			static inline REL::Relocation<decltype(thunk)> func;
		};

	public:
		Hooks()                        = default;
		Hooks(const Hooks&)            = delete;
		Hooks& operator=(const Hooks&) = delete;

	public:
		static void Install();

	private:
		std::atomic<bool> installedHooks;
	};

}