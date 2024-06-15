#include "Scene.h"

#include <iostream>

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

#include "HitData.h"
#include "Ray.h"
#include "Sphere.h"
#include "Quad.h"

#include "Materials.h"


using namespace Rye;

bool Scene::Hit(const Ray& ray, HitData& hit) const
{
    hit.color = glm::vec4(0);
    // closest_hit.color = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    // if there isn't anything in the scene return skycolor
    if (objects.size() == 0)
    {
        return false;
    }

    // try and find our closeset hit, loop over spheres
    for (auto object : objects)
    {
        HitData temp_hit;

        // if distance is infinite/max, we haven't hit anything so check the next sphere
        if (!object->Hit(ray, temp_hit))
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

void Scene::Initialize()
{
    // ground

    AddMaterial(std::make_shared<Emission>(4));
    AddMaterial(std::make_shared<LambertianBSDF>());
    AddMaterial(std::make_shared<MetallicBSDF>(glm::vec4(0.944,0.776,0.373,1)));
    AddMaterial(std::make_shared<GlossyBSDF>());
    AddMaterial(std::make_shared<GlossyBSDF>());

#if 0
    ambientColor = glm::vec4(0.6f,0.7f,0.75f, 1);
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(0,4,-1000,1), 999, materials[0])));
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(4,4,0,1), 1, materials[3])));
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(-4,4,0,1), 1, materials[2])));
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(0,4,1,1), 1, materials[1])));

#else

    AddObject(std::make_shared<Quad>(glm::vec4(-1,-1, 1.9, 1), glm::vec4(0, 2, 0, 0), glm::vec4(2, 0, 0, 0), materials[0]));
    AddObject(std::make_shared<Quad>(glm::vec4(-2,-2, 2, 1), glm::vec4(0, 4, 0, 0), glm::vec4(4, 0, 0, 0), materials[1]));
    AddObject(std::make_shared<Quad>(glm::vec4(-2,-2,-2, 1), glm::vec4(4, 0, 0, 0), glm::vec4(0, 4, 0, 0), materials[1]));
    AddObject(std::make_shared<Quad>(glm::vec4( 2,-2,-2, 1), glm::vec4(0, 0, 4, 0), glm::vec4(0, 4, 0, 0), materials[1]));
    AddObject(std::make_shared<Quad>(glm::vec4(-2, 2,-2, 1), glm::vec4(4, 0, 0, 0), glm::vec4(0, 0, 4, 0), materials[1]));
    AddObject(std::make_shared<Quad>(glm::vec4(-2,-2,-2, 1), glm::vec4(0, 4, 0, 0), glm::vec4(0, 0, 4, 0), materials[1]));

    AddObject(std::make_shared<Sphere>(glm::vec4(-1.5,0,0,1), 0.25, materials[4]));
    AddObject(std::make_shared<Sphere>(glm::vec4(0,0,0,1), 0.25, materials[3]));
    AddObject(std::make_shared<Sphere>(glm::vec4(1.5,0,0,1), 0.25, materials[2]));

#endif
}

void Scene::AddObject(std::shared_ptr<Object> o)
{
    objects.push_back(std::move(o));
}

void Scene::RemoveObject(const int& i)
{
    objects.erase(std::next(objects.begin(), i));
}

void Scene::AddMaterial(std::shared_ptr<Material> m)
{
    materials.push_back(std::move(m));
    materialCount ++;
}

void Scene::RemoveMaterial(const int& i)
{
    materials.erase(std::next(materials.begin(), i));
    materialCount --;
}


