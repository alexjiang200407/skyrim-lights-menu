#include "hooks.hpp"
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "Version.h"
#include "palette.hpp"
#include "serialization.hpp"

namespace SLM
{
	void SetupLog()
	{
		assert(SKSE::log::log_directory().has_value());
		auto path = SKSE::log::log_directory().value() / std::filesystem::path(Version::NAME.data() + ".log"s);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true);
		auto log  = std::make_shared<spdlog::logger>("global log", std::move(sink));

		log->set_level(spdlog::level::trace);
		log->flush_on(spdlog::level::trace);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%g(%#): [%^%l%$] %v", spdlog::pattern_time_type::local);
	}
}

#ifdef SKYRIM_AE
extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []()
{
	SKSE::PluginVersionData v;
	v.PluginVersion(REL::Version{ Version::MAJOR, Version::MINOR, Version::PATCH, 0 });
	v.PluginName("SkyrimLightsMenu");
	v.AuthorName("shdowraithe101");
	v.UsesAddressLibrary();
	v.CompatibleVersions({ SKSE::RUNTIME_LATEST });
	v.UsesUpdatedStructs();

	return v;
}();
#endif


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * skse)
{
	SLM::SetupLog();
	SLM::Palette::LoadPaletteFile();

	SKSE::Init(skse);
	SLM::Hooks::Install();
	SLM::Serialization::RegisterSerialization();

	// Once all plugins and mods are loaded, then the ~ console is ready and
	// can be printed to
	SKSE::GetMessagingInterface()->RegisterListener(
		[](SKSE::MessagingInterface::Message* message)
		{
			if (message->type == SKSE::MessagingInterface::kDataLoaded)
			{
				RE::ConsoleLog::GetSingleton()->Print("SkyrimLightsMenu has been loaded");
			}
		});

	return true;
}