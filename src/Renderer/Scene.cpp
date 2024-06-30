#include "Renderer/Scene.h"

#include <iostream>

#include "Renderer/Ray.h"

#include "Materials/Material.h"
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

        // if (!tempHit.front && m_materials[tempHit.materialID].IsDoubleSided())
        //     continue;

        hit = tempHit;

        // otherwise we have hit a closer sphere so update the closest hit

    }

    // if we havent hit anything then return what ever the sky color is
    return hit.distance < std::numeric_limits<float>::max();

}

void Scene::CornellBox()
{

    AddMaterial(Emissive());   // light
    AddMaterial(Lambertian()); // gray walls
    AddMaterial(Lambertian(glm::vec3(0.68,0.1,0.1))); // red right wall
    AddMaterial(Lambertian(glm::vec3(0.12,0.65,0.1))); // green left wall
    AddMaterial(Conductor(glm::vec3(0.944,0.776,0.373), 1.4)); // gold ball
    AddMaterial(Glossy(glm::vec3(0.25,0.75,1))); // blue plastic ball
    AddMaterial(Dielectric(glm::vec3(1), 1.5f)); // glass ball


    AddObject(Quad(glm::vec3(-5,-5,10), glm::vec3( 0,10, 0), glm::vec3(10, 0, 0), 1)); // top
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3(10, 0, 0), glm::vec3( 0,10, 0), 1)); // bottom

    AddObject(Quad(glm::vec3( 5,-5, 0), glm::vec3( 0, 0,10), glm::vec3( 0,10, 0), 2)); // right
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0,10, 0), glm::vec3( 0, 0,10), 3)); // left

    AddObject(Quad(glm::vec3(-5, 5, 0), glm::vec3(10, 0, 0), glm::vec3( 0, 0,10), 1)); // back
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0, 0,10), glm::vec3(10, 0, 0), 1)); // front

    AddObject(Quad(glm::vec3(-3,-3, 9), glm::vec3(0,6,0), glm::vec3(6,0,0), 0));

    AddObject(Sphere(glm::vec3(-3,0,1), 1, 6));
    // AddObject(Sphere(glm::vec3(0,0,1), 1, 6));
    AddObject(AABB(glm::vec3(-1,-1,0.1), glm::vec3(1,1,2), 6));
    AddObject(Sphere(glm::vec3(3,0,1), 1, 4));

}

void Scene::TestScene()
{
    ambientColor = glm::vec3(0.6f,0.7f,0.75f);

    AddMaterial(Lambertian()); // gray walls
    AddMaterial(Dielectric(glm::vec3(1), 1.5f)); // glass ball
    AddMaterial(Lambertian(glm::vec3(0.68,0.1,0.1))); // red right wall
    AddMaterial(Emissive(20.0f));   // light
    AddMaterial(Dielectric(glm::vec3(1), 0.6f)); // glass ball
    // AddMaterial(Lambertian(glm::vec3(0.12,0.65,0.1))); // green left wall
    // AddMaterial(Conductor(glm::vec3(0.944,0.776,0.373), 1.4)); // gold ball
    // AddMaterial(Glossy(glm::vec3(0.25,0.75,1))); // blue plastic ball

    // AddObject(Sphere(glm::vec3(0,4,-1000), 999, 0));
    // AddObject(Sphere(glm::vec3(0,4,1), 1, 1));
    // AddObject(Sphere(glm::vec3(4,4,0), 1, 3));
    // AddObject(Sphere(glm::vec3(7,4,0), 1, 5));
    // AddObject(Sphere(glm::vec3(-4,4,3), 2, 4));
    AddObject(Quad(glm::vec3(-10,-10, 0), glm::vec3(100, 0, 0), glm::vec3( 0,100, 0), 0)); // bottom
    // AddObject(Quad(glm::vec3( 2, 2, 8), glm::vec3( 0, 4, 0), glm::vec3( 4, 0, 0), 3)); // light
    AddObject(AABB(glm::vec3(0.5,0.5,0.1), glm::vec3(1.5,1.5,1.1), 2));
    AddObject(Sphere(glm::vec3(-1.5,0.5,1), 1, 1));
    AddObject(AABB(glm::vec3(3.1,0.5,0.5), glm::vec3(5.1,2.5,2.5), 1));

    // AddObject(Quad(glm::vec3(3.1,0.5,0.5), glm::vec3(1,0,0),glm::vec3(0,0,1), 2));
    // AddObject(Quad(glm::vec3(3.1,0.5,0.5), glm::vec3(0,1,0),glm::vec3(1,0,0), 2));
    // AddObject(Quad(glm::vec3(3.1,0.5,0.5), glm::vec3(0,0,1),glm::vec3(0,1,0), 2));
    // AddObject(Quad(glm::vec3(4.1,1.5,1.5), glm::vec3(-1,0,0),glm::vec3(0,-1,0), 2));
    // AddObject(Quad(glm::vec3(4.1,1.5,1.5), glm::vec3(0,-1,0),glm::vec3(0,0,-1), 2));
    // AddObject(Quad(glm::vec3(4.1,1.5,1.5), glm::vec3(0,0,-1),glm::vec3(-1,0,0), 2));



}

void Scene::Box2()
{

    AddMaterial(Emissive());   // light
    AddMaterial(Lambertian()); // gray walls
    AddMaterial(Conductor(glm::vec3(0.944,0.776,0.373), 1.4)); // gold ball
    AddMaterial(Conductor(glm::vec3(0.926,0.721,0.504), 1.4)); // copper ball
    AddMaterial(Dielectric(glm::vec3(1), 1.0f)); // glass ball

    AddObject(Quad(glm::vec3(-5,-5,10), glm::vec3( 0,10, 0), glm::vec3(10, 0, 0), 1)); // top
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3(10, 0, 0), glm::vec3( 0,10, 0), 1)); // bottom

    AddObject(Quad(glm::vec3( 5,-5, 0), glm::vec3( 0, 0,10), glm::vec3( 0,10, 0), 2)); // right
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0,10, 0), glm::vec3( 0, 0,10), 3)); // left

    AddObject(Quad(glm::vec3(-5, 5, 0), glm::vec3(10, 0, 0), glm::vec3( 0, 0,10), 1)); // back
    AddObject(Quad(glm::vec3(-5,-5, 0), glm::vec3( 0, 0,10), glm::vec3(10, 0, 0), 1)); // front

    AddObject(Sphere(glm::vec3(3,0,5), 1, 0));
    AddObject(Sphere(glm::vec3(-3,0,5), 1, 3));
    AddObject(AABB(glm::vec3(-1,-1,4), glm::vec3(1,1,6), 4));
    // AddObject(Sphere(glm::vec3(0,0,5), 1, 4));
}


void Scene::AddObject(const ObjectTypes& o)
{
    objects.push_back(Object(o));
}

void Scene::RemoveObject(int i)
{
    objects.erase(std::next(objects.begin(), i));
}

void Scene::AddMaterial(const MaterialTypes& m)
{
    m_materials.push_back(Material(m));
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
