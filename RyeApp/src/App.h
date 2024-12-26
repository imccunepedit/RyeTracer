#ifndef APP_H_
#define APP_H_

#include "Window.h"

namespace Rye {
    class App : public Window
    {
        public:
            App();
            ~App();

        private:
            void Update() override {}
            void ImGuiDraw() override;
            void AppMenu() override;

    };
}

#endif // APP_H_
