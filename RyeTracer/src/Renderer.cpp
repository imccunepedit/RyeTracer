#include "Renderer.h"

#include <iostream>

#include <oneapi/tbb/parallel_for.h>


using namespace Rye;

void Renderer::Render()
{
    m_camera->film.NewSample();

#define MT
#ifndef MT
    std::cout << m_camera->film.width << std::endl;
    for (int j=0; j < m_camera->film.height; j++)
    {
        for (int i=0; i < m_camera->film.width; i++)
        {
            glm::vec4 color = RayGen(i, j);
            m_camera->film.SetPixel(i,j,color);
        }
    }

#else
    using oneapi::tbb::parallel_for;
    parallel_for(size_t(0), size_t(m_camera->film.height), [this](size_t j)
    {
        parallel_for(size_t(0), size_t(m_camera->film.width), [this,j](size_t i){
            glm::vec4 color = RayGen(i, j);
            m_camera->film.SetPixel(i,j,color);
        });
    });
#endif

}

glm::vec4 Renderer::RayGen(const int& i, const int& j)
{

    uint32_t seed = i + j * m_camera->film.width + m_camera->film.Samples() * m_camera->film.width * m_camera->film.height;

    Ray ray;
    ray.origin = m_camera->GetRayOrigin();
    ray.direction = m_camera->GetRayDirection(i, j);

    glm::vec4 color = glm::vec4(1);

    if (m_camera->Inputting())
    {
        // if we are moving the camera return whatever the color of the first hit is
        return TraceRay(ray).color;
    }

    for (int b=0; b <= m_maxDepth; b++)
    {
        if (b == m_maxDepth)
        {
            // if we are at max depth we haven't hit any light source so return black
            color = glm::vec4(0);
            break;
        }

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
    hit.color = m_scene->ambientColor;
    return hit;
}

void Renderer::DrawControls()
{
    ImGui::DragInt("Max Depth", &m_maxDepth);
}
