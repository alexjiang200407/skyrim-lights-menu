#pragma once
#include "palette.hpp"

namespace SLM
{
	class Prop
	{
	public:
		Prop(RE::TESObjectLIGH* light, RE::TESObjectREFRPtr ref) :
			lightBase(light),
			ref(ref),
			lightColor(light->data.color.red, light->data.color.green, light->data.color.blue)
		{
			logger::info("Light base 0x{:X}", light->GetFormID());
			logger::info("Light ref 0x{:X}", ref->GetFormID());
		};

	public:
		// ImGui function
		bool DrawTabItem(bool* isSelected);
		void DrawControlWindow();

	public:
		void Remove();
		void Reload3D();

	private:
		RE::TESObjectLIGH*   lightBase;
		RE::TESObjectREFRPtr ref;
		Palette              palette;
		Rgb                  lightColor;
	};
}