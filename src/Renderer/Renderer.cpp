#include "Renderer/Renderer.h"

#include <iostream>
#include <chrono>

#include <oneapi/tbb/parallel_for.h>

#include "imgui.h"

#include "Renderer/Ray.h"
#include "Renderer/Camera.h"
#include "Renderer/Scene.h"
#include "Assets/Material.h"

using namespace Rye;

int Renderer::Render()
{
    auto timer = std::chrono::steady_clock::now();

    m_camera->film.ResetAccumulator();

    m_camera->film.NewSample();

#define MT
#ifndef MT
    for (int i=0; i < m_camera->rayCount; ++i)
    {
        glm::vec4 color = RayGen(i);
        m_camera->film.SetPixel(i,color);
    }
#else
    using oneapi::tbb::parallel_for;
    parallel_for(size_t(0), size_t(m_camera->rayCount), [this](size_t i)
    {
        glm::vec3 color = RayGen(i);
        m_camera->film.SetPixel(i,color);
    });
#endif


    return (int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timer).count();
}

glm::vec3 Renderer::RayGen(int i)
{

    uint32_t seed = i + m_camera->film.Samples() * m_camera->rayCount;

    Ray ray;
    ray.origin = m_camera->GetRayOrigin();
    ray.direction = m_camera->GetRayDirection(i);

    glm::vec3 color = glm::vec3(1);

    if (m_camera->Inputting())
    {
        // if we are moving the camera return whatever the color of the first hit is
        HitData hit;
        hit.seed = 1;
        return TraceRay(ray, hit).color;
    }

    float hits;
    for (int b=0; b <= m_maxDepth; ++b)
    {
        if (b == m_maxDepth)
        {
            // if we are at max depth we haven't hit any light source so return black
            color = glm::vec4(0);
            break;
        }

        HitData hit;
        hit.seed = seed;
        TraceRay(ray, hit);

        color *= hit.color;

        if (hit.distance == std::numeric_limits<float>::max())
            break;

        if (!m_scene->GetMaterial(hit.materialID).BSDF(ray.direction, hit, ray.direction))
            break;

        ray.origin = hit.point;

        seed = hit.seed;
    }

    return color;
}

HitData Renderer::TraceRay(const Ray& ray, HitData& hit)
{
    // trace the given ray into our scene, if it doesn't hit anything return the ambient scene color
    if (!m_scene->Hit(ray, hit))
    {
        return Miss(ray, hit);
    }

    // get the color from this new ray
    return ClosestHit(ray, hit);
}

HitData Renderer::ClosestHit(const Ray& ray, HitData& hit) const
{
    m_scene->GetMaterial(hit.materialID).Color(ray.direction, hit);
    return hit;
}

HitData Renderer::Miss(const Ray& ray, HitData& hit) const
{
    hit.color = m_scene->ambientColor;
    return hit;
}

void Renderer::DrawControls()
{
    ImGui::DragInt("Max Depth", &m_maxDepth);
}
