#include "Objects/Quad.h"

#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Rye;

Quad::Quad(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, int materialID)
: Plane(position, u, v, materialID) {}

bool Quad::InsideBounds(glm::vec2 planarCoord) const
{
    if (planarCoord.x < 0 || planarCoord.x > 1)
        return false;

    if (planarCoord.y < 0 || planarCoord.y > 1)
        return false;

    return true;
}


