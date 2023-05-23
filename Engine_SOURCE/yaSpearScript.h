#pragma once
#include "yaScript.h"



namespace ya
{
	class SpearScript : public Script
	{
	public:
		SpearScript(int cnt);
		~SpearScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();
		void GameReset();

		void Circularmotion();
		void LookPayer();

		void SetDir(Vector3 dir) { mDir = dir; }
		void SetHolySPearOn() { bHolySpear = true; }
		void SetSoulKnightOn() { bSoulKnight = true; }
		void Attack();

		bool GetBAttack() { return bAttack; };
	
	private:
		float mSpeed;
		float mFireSpeed;
		float mWidth;
		float mHeight;
		float mTime;
		float mAttackTime;
		float value;
		int mDamage;

		bool bAttack;
		bool bHolySpear;
		bool bSoulKnight;
		Vector3 mDir;
	};
}