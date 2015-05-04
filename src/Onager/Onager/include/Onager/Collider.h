
#pragma once


#include "defines.h"
#include "Shapes.h"
#include "MassProperties.h"

namespace ong
{

	struct WorldMemory;
	class World;
	class Body;

	template<typename T>
	class Allocator;

	typedef Allocator<Hull> HullAllocator;


	struct Material
	{
		float density;
		float restitution;
		float friction;
	};


	struct ColliderDescription
	{
		Transform transform;
		Material* material;
		ShapePtr shape;
	};

	struct ColliderData
	{
		Transform transform;
		Material* pMaterial;
		MassData massData;
		AABB aabb;
		ShapePtr shape;
	};


	// todo set shape
	class Collider
	{
	public:

		//	--CREATORS--
		Collider(const ColliderDescription& description);
		// create collider without recalculating all data
		Collider(const ColliderData& data);

		//	--MANIPULATORS--

		void setUserData(void* pUserData);

		void calculateMassProperties();

		void setMaterial(Material* material);

		void calculateAABB();

		void setPosition(const vec3& p);
		void translate(const vec3& translation);

		void setOrientation(const Quaternion& q);
		void rotate(const Quaternion& rotation);

		void setTransform(const Transform& t);

		//	--ACCESSORS--

		const MassData& getMassData();
		Body* getBody();
		const Body* getBody() const;

		void* getUserData() const;

		Transform& getTransform();
		const Transform& getTransform() const;

		Material* getMaterial();

		Collider* getNext();
		Collider* getPrev();

		const AABB& getAABB() const;

		const ShapePtr getShape() const;

		ColliderData getData() const;

	ong_internal:
		void setBody(Body* pBody);
		void setNext(Collider* pNext);
		void setPrev(Collider* pPrev);

	private:
		Body* m_pBody;

		Transform m_transform;

		Material* m_pMaterial;

		MassData m_massData;

		AABB m_aabb;
		ShapePtr m_shape;

		void* m_pUserData;

		Collider* m_prev;
		Collider* m_next;
	};




	inline void Collider::setUserData(void* pUserData)
	{
		m_pUserData = pUserData;
	}


	inline const MassData& Collider::getMassData()
	{
		return m_massData;
	}

	inline Collider* Collider::getNext()
	{
		return m_next;
	}

	inline Collider* Collider::getPrev()
	{
		return m_prev;
	}


	inline Transform& Collider::getTransform()
	{
		return m_transform;
	}

	inline const Transform& Collider::getTransform() const
	{
		return m_transform;
	}

	inline const ShapePtr Collider::getShape() const
	{
		return m_shape;
	}


	inline Material* Collider::getMaterial()
	{
		return m_pMaterial;
	}


	inline void* Collider::getUserData() const
	{
		return m_pUserData;
	}
}