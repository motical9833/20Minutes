#pragma once
#include "yaScript.h"


namespace ya
{
	class Player;
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;


		void SetTarget(Player* object) { target = object; }
	private:
		Player* target;
	};
}
