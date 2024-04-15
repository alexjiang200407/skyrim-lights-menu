#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include <wrl/client.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <spdlog/sinks/basic_file_sink.h>


using namespace std::literals;

namespace stl
{
	using namespace SKSE::stl;

	template <class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		SKSE::AllocTrampoline(14);

		auto& trampoline = SKSE::GetTrampoline();
		T::func          = trampoline.write_call<5>(a_src, T::thunk);
	}
}

#define DLLEXPORT __declspec(dllexport)

namespace logger = SKSE::log;



namespace SLM
{
	template <typename T>
	class Singleton
	{
	public:
		static T* GetSingleton()
		{
			static T singleton{};
			return &singleton;
		}
	};

	struct ScreenSize
	{
		uint32_t width;
		uint32_t height;
	};

	inline ScreenSize GetScreenSize()
	{
		// This is a global managed by Renderer, but not part of the RendererData struct.
		// We pass back the value so users are not tempted to modify this directly.
		REL::Relocation<ScreenSize*> singleton{ RELOCATION_ID(525002, 411483) };
		return *singleton;
	}

}


#ifdef SKYRIM_AE
#	define OFFSET(se, ae) ae
#else
#	define OFFSET(se, ae) se
#endif