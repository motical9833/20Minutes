#pragma once
#include "yaScript.h"
#include "yaAnimator.h"
#include "yaTransform.h"

namespace ya
{
	class PlayScene;
	class WeaponScript : public Script
	{
	public:
		WeaponScript();
		~WeaponScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Reload();

		void SetBullets(Transform* bullet) { bullets.push_back(bullet); }
		void SetFirePosObject(GameObject* object) { firePosObject.push_back(object); }
		void SetBulletCnt(int count) { oneShotFire += count; } 

		void FirePosRot();
		void ReloadSkill();
		void FanFire();
		void BackFire();
		void IceShardFire();

		void SetFireRotMul(float value) { fireRotmul += value; }
		void SetFireRotRed(float value) { fireRotmul -= value; }
		void SetFireDelayTimeInc(float value) { fireDelayTimeMul += value; }
		void SetFireDelayTimeDec(float value) { fireDelayTimeMul -= value; }
		void SetMaxBullet(int value) { maxBullet += value; currentBullet = maxBullet; }
		void SetReloadTimeMul(float value) { reloadTimeMul += value; }
		void SetReloadTimeRed(float value) { reloadTimeMul -= value; }
		void SetBounceTrigger() { bBounceTrigger = true; }
		void SetbSiege() { bSiege = true; }
		void SetFanFire() { bFanFireTrigger = true; }
		void SetBackFire() { bBackFire = true; }
		void SetKillCntInc() { killClip += 0.05f; }
		void SetThunderOn() { bThunder = true; }
		void SetFreezeOn() { bFreezeTrigger = true; }
		void SetIceShardOn() { bIceShard = true; }
		void SetCurseOn() { bCurseTrigger = true; }
		void SetRitualStack();
		void SetHolyAttack() { bHolyAttack = true; }
		void SetGaleTrigger() { bGaleTrigger = true; }

		void BulletSupply(int count);

		void Gale();
		void Smite();

		void Fire();
		void WeaponRotate();

		void Start();
		void Action();
		void End();

		void BulletUIReset();
		void MaxBulletUISetting();
		void Reset();
		void GameReset();

	private:

		void Cheat();

		bool bReload;
		bool bReloading;
		bool bBounceTrigger;
		bool bSiege;
		bool bBackFire;
		bool bFanFireTrigger;
		bool bFanFire;
		bool bThunder;
		bool bFreezeTrigger;
		bool bCurseTrigger;
		bool bIceShard;
		bool bHolyAttack;
		bool bGaleTrigger;

		float time;
		float reloadTime;
		float fanFireTime;
		float rateFireTime;
		float killClip;

		int maxBullet;
		int currentBullet;
		int oneShotFire;
		int allFireBulletCnt;
		int fanFireCnt;
		int ritualStack;

		Animator* mAnimator;
		Transform* mTransform;


		Transform* mTrans;
		Vector3 mMousePos;
		Vector3 mPos;
		Vector3 mRot;
		Vector3 pPos;

		Vector3 bulletPos;
		Vector3 bulletRot;

		float fireDelayTime;
		float fireDelayTimeMul;
		float reloadTimeMul;
		float circleR;
		float deg;
		float objSpeed;

		float fireRotmul;

		PlayScene* pScene;
		std::vector<Transform*> bullets;
		std::vector<GameObject*> firePosObject;
	};
}