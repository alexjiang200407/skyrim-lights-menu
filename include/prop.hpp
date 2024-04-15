#pragma once
#include "palette.hpp"

namespace SLM
{
	class Prop
	{
	public:
		Prop(RE::TESObjectREFRPtr ref) :
			ref(ref){};
		
	// ImGui
	public:
		bool                 DrawTabItem(bool* isSelected);
		void                 DrawControlWindow();

	public:
		void                 Remove();

	private:
		RE::TESObjectREFRPtr ref;
		Palette              palette;
	};
}