#include "Scene.h"
#include "Hit.h"
#include "Ray.h"
#include "imgui.h"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include "tracy/Tracy.hpp"


bool Scene::hit(const Ray& ray, Hit& hit) const
{
    ZoneScoped;
    hit.light = sky_color;
    // closest_hit.color = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    // if there isn't anything in the scene return skycolor
    if (spheres.size() == 0)
    {
        return false;
    }

    // try and find our closeset hit, loop over spheres
    for (int i = 0; i < spheres.size(); i++)
    {
        // get a sphere to check if our ray hits it
        Sphere sphere = spheres.at(i);
        Hit temp_hit;

        // get a hit from our sphere
        bool is_hit = sphere.hit(ray, temp_hit);

        // if distance is infinite/max, we haven't hit anything so check the next sphere
        if (!is_hit) // didn't hit anything
            continue;

        // if our closest hit is closer than the hit on our sphere we aren't able to
        // see it so check the next sphere
        if (hit.distance < temp_hit.distance) // already hit something infront
        {
            continue;
        }
        hit = temp_hit;

        // otherwise we have hit a closer sphere so update the closest hit

    }


    // if we havent hit anything then return what ever the sky color is
    return hit.distance < std::numeric_limits<float>::max();

}

void Scene::load_default()
{
    directional_light_direction = glm::vec3(0.0f, 1.0f, -1.0f);
    add_sphere(Sphere(glm::vec3(4,0,0), 1, glm::vec3(0.1f)));
    add_sphere(Sphere(glm::vec3(4,0,-100), 99, glm::vec3(0.1f)));
    // add_sphere(Sphere(glm::vec3(4,2,0), 1, glm::vec3(0,0,1)));
    // add_sphere(Sphere(glm::vec3(4,-2,0), 1, glm::vec3(1,0,1)));
}

void Scene::add_sphere(Sphere s)
{
    spheres.push_back(s);
}

void Scene::remove_sphere(const int& i)
{
    spheres.erase(std::next(spheres.begin(), i));
}
