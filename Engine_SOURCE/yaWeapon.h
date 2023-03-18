#pragma once
#include "yaGameObject.h"


namespace ya
{
	class Weapon : public GameObject
	{
	public:
		Weapon();
		virtual ~Weapon();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:

	};
}