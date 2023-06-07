#include "yaMonster.h"


namespace ya
{
	Monster::Monster()
	{

	}
	Monster::~Monster()
	{

	}
	void Monster::Initalize()
	{
		GameObject::Initalize();
	}
	void Monster::Update()
	{
		if (bStop)
			return;

		GameObject::Update();
	}
	void Monster::FixedUpdate()
	{
		if (bStop)
			return;

		GameObject::FixedUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
}
