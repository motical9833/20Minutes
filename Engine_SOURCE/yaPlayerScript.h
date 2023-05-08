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
		void SetMaxHP_Add(int value) 
		{ 
			mMaxHP += value;
			mCurrentHP += value;
		}
		void SetHealing() { mCurrentHP++; }
		void SetCurrentHP() { mCurrentHP = mMaxHP; }
		void SetSpeedMul(float value) { mSpeedMul += value; }
		void SetSpeedRed(float value) { mSpeedMul -= value; }
		void SetslowSpeedMul(float value) { mslowSPeedMul += value; }
		void SetAngerPoint() { bAngerPointTrigger = true; }
		void SetScaleMul(float value);
		void SetScaleRed(float value);
		void SetRegeneration() { bRegeneration = true; }
		void SetShooting() { bShooting = true; };
		void SetDodgeRate(int value) { dodgeRate += value; }
		void SetReflexOn() { bReflex = true; }

		float GetSpeedMul() { return mSpeedMul; }
		bool GetPlayerHit() { return bPlayerHit; }

		void ShieldOn() { bShield = true; }

		void FireSlow();

		void StartSetting();
		void HPReset();

		bool Evasion();

		bool GetIdle() { return bIdle; }

	private:
		float immuneTime;
		float hitBuffTime;
		float regenerationTime;
		float slowTime;

		float mSpeed;
		float mslowSpeed;
		float mSpeedMul;
		float mslowSPeedMul;
		float mScaleMul;

		bool bMove;
		bool bHitImmune;
		bool bPlayerHit;
		bool bAngerPointTrigger;
		bool bRegeneration;
		bool bShooting;
		bool bReflex;

		int mCurrentHP;
		int mMaxHP;
		int dodgeRate;


		bool bShield;
		bool bIdle;
	};
}