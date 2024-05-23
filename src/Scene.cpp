#include "Scene.h"
#include "Hit.h"
#include "Ray.h"
#include <glm/gtc/random.hpp>


Hit Scene::hit(const Ray& ray) const
{
    Hit closest_hit;
    closest_hit.color = sky_color;
    // closest_hit.color = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    // if there isn't anything in the scene return skycolor
    if (spheres.size() == 0)
    {
        return closest_hit;
    }

    // try and find our closeset hit, loop over spheres
    for (int i = 0; i < spheres.size(); i++)
    {
        // get a sphere to check if our ray hits it
        Sphere sphere = spheres.at(i);

        // get a hit from our sphere
        Hit hit = sphere.hit(ray);

        // if distance is infinite, we haven't hit anything so check the next sphere
        if (std::isinf(hit.distance))
            continue;

        // if our closest hit is closer than the hit on our sphere we aren't able to
        // see it so check the next sphere
        if (closest_hit.distance < hit.distance)
            continue;

        // otherwise we have hit a closer sphere so update the closest hit
        closest_hit = hit;

    }


    // if we havent hit anything then return what ever the sky color is
    // TODO fix directional light
    // if ((!std::isinf(closest_hit.distance)) & (directional_light.length() > 0.5f))
    //     closest_hit.color *= glm::dot(closest_hit.normal, directional_light);

    return closest_hit;

}

void Scene::add_sphere(Sphere s)
{
    spheres.push_back(s);
}

void Scene::remove_sphere(const int& i)
{
    spheres.erase(std::next(spheres.begin(), i));
}

void Scene::load_default()
{
    sky_color = glm::vec4(0.618f, 0.809f, 1.000f, 1.000f);
    // directional_light = glm::normalize(glm::vec3(-1.0f, -1.0f, 1.000f));
    add_sphere(Sphere(glm::vec3(0,0,-100), 99, glm::vec4(1.0f,0.0f,0.0f,1.0f)));
    add_sphere(Sphere(glm::vec3(4,0,0), 1, glm::vec4(0,0,1,1)));
    // add_sphere(Sphere(glm::vec3(4,2,0), 1, glm::vec4(1,0,0,1)));
    // add_sphere(Sphere(glm::vec3(4,-2,0), 1, glm::vec4(1,1,0,1)));
}
