#pragma once
#include "yaScript.h"
#include "yaMath.h"

namespace ya
{
	class PlayerMoveScript : public Script
	{
	public:
		PlayerMoveScript();
		~PlayerMoveScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		float GetPlayerSpeed() { return pSpeed; }
		void SetPlayerSpeed(float speed) { pSpeed = speed; }

	private:
		float pSpeed;
		Vector3 dir;
	};
}

