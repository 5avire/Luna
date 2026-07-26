#pragma once

#include <csignal>

#ifdef _WIN32
    #define LUNA_DEBUGBREAK() __debugbreak()
#elif defined(__linux__)
    #include <csignal>
    #define LUNA_DEBUGBREAK() raise(SIGTRAP)
#else
    #define LUNA_DEBUGBREAK() LUNA_CORE_ERROR("No DebugBreak Implementation")
#endif

#ifdef LUNA_ENABLE_ASSERTS
    #define LUNA_ASSERT(x, ...) { if(!(x)) { LUNA_ERROR("Assertion Failed: {0}", __VA_ARGS__); LUNA_DEBUGBREAK(); } }
    #define LUNA_CORE_ASSERT(x, ...) { if(!(x)) { LUNA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); LUNA_DEBUGBREAK(); } }
#else
    #define LUNA_ASSERT(x, ...)
    #define LUNA_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
