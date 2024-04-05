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
}


#ifdef SKYRIM_AE
#	define OFFSET(se, ae) ae
#else
#	define OFFSET(se, ae) se
#endif