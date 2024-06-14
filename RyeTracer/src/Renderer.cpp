#include "Renderer.h"

#include <iostream>

using namespace Barley;

void Renderer::Render()
{
    m_camera->film.samples ++;

    std::cout << m_camera->film.Width() << std::endl;
    for (int j=0; j < m_camera->film.Height(); j++)
    {
        for (int i=0; i < m_camera->film.Width(); i++)
        {
            glm::vec4 color = RayGen(i, j);
            m_camera->film.SetPixel(i,j,color);
        }
    }


    // using oneapi::tbb::parallel_for;

    // parallel_for(size_t(0), size_t(viewport_pixel_height), [this,s](size_t j)
    // {
    //     parallel_for(size_t(0), size_t(viewport_pixel_width), [this,s,j](size_t i){
    //         pixel_color(i, j, s);
    //     });
    // });

}

glm::vec4 Renderer::RayGen(const int& i, const int& j)
{

    Ray ray;
    uint32_t seed = i + j * m_camera->film.Width() + m_camera->film.samples * m_camera->film.Width() * m_camera->film.Height();

    ray.origin = m_camera->GetRayOrigin();
    ray.direction = m_camera->GetRayDirection(i, j);

    HitData hit = TraceRay(ray);

    return glm::vec4(1,0,1,1);
}

HitData Renderer::TraceRay(const Ray& ray)
{

    // if we are at the max depth of the scene return a black color since with enough bounces almost all light would be absorbed
    if (ray.depth >= 1)
        return Miss(ray);

    // trace the given ray into our scene, if it doesn't hit anything return the ambient scene color
    HitData hit;
    if (!m_scene->Hit(ray, hit))
    {
        return Miss(ray);
    }


    // TODO fix recursion/remove recursion
    // create a ray to scatter and ask materials bsdf we just hit what the new ray should be
    Ray scatter_ray;
    if (m_scene->materials.at(hit.materialID)->BSDF(ray, hit, scatter_ray))
        hit = TraceRay(scatter_ray);
    else if (m_scene->materials[hit.materialID]->Absorb(ray, hit))
        hit.color = glm::vec4(1); // TODO


    // get the color from this new ray

    return ClosestHit(ray);

    // return hit.color * light;
}

HitData Renderer::ClosestHit(const Ray& ray)
{
    return HitData();
}

HitData Renderer::Miss(const Ray& ray)
{
    return HitData();
}
