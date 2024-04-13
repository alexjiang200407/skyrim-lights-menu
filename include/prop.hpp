#pragma once
#include "palette.hpp"

namespace SLM
{
	class Prop
	{
	public:
		Prop(RE::TESObjectREFRPtr ref) :
			ref(ref){};
		
	public:
		bool                 DrawTabItem();
		bool                 DrawTabItem(bool* isSelected);
		void                 Remove();
		void                 DrawControlWindow();

	private:
		RE::TESObjectREFRPtr ref;
		Palette              palette;
	};
}