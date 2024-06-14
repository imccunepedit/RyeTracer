#include "Renderer.h"

#include <iostream>


using namespace Rye;

void Renderer::Render()
{
    m_camera->film.samples ++;

    std::cout << m_camera->film.width << std::endl;
    for (int j=0; j < m_camera->film.height; j++)
    {
        for (int i=0; i < m_camera->film.width; i++)
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
    uint32_t seed = i + j * m_camera->film.width + m_camera->film.samples * m_camera->film.width * m_camera->film.height;

    ray.origin = m_camera->GetRayOrigin();
    ray.direction = m_camera->GetRayDirection(i, j);

    HitData hit;
    glm::vec4 color = glm::vec4(0);

    float attenuation = 1;
    for (int i=0; i < 5; i++)
    {
        attenuation *= 0.5f;
        hit =  TraceRay(ray);
        color += hit.color * attenuation;
        if (hit.distance == std::numeric_limits<float>::max())
            break;

        ray.origin = hit.point;
        hit.material->BSDF(ray.direction, hit, ray.direction);

    }

    return color;
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

    // get the color from this new ray
    return ClosestHit(ray, hit);
}

HitData Renderer::ClosestHit(const Ray& ray, HitData& hit)
{
    // std::cout << "hit" << std::endl;
    // TODO fix recursion/remove recursion
    // create a ray to scatter and ask materials bsdf we just hit what the new ray should be
    // Ray scatter_ray;
    // if (hit.material->BSDF(ray.direction, hit, scatter_ray.direction))
    //     hit = TraceRay(scatter_ray);
    // else if (hit.material->Absorb(ray.direction, hit))
    //     hit.color = glm::vec4(1); // TODO
    glm::vec4 dir;
    hit.material->BSDF(ray.direction, hit, dir);
    return hit;
}

HitData Renderer::Miss(const Ray& ray)
{
    HitData hit;
    hit.color = glm::vec4(0.6f,0.7f,0.75f, 1);
    return hit;
}
