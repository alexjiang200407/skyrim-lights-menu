#pragma once




namespace SLM
{
	class Renderer
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

	public:
		static void Init();

	private:
		static std::atomic<bool> initialized;
	};




}