#pragma once
#include "yaScript.h"

namespace ya
{
	class Player;
	class HolyShieldScript : public Script
	{
	public:
		HolyShieldScript();
		~HolyShieldScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();
		void Reset();

		void Break();

	private:
		Player* player;
		float rotTime;
	};
}