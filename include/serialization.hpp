#pragma once

namespace SLM
{
	class Serialization
	{
		enum : std::uint32_t
		{
			kSerializationVersion = 0,
			kSkyrimLightsMenu = 'SLM',
		};

	public:
		static void RegisterSerialization();

	private:
		static void LoadCallback(SKSE::SerializationInterface* intfc);
		static void SaveCallback(SKSE::SerializationInterface* intfc);
		static void RevertCallback(SKSE::SerializationInterface* intfc);
	};
}