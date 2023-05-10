#pragma once
#include "yaScript.h"

namespace ya
{
	class Weapon;
	class Scene;
	class Transform;
	class BulletScript : public Script
	{

	public:
		BulletScript();
		~BulletScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Setdir(Vector3 dir) { GetOwner()->GetComponent<Transform>()->SetRotation(dir); }
		void SetSpeed(float speed) { mSpeed = speed; }
		void SetSpeedMul(float speed) { mSpeedMul += speed; }
		void SetSpeedReduction(float speed) { mSpeedMul -= speed; }
		void SetPenetrateInc(int value) { mMaxPenetrate += value; }
		void SetPenetrateDec(int value) { mMaxPenetrate -= value; }
		void SetDamageInc(float value) { mDamageMul += value; }
		void SetDamageDec(float value) { mDamageMul -= value; }
		void SetAssassin() { bAssassin = true; }
		void SetDieBulletOn() { bDieBullet = true; }
		void SetScaleInc(float value) { mScaleMul += value; }
		void SetScaleDec(float value) { mScaleMul -= value; }
		void SetCurse() { bCurse = true; }

		void SetFreezeBullet() { bFreeze = true; }
		void SetBounceTrigger() { bBounceTrigger = true; }
		void SetIgnitionBullet() { bIgnitionBullet = true; }
		void SetBounceCntAdd(int value) { mBounceCnt += value; }
		void SetMagicLensOn() { bMagicLensOn = true; }


		void Freeze(Collider2D* collider);
		void Curse(Collider2D* collider);

		void PlayerHitChack();

		float Getspeed() { return mSpeed; }
		float GetDamageInc() { return mDamageMul; }
		bool GetMagicLensOn() { return bMagicLensOn; }

		void Start();
		void Action();
		void End();

		void Reset();
		void GameReset();
		void ThunderEnchantOn() { bThunder = true; };
	private:
		float mSpeed;
		float mSpeedMul;
		float time;
		float crashTime;
		float mDamageMul;
		float mScaleMul;
		int mIgnitionDamage;
		int mDamage;
		int mPenetrate;
		int mMaxPenetrate;
		int mBounceCnt;
		Vector3 direction;
		


		Transform* mTr;
		Weapon* mWeapon;

		bool bCrash;
		bool bThunder;
		bool bAssassin;
		bool bDieBullet;
		bool bBounce;
		bool bBounceTrigger;
		bool bFreeze;
		bool bCurse;
		bool bPlayerhit;
		bool bIgnitionBullet;
		bool bMagicLensOn;
	};
}