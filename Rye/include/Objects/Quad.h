#ifndef QUAD_H_
#define QUAD_H_

#include "Plane.h"

namespace Rye {
    class Quad : public Plane {
        public:
            Quad(const glm::vec4 position, const glm::vec4 u, const glm::vec4 v, int materialID);
        protected:
            bool InsideBounds(glm::vec2 planarCoord) const override;
    };

}

#endif // QUAD_H_
