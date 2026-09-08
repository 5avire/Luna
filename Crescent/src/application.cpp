#include <Luna.h>
#include <LunaEntryPoint.h>

#include "EditorLayer.h"

namespace Luna {

    class Crescent : public Application
    {
        public:
            Crescent()
                : Application("Crescent")
            {
                PushLayer(new EditorLayer());
            }

            ~Crescent()
            {
            }
    };

    Application* CreateApplication()
    {
        return new Crescent();
    }
}
