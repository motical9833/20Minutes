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
		void SetAssassin() { bAssassin = true; }
		void SetDieBulletOn() { bDieBullet = true; }
		void SetScaleInc(float value) { mScaleMul += value; }
		void SetScaleDec(float value) { mScaleMul -= value; }

		float Getspeed() { return mSpeed; }
		float GetDamageInc() { return mDamageMul; }

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
		int mDamage;
		int mPenetrate;
		int mMaxPenetrate;
		Vector3 direction;
		


		Transform* mTr;
		Weapon* mWeapon;

		bool bCrash;
		bool bThunder;
		bool bAssassin;
		bool bDieBullet;
	};
}