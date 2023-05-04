#pragma once
#include "yaScript.h"

namespace ya
{
	class ThunderScript : public Script
	{
	public:
		ThunderScript();
		~ThunderScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


		void EnergizedOn() { bEnergized = true; }

		void Move();

		void Start();
		void Action();
		void End();
		void Reset();
		void GameReset();
	private:

		int mDamage;

		bool bEnergized;

		float time;
	};
}