#include "App.h"
#include "Image.h"
#include "Camera.h"
#include "Scene.h"

class RayTracer : public App
{
    public:
        RayTracer();
        ~RayTracer();
    private:
        void Update() override;
        void app_menu() override;

    private:
        bool render_every_frame = true;
        bool show_camera_debug = false;

        Image* image;
        Camera cam;
        int viewport_width, viewport_height;

        Scene my_scene;
};
