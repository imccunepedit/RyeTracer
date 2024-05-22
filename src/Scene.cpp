#include "Scene.h"


void Scene::add_sphere(Sphere s)
{
    spheres.push_back(s);
}

void Scene::remove_sphere(int i)
{
    spheres.erase(std::next(spheres.begin(), i));
}

void Scene::load_default()
{
    sky_color = glm::vec4(0.618f, 0.809f, 1.000f, 1.000f);
    add_sphere(Sphere(glm::vec3(0,0,-100), 99, glm::vec4(0.0f,0.0f,0.0f,1.0f)));
    add_sphere(Sphere(glm::vec3(4,0,0), 1, glm::vec4(0,0,0,1)));
    // add_sphere(Sphere(glm::vec3(4,2,0), 1, glm::vec4(1,0,0,1)));
    // add_sphere(Sphere(glm::vec3(4,-2,0), 1, glm::vec4(1,1,0,1)));
}
