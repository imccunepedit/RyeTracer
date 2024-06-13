#include "Renderer.h"

using namespace Barley;

void Renderer::Render()
{
    m_camera.film.samples ++;

    for (int j=0; j < m_camera.film.Height(); j++)
    {
        for (int i = 0; i < m_camera.film.Width(); i++)
        {
            glm::vec4 color = RayGen(i, j);
            m_camera.film.SetPixel(i,j,color);
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

    ray.origin = m_camera.GetRayOrigin();
    ray.direction = m_camera.GetRayDirection(i, j);

    Hit hit = TraceRay(ray);

    return hit.color;
}

Hit Renderer::TraceRay(const Ray& ray)
{

    // if we are at the max depth of the scene return a black color since with enough bounces almost all light would be absorbed
    if (ray.depth >= 1)
        return Miss(ray);

    // trace the given ray into our scene, if it doesn't hit anything return the ambient scene color
    Hit hit;
    if (!m_scene.hit(ray, hit))
    {
        return Miss(ray);
    }


    // TODO fix recursion/remove recursion
    // create a ray to scatter and ask materials bsdf we just hit what the new ray should be
    Ray scatter_ray;
    if (m_scene.materials.at(hit.material_id)->bsdf(ray, hit, scatter_ray))
        hit = TraceRay(scatter_ray);
    else if (m_scene.materials[hit.material_id]->absorb(ray, hit))
        hit.color = glm::vec4(1); // TODO


    // get the color from this new ray

    return ClosestHit(ray);

    // return hit.color * light;
}

Hit Renderer::ClosestHit(const Ray& ray)
{
    return Hit();
}

Hit Renderer::Miss(const Ray& ray)
{
    return Hit();
}
