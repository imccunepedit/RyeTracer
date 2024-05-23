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

    private:
        bool render_every_frame = false;

        Image* image;
        Camera cam;
        int viewport_width, viewport_height;

        Scene my_scene;
};
