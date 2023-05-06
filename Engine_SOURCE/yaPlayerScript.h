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
		void GameReset();

		void IdleAniStart();
		void MoveAniStart();

		void TakeDamage(int damage);
		void SetMaxHP(int value) { mMaxHP = value; }
		void SetMaxHP_Add(int value) { mMaxHP += value; }
		void SetHealing() { mCurrentHP++; }
		void SetCurrentHP() { mCurrentHP = mMaxHP; }
		void SetSpeedMul(float value) { mSpeedMul += value; }
		float GetSpeedMul() { return mSpeedMul; }
		void ShieldOn() { bShield = true; }

		void StartSetting();


		bool GetIdle() { return bIdle; }

	private:
		float immuneTime;
		float mSpeed;
		float mSpeedMul;
		bool bMove;
		bool bHitImmune;
		int mCurrentHP;
		int mMaxHP;

		bool bShield;
		bool bIdle;
	};
}