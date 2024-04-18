#pragma once

namespace SLM
{

	class LightType
	{
	public:

	public:
		LightType(SKSE::stl::enumeration<RE::TES_LIGHT_FLAGS, uint32_t>* type);


	public:
		// ImGui Functions
		bool DrawLightTypeControlWindow();

	private:
		SKSE::stl::enumeration<RE::TES_LIGHT_FLAGS, uint32_t>* type;
		static const char*                                     shadowTypeNames[];
		static constexpr int                                   shadowTypeCount    = 3;
		int                                                    selectedLightIndex = 0;
	};
}