#pragma once
#include "SkyrimLightsMenu.hpp"

namespace SLM
{
	class Renderer :
		Singleton<Renderer>
	{
	private:
		struct ScreenSize
		{
			uint32_t width;
			uint32_t height;
		};


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

	public:
		Renderer() = default;
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;


	public:
		static void       Init();
		static ScreenSize GetScreenSize();

	private:
		std::atomic<bool> initialized;
	};




}