#include "lightType.hpp"

const char* SLM::LightType::shadowTypeNames[] = { "None", "Shadow Hemisphere", "Omnidirectional Shadow" };

enum SHADOW_TYPE_INDEX
{
	NONE = 0,
	HEMI_SHADOW,
	OMNI_SHADOW,
};

SLM::LightType::LightType(SKSE::stl::enumeration<RE::TES_LIGHT_FLAGS, uint32_t>* type) :
	type(type)
{
	using FLAGS = RE::TES_LIGHT_FLAGS;

	if (type->any(FLAGS::kHemiShadow))
		selectedLightIndex = HEMI_SHADOW;
	else if (type->any(FLAGS::kOmniShadow))
		selectedLightIndex = OMNI_SHADOW;
}

bool SLM::LightType::DrawLightTypeControlWindow()
{
	bool changed        = false;

	ImGui::BeginChild("##LightPropertiesControlWindow", ImVec2(0, 100), true);
	{
		ImGui::Text("Light Shadow Type:");

		for (int i = 0; i < shadowTypeCount; i++)
		{
			if (i != 0)
				ImGui::SameLine();
			changed |= ImGui::RadioButton(shadowTypeNames[i], &selectedLightIndex, i);
		}

	}
	ImGui::EndChild();

	using FLAGS = RE::TES_LIGHT_FLAGS;

	if (changed)
	{
		if (selectedLightIndex == HEMI_SHADOW)
			type->set(FLAGS::kHemiShadow);
		else
			type->reset(FLAGS::kHemiShadow);

		if (selectedLightIndex == OMNI_SHADOW)
			type->set(FLAGS::kOmniShadow);
		else
			type->reset(FLAGS::kOmniShadow);
	}

	return changed;
}
