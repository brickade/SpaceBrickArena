#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "GameObject.h"

#include "DebugDraw.h"
#include "CSVParser.h"
#include "Bullet.h"
#include "BrickManager.h"

namespace TheBrick
{
    class CSpaceship : public CGameObject
    {
    public:
        CCSVParser* m_pCSVFile;

    private:
        ong::vec3 m_TargetVec;
        ong::vec3 m_TargetAng;

    public:
        CSpaceship(ong::World& a_rWorld);
        ~CSpaceship();

        void Draw(PuRe_IGraphics* a_pGraphics, PuRe_Camera* a_pCamera) override;

        void Deserialize(CSerializer& a_pSerializer, CBrickManager& a_pBrickManager, ong::World& a_pWorld) override;
        void Update(float a_DeltaTime) override;

        void HandleInput(PuRe_IInput* a_pInput, float a_DeltaTime, std::vector<CBullet*>& a_rBullets, CBrickManager* a_pManager);

        void Thrust(float a_Thrust, float a_DeltaTime);
        void Spin(float a_Spin, float a_DeltaTime);
        void Move(PuRe_Vector2F a_Move, float a_DeltaTime);
        void Shoot(std::vector<CBullet*>& a_rBullets, CBrickManager* a_pManager, float a_DeltaTime);

        void Deserialize(CSerializer* a_pSerializer, CBrickManager* a_pBrickManager, ong::World* a_pWorld) override;
        void Serialize(CSerializer* a_pSerializer);
    };
}

#endif /* _SPACESHIP_H_ */