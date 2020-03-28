#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Luna
{
class LUNA_API Log
{
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

} // namespace Luna

// Core log macros
#define LN_CORE_TRACE(...) ::Luna::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LN_CORE_INFO(...) ::Luna::Log::getCoreLogger()->info(__VA_ARGS__)
#define LN_CORE_WARN(...) ::Luna::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LN_CORE_ERROR(...) ::Luna::Log::getCoreLogger()->error(__VA_ARGS__)
#define LN_CORE_FATAL(...) ::Luna::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define LN_TRACE(...) ::Luna::Log::getClientLogger()->trace(__VA_ARGS__)
#define LN_INFO(...) ::Luna::Log::getClientLogger()->info(__VA_ARGS__)
#define LN_WARN(...) ::Luna::Log::getClientLogger()->warn(__VA_ARGS__)
#define LN_ERROR(...) ::Luna::Log::getClientLogger()->error(__VA_ARGS__)
#define LN_FATAL(...) ::Luna::Log::getClientLogger()->fatal(__VA_ARGS__)
