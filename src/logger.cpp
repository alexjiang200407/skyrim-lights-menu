#include "logger.hpp"
#include "Version.h"

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