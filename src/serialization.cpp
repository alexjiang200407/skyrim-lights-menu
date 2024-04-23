#include "serialization.hpp"
#include "SkyrimLightsMenu.hpp"

void SLM::Serialization::RegisterSerialization()
{
	auto* serialisation = SKSE::GetSerializationInterface();

	// Register serialisation
	serialisation->SetUniqueID(Serialization::kSkyrimLightsMenu);
	serialisation->SetSaveCallback(Serialization::SaveCallback);
	serialisation->SetLoadCallback(Serialization::LoadCallback);
	//serialisation->SetRevertCallback(Serialization::RevertCallback);
}

void SLM::Serialization::LoadCallback(SKSE::SerializationInterface* intfc)
{
	logger::trace("Load callback");
	uint32_t type, version, length;
	SkyrimLightsMenu::GetSingleton()->Revert();

	while (intfc->GetNextRecordInfo(type, version, length))
	{
		if (version != kSerializationVersion)
		{
			logger::error("Loaded data is out of data!");
			continue;
		}

		if (type == Serialization::kSkyrimLightsMenu)
		{
			logger::trace("Found serialization");
			SkyrimLightsMenu::GetSingleton()->Deserialize(intfc);
			break;
		}
		else
		{
			logger::error("Unrecognized signature type {}!", type);
			break;
		}
	}
}

void SLM::Serialization::SaveCallback(SKSE::SerializationInterface* intfc)
{
	logger::trace("Save callback");

	if (!intfc->OpenRecord(Serialization::kSkyrimLightsMenu, Serialization::kSerializationVersion))
	{
		logger::error("Failed to read SkyrimLightsMenu data record!");
		return;
	}
	SkyrimLightsMenu::GetSingleton()->Serialize(intfc);
}

void SLM::Serialization::RevertCallback(SKSE::SerializationInterface*)
{
	logger::trace("Revert callback");
	SkyrimLightsMenu::GetSingleton()->Revert();
}
