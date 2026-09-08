#include <lunapch.h>
#include "Window.h"

#include "Platform/GLobal/GlobalWindow.h"

namespace Luna {

    Scope<Window> Window::Create(const WindowProps& props)
    {
#if defined(LUNA_PLATFORM_LINUX)
        return CreateScope<GlobalWindow>(props);
#elif defined(LUNA_PLATFORM_WINDOWS)
        return CreateScope<GlobalWindow>(props);
#else
        LUNA_CORE_ASSERT(false, "Unsupported Platform");
        return nullptr;
#endif
    }

}
