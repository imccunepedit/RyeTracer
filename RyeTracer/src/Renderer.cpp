#include "Renderer.h"

#include <iostream>


using namespace Rye;

void Renderer::Render()
{
    m_camera->film.NewSample();

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

    uint32_t seed = i + j * m_camera->film.width + m_camera->film.Samples() * m_camera->film.width * m_camera->film.height;

    Ray ray;
    ray.origin = m_camera->GetRayOrigin();
    ray.direction = m_camera->GetRayDirection(i, j);

    glm::vec4 color = glm::vec4(1);

    int maxDepth = 5;
    if (m_camera->Inputting())
        maxDepth = 1;

    for (int i=0; i < maxDepth; i++)
    {
        HitData hit = TraceRay(ray);
        hit.seed = seed;
        color *= hit.color;

        if (hit.distance == std::numeric_limits<float>::max())
            break;

        if (!hit.material->BSDF(ray.direction, hit, ray.direction))
            break;

        ray.origin = hit.point;
        seed = hit.seed;
    }

    return color;
}

HitData Renderer::TraceRay(const Ray& ray)
{
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
    hit.material->Absorb(ray.direction, hit);
    return hit;
}

HitData Renderer::Miss(const Ray& ray)
{
    HitData hit;
    // hit.color = glm::vec4(0.6f,0.7f,0.75f, 1);
    return hit;
}
