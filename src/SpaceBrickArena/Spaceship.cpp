#include "include/Spaceship.h"

#include "TheBrick/Conversion.h"
#include "TheBrick/BrickInstance.h"
#include "TheBrick/Brick.h"

#include "include/Player.h"
#include "include/Editor_BrickCategory.h"

namespace sba
{
    const int CSpaceship::MAX_BRICK_COUNT = 200;
    const int CSpaceship::MAX_BRICK_WIDTH = 20;
    const int CSpaceship::MAX_BRICK_HEIGHT = 15 * 3;

    // **************************************************************************
    // **************************************************************************
    CSpaceship::CSpaceship(ong::World& a_rWorld,std::string a_Name) : CGameObject(a_rWorld, nullptr)
    {
        this->m_Type = TheBrick::EGameObjectType::Ship;
        this->m_TargetVec = ong::vec3(0.0f, 0.0f, 0.0f);
        this->m_TargetAng = ong::vec3(0.0f, 0.0f, 0.0f);
        this->m_Name = a_Name;
        this->m_Respawn = 0.0f;
    }

    // **************************************************************************
    // **************************************************************************
    CSpaceship::~CSpaceship()
    {

    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Collision(ong::Collider* thisCollider, ong::Contact* contact)
    {
        CSpaceship* Ship = (CSpaceship*)thisCollider->getBody()->getUserData();
        ong::Collider* other;
        if (thisCollider == contact->colliderA)
            other = contact->colliderB;
        else
            other = contact->colliderA;

        CGameObject* object = static_cast<CGameObject*>(other->getBody()->getUserData());
        if (object->m_Type == TheBrick::EGameObjectType::Ship)
        {
            CSpaceship* oship = static_cast<CSpaceship*>(object);
            if (oship->m_Respawn == 0.0f)
                oship->m_Life -= 10;
            if (Ship->m_Respawn == 0.0f)
                Ship->m_Life -= 10;

            ong::vec3 diff = oship->m_pBody->getWorldCenter() - Ship->m_pBody->getWorldCenter(); //from oship to ship
            ong::vec3 impactVector = contact->manifold.normal;
            diff.x *= 50.0f;
            diff.y *= 50.0f;
            diff.z *= 50.0f;

            Ship->m_pBody->applyImpulse(-diff);
            oship->m_pBody->applyImpulse(diff);
        }
        else if (object->m_Type == TheBrick::EGameObjectType::Item)
        {
            CItem* item = static_cast<CItem*>(object);
            if (!item->m_Collided)
            {
                switch (item->GetType())
                {
                    case sba::EItemType::Repair:
                        Ship->m_Life += 10.0f;
                        if (Ship->m_Life  > Ship->m_MaxLife)
                            Ship->m_Life = Ship->m_MaxLife;
                        break;
                    case sba::EItemType::Shield:
                        Ship->m_Shield += 10.0f;
                        if (Ship->m_Shield  > 100.0f)
                            Ship->m_Shield = 100.0f;
                        break;
                }
                item->m_Collided = true;
            }
        }
        else if (object->m_Type == TheBrick::EGameObjectType::Bullet)
        {
            CBullet* bull = static_cast<CBullet*>(object);
            if (!bull->m_Collided)
            {
                if (Ship->m_Respawn == 0.0f)
                {
                    Ship->m_Life -= bull->m_Damage;
                    if (Ship->m_Life < 0)
                        bull->m_pOwner->m_Points += 10;
                }
                bull->m_Collided = true;
            }
        }
        else
        {

        }
        
            
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::CalculateData()
    {
        float mass = 1.0f/this->m_pBody->getInverseMass();
        this->m_RotationAcceleration = PuRe_Vector3F(mass*50.0f, mass*100.0f, mass*100.0f);
        this->m_SpeedAcceleration = mass*30.0f;
        this->m_MaxRotationSpeed = PuRe_Vector3F(2.0f, 2.0f, 2.0f);
        this->m_MaxSpeed = 15.0f*(20.0f/mass);
        this->m_MaxLife = (int)(mass*10.0f);
        this->m_Life = this->m_MaxLife;
        this->m_Shield = 0;


        ong::Collider* c = this->m_pBody->getCollider();
        ong::ColliderCallbacks cb;
        cb.beginContact = CSpaceship::Collision;

        while (c)
        {
            c->setCallbacks(cb);
            c = c->getNext();
        }
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Shoot(std::vector<CBullet*>& a_rBullets, SPlayer* a_pOwner,PuRe_Vector3F a_Forward)
    {
        if (this->m_Life > 0)
        {
            ong::Body* b = this->m_pBody;
            ong::World* w = b->getWorld();

            float len = TheBrick::OngToPuRe(this->m_pBody->getLinearVelocity()).Length();
            PuRe_Vector3F speed = a_Forward*100.0f + a_Forward * len;

            speed *= 1.0f/100.0f;
            a_rBullets.push_back(new CBullet(TheBrick::OngToPuRe(this->GetTransform().p) + a_Forward*10.0f, speed, *w, a_pOwner));
        }
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Spin(float a_Spin)
    {
        if (a_Spin > 0.2f || a_Spin < -0.2f)
            this->m_TargetAng.z = a_Spin * this->m_MaxRotationSpeed.X;
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Move(PuRe_Vector2F a_Move)
    {
        if (a_Move.Length() > 0.5f)
        {
            this->m_TargetAng.x = a_Move.Y * this->m_MaxRotationSpeed.Z;
            this->m_TargetAng.y = a_Move.X * this->m_MaxRotationSpeed.Y;
        }

    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Thrust(float a_Thrust)
    {
        if (a_Thrust > 0.2f || a_Thrust < -0.2f)
            this->m_TargetVec.z += a_Thrust * this->m_MaxSpeed;
    }
    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Update(float a_DeltaTime)
    {
        if (this->m_Respawn > 0.0f)
        {
            this->m_Respawn -= a_DeltaTime;
            if (this->m_Respawn < 0.0f)
            {
                this->m_Respawn = 0.0f;
                float x = (this->m_pBricks.size() % 10) * 10.0f;
                float y = (this->m_pBricks.size() % 5) * 10.0f;
                float z = (this->m_pBricks.size() % 8) * 10.0f;
                this->m_pBody->setPosition(ong::vec3(x, y, z));
                this->m_Life = this->m_MaxLife;
            }
        }
        else
        {
            ong::vec3 currVel = ong::rotate(this->m_pBody->getLinearVelocity(), ong::conjugate(this->m_pBody->getOrientation()));
            ong::vec3 currAng = ong::rotate(this->m_pBody->getAngularVelocity(), ong::conjugate(this->m_pBody->getOrientation()));

            float forAcc = this->m_SpeedAcceleration;
            float yawAcc = this->m_RotationAcceleration.Y;
            float pitchAcc = this->m_RotationAcceleration.Z;
            float rollAcc = this->m_RotationAcceleration.X;
            // negate rotational velocity
            this->m_pBody->applyRelativeImpulse(1.0f / this->m_pBody->getInverseMass() * ong::vec3(this->m_TargetVec.x - currVel.x, this->m_TargetVec.y - currVel.y, 0));

            // apply thrust
            if (lengthSq(currVel - this->m_TargetVec) > 0.1f * 0.1f)
                this->m_pBody->applyRelativeForce(hadamardProduct(ong::vec3(0, 0, forAcc), normalize(this->m_TargetVec - currVel)), a_DeltaTime);

            //apply rotation
            if (ong::lengthSq(currAng - this->m_TargetAng) > 0.0f)
            {

                ong::vec3 f = ong::hadamardProduct(ong::vec3(pitchAcc, yawAcc, rollAcc), ong::normalize(this->m_TargetAng - currAng));
                ong::vec3 dAng = this->m_pBody->getInverseMass() * a_DeltaTime* f;

                if (ong::lengthSq(dAng) > ong::lengthSq(currAng - this->m_TargetAng))
                {
                    ong::vec3 dAngularMomentum = 1.0f / this->m_pBody->getInverseMass() * (this->m_TargetAng - currAng);
                    this->m_pBody->applyRelativeAngularImpulse(dAngularMomentum);
                }
                else
                {
                    this->m_pBody->applyRelativeTorque(f, a_DeltaTime);
                }
            }

            //this->m_Transform = this->m_pBody->getTransform();
            this->m_TargetVec = ong::vec3(0.0f,0.0f,0.0f);
            this->m_TargetAng = ong::vec3(0.0f, 0.0f, 0.0f);

            ong::Transform t = ong::Transform(ong::vec3(0.0f, 0.0f, 0.0f), ong::Quaternion(ong::vec3(0, 0, 0), 1));
        }
    }

    // **************************************************************************
    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Deserialize(TheBrick::CSerializer& a_pSerializer, TheBrick::BrickArray& a_rBricks, ong::World& a_pWorld)
    {
        CGameObject::Deserialize(a_pSerializer, a_rBricks, a_pWorld);
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Serialize(TheBrick::CSerializer& a_pSerializer)
    {
        CGameObject::Serialize(a_pSerializer);
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::Reset(TheBrick::CBrick& a_rStartBrick, ong::World& a_rWorld)
    {
        for (size_t i = 0; i < this->m_pBricks.size(); i++)
        {
            SAFE_DELETE(this->m_pBricks[i]);
            i--;
        }
        TheBrick::CBrickInstance* brickInstance = a_rStartBrick.CreateInstance(*this, a_rWorld);
        brickInstance->SetTransform(ong::Transform(ong::vec3(0, 0, 0), ong::Quaternion(ong::vec3(0, 0, 0), 1)));
        brickInstance->RotateAroundPivotOffset(PuRe_QuaternionF(0.0f, 0.0f, 0.0f));
        brickInstance->m_Color = PuRe_Color(0, 0, 1);
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::GetWeapons(std::vector<TheBrick::CBrickInstance**>& a_rOutVector)
    {
        for (std::vector<TheBrick::CBrickInstance*>::iterator it = this->m_pBricks.begin(); it != this->m_pBricks.end(); ++it)
        {
            if ((*it)->m_pBrick->GetCategoryId() == Editor::CBrickCategory::CATEGORY_WEAPONS)
            {
                a_rOutVector.push_back(&(*it));
            }
        }
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::GetEngines(std::vector<TheBrick::CBrickInstance**>& a_rOutVector)
    {
        for (std::vector<TheBrick::CBrickInstance*>::iterator it = this->m_pBricks.begin(); it != this->m_pBricks.end(); ++it)
        {
            if ((*it)->m_pBrick->GetCategoryId() == Editor::CBrickCategory::CATEGORY_ENGINES)
            {
                a_rOutVector.push_back(&(*it));
            }
        }
    }

    // **************************************************************************
    // **************************************************************************
    void CSpaceship::GetCockpits(std::vector<TheBrick::CBrickInstance**>& a_rOutVector)
    {
        for (std::vector<TheBrick::CBrickInstance*>::iterator it = this->m_pBricks.begin(); it != this->m_pBricks.end(); ++it)
        {
            if ((*it)->m_pBrick->GetCategoryId() == Editor::CBrickCategory::CATEGORY_COCKPITS)
            {
                a_rOutVector.push_back(&(*it));
            }
        }
    }
}