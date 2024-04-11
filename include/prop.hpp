#pragma once

namespace SLM
{
	class Prop
	{
	public:
		Prop(RE::TESObjectREFRPtr ref) :
			ref(ref){};
		
	public:
		bool                 DrawTabItem();
		void                 Remove();

	private:
		RE::TESObjectREFRPtr ref;
	};
}