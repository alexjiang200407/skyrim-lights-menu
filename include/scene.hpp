#pragma once
#include "prop.hpp"

namespace SLM 
{
	class Scene 
	{
	public:
		Scene()                        = default;
		Scene(const Scene&)            = delete;
		Scene(const Scene&&)           = delete;
		Scene& operator=(const Scene&) = delete;

	public:
		void               PlaceProp(RE::TESBoundObject* obj);
		void               ClearScene();
		std::vector<Prop>& GetProps() { return props; }

	private:
		std::vector<Prop> props;
	};
}