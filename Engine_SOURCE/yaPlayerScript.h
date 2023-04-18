#pragma once
#include "yaScript.h"


namespace ya
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Move();

		void Start();
		void Action();
		void End();
		void Reset();
		
		void TakeDamage(int damage);
		void SetMaxHP(int value) { mMaxHP = value; }
		void SetCurrentHP() { mCurrentHP = mMaxHP; }

	private:
		float immuneTime;
		bool bMove;
		bool bHitImmune;
		int mCurrentHP;
		int mMaxHP;

		bool mShield;
	};
}
