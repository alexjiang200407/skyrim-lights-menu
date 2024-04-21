#pragma once
#include "lightType.hpp"
#include "palette.hpp"

namespace SLM
{
	class Prop
	{
	public:
		Prop(RE::TESObjectLIGH* light, RE::TESObjectREFRPtr ref) :
			lightBase(light),
			ref(ref),
			lightColor(light->data.color.red, light->data.color.green, light->data.color.blue),
			lightType(&lightBase->data.flags),
			startingPos(ref->GetPosition())
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
		bool DrawLightIntensityControlWindow();

	private:
		RE::TESObjectLIGH*   lightBase;
		RE::TESObjectREFRPtr ref;
		RE::NiPoint3         startingPos;
		RE::NiPoint3         movePos{ 0, 0, 0 };
		Palette              palette;
		LightType            lightType;
		Rgb                  lightColor;
		static bool          followCrosshair;
		static float         crosshairDistance;
	};
}