#include "yaPlayer.h"


namespace ya
{



	Player::Player()
		:bStop(false)
	{
	}

	Player::~Player()
	{
	}

	void Player::Initalize()
	{
		GameObject::Initalize();
	}

	void Player::Update()
	{
		if (bStop)
			return;

		GameObject::Update();
	}

	void Player::FixedUpdate()
	{
		if (bStop)
			return;

		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}
