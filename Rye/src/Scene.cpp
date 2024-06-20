#include "Scene.h"

#include <iostream>

#include "Ray.h"

#include "Material.h"
#include "Object.h"

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
        if (!object.Hit(ray, tempHit))
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
    AddMaterial(Material(Material::Glossy, glm::vec4(0.25,0.75,1,1)));
    AddMaterial(Material(Material::Dielectric));

#if 0
    ambientColor = glm::vec4(0.6f,0.7f,0.75f, 2);
    AddObject(Object(Object::Sphere, Transform(glm::vec3(0,4,-1000), 999), 1));
    AddObject(Object(Object::Sphere, Transform(glm::vec3(4,4,0), 1), 3));
    AddObject(Object(Object::Sphere, Transform(glm::vec3(-4,4,3), glm::vec3(2,2,1)), 4));
    AddObject(Object(Object::Sphere, Transform(glm::vec3(0,4,1), 1), 0));
    AddObject(Object(Object::Quad, Transform(glm::vec3(0,4,1), 8, glm::vec3(90,0,0)), 0));

#else
    AddObject(Object(Object::Quad, Transform(glm::vec4(-3, 3, 9, 1),  6, glm::vec3(180,  0,  0)), 0));
    AddObject(Object(Object::Quad, Transform(glm::vec4(-5, 5,10, 1), 10, glm::vec3(180,  0,  0)), 1)); // top
    AddObject(Object(Object::Quad, Transform(glm::vec4(-5,-5, 0, 1), 10, glm::vec3(  0,  0,  0)), 1)); // bottom
    AddObject(Object(Object::Quad, Transform(glm::vec4( 5,-5, 0, 1), 10, glm::vec3(  0,-90,  0)), 2)); // right
    AddObject(Object(Object::Quad, Transform(glm::vec4(-5,-5,10, 1), 10, glm::vec3(  0, 90,  0)), 3)); // left
    AddObject(Object(Object::Quad, Transform(glm::vec4(-5, 5, 0, 1), 10, glm::vec3( 90,  0,  0)), 1)); // back
    AddObject(Object(Object::Quad, Transform(glm::vec4(-5,-5,10, 1), 10, glm::vec3(-90,  0,  0)), 1)); // front

    AddObject(Object(Object::Sphere, Transform(glm::vec4(-3,0,1,1), 1), 6));
    AddObject(Object(Object::Sphere, Transform(glm::vec4(0,0,1,1), 1), 5));
    AddObject(Object(Object::Sphere, Transform(glm::vec4(3,0,1,1), 1), 4));
#endif

}

void Scene::AddObject(Object o)
{
    objects.push_back(o);
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


Material& Scene::GetMaterial(uint32_t ID)
{
    if (ID >= materialCount)
        return m_materials[0];

    return m_materials[ID];
}
