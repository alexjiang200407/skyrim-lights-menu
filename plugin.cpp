#include "SkyrimLightsMenu.hpp"
#include "logger.hpp"
#include "hooks.hpp"
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "Version.h"

#ifdef SKYRIM_AE
extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []()
{
	SKSE::PluginVersionData v;
	v.PluginVersion(REL::Version{ Version::MAJOR, Version::MINOR, Version::PATCH, 0 });
	v.PluginName("SkyrimLightsMenu");
	v.AuthorName("shdowraithe101");
	v.UsesAddressLibrary();
	v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST_AE });
	v.UsesStructsPost629();

	return v;
}();
#endif


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * skse)
{
	SLM::SetupLog();

	SKSE::Init(skse);
	SLM::Hooks::Install();

	// Once all plugins and mods are loaded, then the ~ console is ready and
	// can be printed to
	SKSE::GetMessagingInterface()->RegisterListener(
		[](SKSE::MessagingInterface::Message* message)
		{
			if (message->type == SKSE::MessagingInterface::kDataLoaded)
			{
				RE::ConsoleLog::GetSingleton()->Print("SkyrimLightsMenu has been loaded");
				SLM::SkyrimLightsMenu::GetSingleton()->Init();
			}
		});

	return true;
}