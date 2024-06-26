#include "Renderer/Scene.h"

#include <iostream>

#include "Renderer/Ray.h"

#include "Objects/Material.h"
#include "Objects/Object.h"

using namespace Rye;

bool Scene::Hit(const Ray& ray, HitData& hit, float t_min) const
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
        if (!object.Hit(ray, tempHit, t_min))
            continue;

        // if our closest hit is closer than the hit on our sphere we aren't able to
        // see it so check the next sphere
        if (hit.distance < tempHit.distance) // already hit something infront
            continue;

        if (!tempHit.front && m_materials[tempHit.materialID].materialType != Material::Dielectric)
            continue;

        hit = tempHit;

        // otherwise we have hit a closer sphere so update the closest hit

    }

    // if we havent hit anything then return what ever the sky color is
    return hit.distance < std::numeric_limits<float>::max();

}

void Scene::CornellBox()
{

    AddMaterial(Material(Material::Emissive));   // light
    AddMaterial(Material(Material::Lambertian)); // gray walls
    AddMaterial(Material(Material::Lambertian, glm::vec4(0.68,0.1,0.1,1))); // red right wall
    AddMaterial(Material(Material::Lambertian, glm::vec4(0.12,0.65,0.1,1))); // green left wall
    AddMaterial(Material(Material::Conductor, glm::vec4(0.944,0.776,0.373,1))); // gold ball
    AddMaterial(Material(Material::Glossy, glm::vec4(0.25,0.75,1,1))); // blue plastic ball
    AddMaterial(Material(Material::Dielectric, glm::vec4(1))); // glass ball


    AddObject(Quad(glm::vec3(-5,-5,10), glm::vec3( 0,10, 0), glm::vec3(10, 0, 0), 1)); // top
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3(10, 0, 0), glm::vec3( 0,10, 0), 1)); // bottom

    AddObject(Quad(glm::vec3( 5,-5, 0), glm::vec3( 0, 0,10), glm::vec3( 0,10, 0), 2)); // right
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0,10, 0), glm::vec3( 0, 0,10), 3)); // left

    AddObject(Quad(glm::vec3(-5, 5, 0), glm::vec3(10, 0, 0), glm::vec3( 0, 0,10), 1)); // back
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0, 0,10), glm::vec3(10, 0, 0), 1)); // front

    AddObject(Quad(glm::vec3(-3,-3, 9), glm::vec3(0,6,0), glm::vec3(6,0,0), 0));

    AddObject(Sphere(glm::vec3(-3,0,1), 1, 6));
    AddObject(Sphere(glm::vec3(0,0,1), 1, 5));
    AddObject(Sphere(glm::vec3(3,0,1), 1, 4));

}

void Scene::TestScene()
{
    ambientColor = glm::vec4(0.6f,0.7f,0.75f, 2);

    AddMaterial(Material(Material::Lambertian)); // gray ground
    AddMaterial(Material(Material::Emissive));   // light
    AddMaterial(Material(Material::Lambertian, glm::vec4(0.68,0.1,0.1,1))); // red
    AddMaterial(Material(Material::Dielectric)); // glass
    AddMaterial(Material(Material::Conductor, glm::vec4(0.944,0.776,0.373,1))); // goldish
    AddMaterial(Material(Material::Glossy, glm::vec4(0.25,0.75,1,1))); // blue plastic

    AddObject(Sphere(glm::vec3(0,4,-1000), 999, 0));
    AddObject(Sphere(glm::vec3(0,4,1), 1, 1));
    AddObject(Sphere(glm::vec3(4,4,0), 1, 3));
    AddObject(Sphere(glm::vec3(7,4,0), 1, 5));
    AddObject(Sphere(glm::vec3(-4,4,3), 2, 4));
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0,10, 0), glm::vec3(10, 0, 0), 1)); // bottom
}

void Scene::Box2()
{

    AddMaterial(Material(Material::Lambertian)); // gray
    AddMaterial(Material(Material::Emissive));   // light
    AddMaterial(Material(Material::Conductor, glm::vec4(0.944,0.776,0.373,1), 0, 0.8f)); // gold
    AddMaterial(Material(Material::Conductor, glm::vec4(0.926,0.721,0.504,1), 0, 0.8)); // copper
    AddMaterial(Material(Material::Dielectric)); // glass ball

    AddObject(Quad(glm::vec3(-5,-5,10), glm::vec3( 0,10, 0), glm::vec3(10, 0, 0), 1)); // top
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3(10, 0, 0), glm::vec3( 0,10, 0), 1)); // bottom

    AddObject(Quad(glm::vec3( 5,-5, 0), glm::vec3( 0, 0,10), glm::vec3( 0,10, 0), 2)); // right
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0,10, 0), glm::vec3( 0, 0,10), 3)); // left

    AddObject(Quad(glm::vec3(-5, 5, 0), glm::vec3(10, 0, 0), glm::vec3( 0, 0,10), 1)); // back
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0, 0,10), glm::vec3(10, 0, 0), 1)); // front

    AddObject(Sphere(glm::vec3(3,0,5), 1, 2));
    AddObject(Sphere(glm::vec3(-3,0,5), 1, 3));
    AddObject(Sphere(glm::vec3(0,0,5), 1, 4));
}


void Scene::AddObject(const ObjectTypes& o)
{
    objects.push_back(Object(o));
}

void Scene::RemoveObject(int i)
{
    objects.erase(std::next(objects.begin(), i));
}

void Scene::AddMaterial(const Material& m)
{
    m_materials.push_back(m);
    materialCount ++;
}

void Scene::RemoveMaterial(int i)
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
