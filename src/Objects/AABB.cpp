#include "Objects/AABB.h"

#include <glm/geometric.hpp>
#include <glm/vector_relational.hpp>

#include <Utils/Log.h>

#include "Renderer/Ray.h"

using namespace Rye::Objects;

AABB::AABB(glm::vec3 a, glm::vec3 b, int materialID)
    : m_materialID(materialID)
{
    glm::vec3 min = glm::min(a,b);
    glm::vec3 max = glm::max(a,b);
    // glm::vec3 min = a;
    // glm::vec3 max = b;


    glm::vec3 dx = glm::vec3(max.x - min.x,0,0);
    glm::vec3 dy = glm::vec3(0,max.y - min.y,0);
    glm::vec3 dz = glm::vec3(0,0,max.z - min.z);

    // fix re initializing this... kinda stupid
    m_faces[0] = Quad(min, dx, dz, 0);
    m_faces[2] = Quad(min, dy, dx, 0);
    m_faces[1] = Quad(min, dz, dy, 0);
    m_faces[3] = Quad(max, -dx, -dy, 0);
    m_faces[4] = Quad(max, -dy, -dz, 0);
    m_faces[5] = Quad(max, -dz, -dx, 0);
}



bool AABB::Hit(const Ray& ray, HitData& hit, float t_min) const
{
    bool isHit = false;
    for (int i = 0; i < 6; ++i) {
        HitData temphit;
        temphit.seed = hit.seed;
        if (!m_faces[i].Hit(ray, temphit, t_min, true))
            continue;

        isHit = true;

        if (hit.distance < temphit.distance)
            continue;


        hit = temphit;
    }

    if (!isHit)
        return false;

    hit.materialID = m_materialID;
    return true;
}
