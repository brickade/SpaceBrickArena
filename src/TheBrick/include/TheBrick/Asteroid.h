#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "GameObject.h"

#include "DebugDraw.h"
#include "CSVParser.h"

namespace TheBrick
{
    class CAsteroid : public CGameObject
    {
    public:
        CAsteroid(/*CBrickManager* a_pBrickManager, */ong::World& a_rWorld, ong::vec3 a_Position);
        ~CAsteroid();

        void Update(float a_DeltaTime) override;

        void Deserialize(CSerializer& a_pSerializer, BrickArray& a_rBricks, ong::World& a_pWorld) override;
        void Serialize(CSerializer& a_pSerializer) override;
    };
}

#endif /* _ASTEROID_H_ */