#include "yaWeapon.h"


namespace ya
{
	Weapon::Weapon()
		:bStop(false)
	{

	}
	Weapon::~Weapon()
	{

	}
	void Weapon::Initalize()
	{
		GameObject::Initalize();
	}
	void Weapon::Update()
	{
		if (bStop)
			return;

		GameObject::Update();
	}
	void Weapon::FixedUpdate()
	{
		if (bStop)
			return;

		GameObject::FixedUpdate();
	}
	void Weapon::Render()
	{
		GameObject::Render();
	}
}