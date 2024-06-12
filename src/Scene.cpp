#include "Scene.h"
#include "Hit.h"
#include "Ray.h"
#include "imgui.h"
#include "Sphere.h"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>


#include "Materials/Emission.h"
#include "Materials/Lambertian.h"
#include "Materials/Metallic.h"
#include "Materials/Glass.h"
#include "Materials/Specular.h"
#include "Materials/Glossy.h"


bool Scene::hit(const Ray& ray, Hit& hit) const
{
    hit.color = glm::vec3(0,0,0);
    // closest_hit.color = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    // if there isn't anything in the scene return skycolor
    if (objects.size() == 0)
    {
        return false;
    }

    // try and find our closeset hit, loop over spheres
    for (auto object : objects)
    {
        Hit temp_hit;

        // if distance is infinite/max, we haven't hit anything so check the next sphere
        if (!object->hit(ray, temp_hit))
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
    ambient_color = glm::vec3(0.6f,0.7f,0.75f);
    // ground
    add_material(std::make_shared<lambertian_bsdf>());
    add_object(std::make_shared<Sphere>(Sphere(glm::vec3(0,4,-1000), 999, 0)));

    add_object(std::make_shared<Sphere>(Sphere(glm::vec3(0,4,10), 1, 1)));
    add_object(std::make_shared<Sphere>(Sphere(glm::vec3(-4,4,0), 1, 2)));
    add_object(std::make_shared<Sphere>(Sphere(glm::vec3(0,4,0), 1, 3)));

    add_material(std::make_shared<emission>());
    add_material(std::make_shared<metallic_bsdf>(glm::vec3(0.944,0.776,0.373)));
    add_material(std::make_shared<glossy_bsdf>());
}

void Scene::add_object(std::shared_ptr<Object> o)
{
    objects.push_back(std::move(o));
}

void Scene::remove_object(const int& i)
{
    objects.erase(std::next(objects.begin(), i));
}

void Scene::add_material(std::shared_ptr<Material> m)
{
    materials.push_back(std::move(m));
    material_count ++;
}

void Scene::remove_material(const int& i)
{
    materials.erase(std::next(materials.begin(), i));
    material_count --;
}
