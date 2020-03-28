#include "lnpch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Luna
{
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$"); // color, timestamp, name {core/client}, logmsg

    s_CoreLogger = spdlog::stdout_color_mt("LUNA");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);
}

} // namespace Luna
