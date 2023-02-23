#pragma once
#include "yaMath.h"
#include "yaEntity.h"

using namespace ya::enums;
namespace ya
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initalize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		eComponentType GetOrder() { return mType; }
		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }

	private:
		const  eComponentType mType;
		GameObject* mOwner;
	};
}