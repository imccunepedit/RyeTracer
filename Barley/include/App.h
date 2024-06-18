#ifndef APP_H_
#define APP_H_

#include "Window.h"

namespace Barley {
    class App : public Window
    {
        public:
            App();
            ~App();

        private:
            void Update() override {}
            void Draw() override;
            void AppMenu() override;

    };
}

#endif // APP_H_
