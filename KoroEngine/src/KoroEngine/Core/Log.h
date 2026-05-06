#pragma once


#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Koro {


class Log
{

public:
static void Init();
inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};



} // Koro

#define KORO_ENG_TRACE(...)    ::Koro::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KORO_ENG_INFO(...)     ::Koro::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KORO_ENG_WARN(...)     ::Koro::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KORO_ENG_ERROR(...)    ::Koro::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KORO_ENG_CRITICAL(...) ::Koro::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define KORO_TRACE(...)    ::Koro::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KORO_INFO(...)     ::Koro::Log::GetClientLogger()->info(__VA_ARGS__)
#define KORO_WARN(...)     ::Koro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KORO_ERROR(...)    ::Koro::Log::GetClientLogger()->error(__VA_ARGS__)
#define KORO_CRITICAL(...) ::Koro::Log::GetClientLogger()->critical(__VA_ARGS__)
