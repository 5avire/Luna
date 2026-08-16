#pragma once
#include <lunapch.h>

#include "Luna/Core.h"


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Luna {

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

}

#ifdef LUNA_DIST
    #define LUNA_CORE_TRACE(...)
    #define LUNA_CORE_INFO(...)
    #define LUNA_CORE_WARN(...)
    #define LUNA_CORE_ERROR(...)
    #define LUNA_CORE_CRITICAL(...)

    #define LUNA_TRACE(...)
    #define LUNA_INFO(...)
    #define LUNA_WARN(...)
    #define LUNA_ERROR(...)
    #define LUNA_CRITICAL(...)
#else
    // Core log macros
    #define LUNA_CORE_TRACE(...)     ::Luna::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define LUNA_CORE_INFO(...)      ::Luna::Log::GetCoreLogger()->info(__VA_ARGS__)
    #define LUNA_CORE_WARN(...)      ::Luna::Log::GetCoreLogger()->warn(__VA_ARGS__)
    #define LUNA_CORE_ERROR(...)     ::Luna::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define LUNA_CORE_CRITICAL(...)  ::Luna::Log::GetCoreLogger()->critical(__VA_ARGS__)

    // Client log macros
    #define LUNA_TRACE(...)     ::Luna::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define LUNA_INFO(...)      ::Luna::Log::GetClientLogger()->info(__VA_ARGS__)
    #define LUNA_WARN(...)      ::Luna::Log::GetClientLogger()->warn(__VA_ARGS__)
    #define LUNA_ERROR(...)     ::Luna::Log::GetClientLogger()->error(__VA_ARGS__)
    #define LUNA_CRITICAL(...)  ::Luna::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif
