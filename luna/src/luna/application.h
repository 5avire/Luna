#pragma once

namespace Luna {

    class Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();
    };

    // To be defined by user
    Application* CreateApplication();
}
