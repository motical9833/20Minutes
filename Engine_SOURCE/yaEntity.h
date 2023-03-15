#pragma once
#include "yaEngine.h"

namespace ya
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& other);
		virtual ~Entity();

		void SetName(const std::wstring& name) { mAnimationName = name; }
		const std::wstring& GetName() { return mAnimationName; }
		UINT32 GetID() { return mID; }

	private:
		std::wstring mAnimationName;
		const UINT32 mID;
		
	};
}


