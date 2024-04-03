#include "logger.hpp"

namespace SLM
{
	void SetupLog()
	{
		auto path = logger::log_directory();
		if (!path)
		{
			SKSE::stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
		*path /= std::format("{}.log"sv, pluginName);

		auto       sink  = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		const auto level = spdlog::level::trace;

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);
		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%s(%#): [%^%l%$] %v"s);

		logger::info("Hello World");
	}
}