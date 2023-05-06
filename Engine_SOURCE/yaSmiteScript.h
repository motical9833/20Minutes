#pragma once
#include "yaScript.h"

namespace ya
{
	class SmiteScript : public Script
	{
	public:
		SmiteScript();
		~SmiteScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetHolyMightOn() { bHolyMightOn = true; }

		void Start();
		void Action();
		void End();
		void Reset();
		void GameReset();
	private:
		int mDamage;

		bool bHolyMightOn;
	};
}