#include "yaEntity.h"

namespace ya
{
	Entity::Entity()
		: mID(reinterpret_cast<UINT32>(this))
	{
	}
	Entity::Entity(const Entity& other)
		: mID(reinterpret_cast<UINT32>(this))
		, mAnimationName(other.mAnimationName)
	{
	}
	Entity::~Entity()
	{
	}
}