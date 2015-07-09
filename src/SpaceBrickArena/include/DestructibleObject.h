#ifndef _DESTRUCTIBLE_OBJECT_H_
#define _DESTRUCTIBLE_OBJECT_H_

#include "TheBrick\GameObject.h"


namespace sba
{

	struct SBrickDestruction;

	class CDestructibleObject : public TheBrick::CGameObject
	{
	private:
		SBrickDestruction* m_pCenterBrick;
	public:

		static void ImpulseResponse(ong::Collider* thisCollider, ong::Contact* contact);

		CDestructibleObject(ong::World& a_rWorld, ong::BodyDescription* a_pBodyDesc);

		void SetCenterBrick(SBrickDestruction* a_pCenterBrick);
		SBrickDestruction* getCenterBrick();

        void Build();

		void Deserialize(TheBrick::CSerializer& a_pSerializer, TheBrick::BrickArray& a_rBricks, ong::World& a_pWorld) override;
	};

}



#endif