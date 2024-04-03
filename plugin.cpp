#include "SkyrimLightsMenu.hpp"
#include "logger.hpp"

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
	SLM::SetupLog();
    SKSE::Init(skse);

    // Once all plugins and mods are loaded, then the ~ console is ready and
    // can be printed to
    SKSE::GetMessagingInterface()->RegisterListener(
        [](SKSE::MessagingInterface::Message* message) {
            if (message->type == SKSE::MessagingInterface::kDataLoaded) 
            {
                RE::ConsoleLog::GetSingleton()->Print("Hello World");
				SLM::SkyrimLightsMenu::Init();
            }
        }
    );

    return true;
}