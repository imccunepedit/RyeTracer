#include "Scene.h"

#include <iostream>

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

#include "Ray.h"

// #include "Materials/Emission.h"
// #include "Materials/Lambertian.h"
// #include "Materials/Glass.h"
// #include "Materials/Glossy.h"
// #include "Materials/Metallic.h"
#include "Material.h"

#include "Objects/Sphere.h"
#include "Objects/Quad.h"



using namespace Rye;

bool Scene::Hit(const Ray& ray, HitData& hit)
{
    // if there isn't anything in the scene return
    if (objects.size() == 0)
    {
        return false;
    }

    // try and find our closeset hit, loop over spheres
    for (auto object : objects)
    {
        HitData tempHit;
        tempHit.seed = hit.seed;

        // if distance is infinite/max, we haven't hit anything so check the next sphere
        if (!object->Hit(ray, tempHit))
            continue;

        // if our closest hit is closer than the hit on our sphere we aren't able to
        // see it so check the next sphere
        if (hit.distance < tempHit.distance) // already hit something infront
            continue;

        if (!tempHit.front & !GetMaterial(tempHit.materialID).doubleSided)
            continue;

        hit = tempHit;

        // otherwise we have hit a closer sphere so update the closest hit

    }

    // if we havent hit anything then return what ever the sky color is
    return hit.distance < std::numeric_limits<float>::max();

}

void Scene::Initialize()
{
    // ground

    AddMaterial(Material(Material::Emissive));
    AddMaterial(Material(Material::Lambertian));
    AddMaterial(Material(Material::Lambertian, glm::vec4(0.68,0.1,0.1,1)));
    AddMaterial(Material(Material::Lambertian, glm::vec4(0.12,0.65,0.1,1)));
    AddMaterial(Material(Material::Conductor, glm::vec4(0.944,0.776,0.373,1)));
    AddMaterial(Material(Material::Lambertian, glm::vec4(0,0,1.0f,1)));
    AddMaterial(Material(Material::Dielectric));

#if 0
    ambientColor = glm::vec4(0.6f,0.7f,0.75f, 1);
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(0,4,-1000,1), 999, materials[0])));
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(4,4,0,1), 1, materials[3])));
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(-4,4,0,1), 1, materials[2])));
    AddObject(std::make_shared<Sphere>(Sphere(glm::vec4(0,4,1,1), 1, materials[1])));

#else

    AddObject(std::make_shared<Quad>(glm::vec4(-3,-3, 9, 1), glm::vec4(0, 6, 0, 0), glm::vec4(6, 0, 0, 0), 0));
    AddObject(std::make_shared<Quad>(glm::vec4(-5,-5,10, 1), glm::vec4(0, 10, 0, 0), glm::vec4(10, 0, 0, 0), 1)); // top
    AddObject(std::make_shared<Quad>(glm::vec4(-5,-5, 0, 1), glm::vec4(10, 0, 0, 0), glm::vec4(0, 10, 0, 0), 1)); // bottom
    AddObject(std::make_shared<Quad>(glm::vec4( 5,-5, 0, 1), glm::vec4(0, 0, 10, 0), glm::vec4(0, 10, 0, 0), 2)); // right
    AddObject(std::make_shared<Quad>(glm::vec4(-5,-5, 0, 1), glm::vec4(0, 10, 0, 0), glm::vec4(0, 0, 10, 0), 3)); // left
    AddObject(std::make_shared<Quad>(glm::vec4(-5, 5, 0, 1), glm::vec4(10, 0, 0, 0), glm::vec4(0, 0, 10, 0), 1)); // back
    AddObject(std::make_shared<Quad>(glm::vec4(-5,-5, 0, 1), glm::vec4(0, 0, 10, 0), glm::vec4(10, 0, 0, 0), 1)); // front

    AddObject(std::make_shared<Sphere>(glm::vec4(-3,0,1,1), 1, 6));
    AddObject(std::make_shared<Sphere>(glm::vec4(0,0,1,1), 1, 5));
    AddObject(std::make_shared<Sphere>(glm::vec4(3,0,1,1), 1, 4));

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

void Scene::AddMaterial(Material m)
{
    m_materials.push_back(m);
    materialCount ++;
}

void Scene::RemoveMaterial(const int& i)
{
    m_materials.erase(std::next(m_materials.begin(), i));
    materialCount --;
}


Material Scene::GetMaterial(uint32_t ID)
{
    if (ID >= materialCount)
        return m_materials[0];

    return m_materials[ID];
}
