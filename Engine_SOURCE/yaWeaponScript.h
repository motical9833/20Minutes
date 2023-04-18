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
		void BulletCnt(int count) { oneShotFire = count; } 


		void BulletSpeedUP(float percentage);
		void BulletSpeedDown(float percentage);
		void BulletScaleUp(float percentage);
		void BulletScaleDown(float percentage);
		void AttackSpeedUP(float percentage);
		void AttackSpeedDown(float percentage);
		void ReloadTimeUP(float percentage);
		void ReloadTimeDown(float percentage);
		void BulletCntUP();
		void BulletCntDown();
		void FirePosRot();

		void Fire();
		void WeaponRotate();

		void Start();
		void Action();
		void End();

		void Reset();
	private:

		void Cheat();

		bool bReload;
		bool bReloading;
		float time;
		float reloadTime;
		int maxBullet;
		int currentBullet;
		int oneShotFire;
		int allFireBulletCnt;

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
		float circleR;
		float deg;
		float objSpeed;

		PlayScene* pScene;
		std::vector<Transform*> bullets;
		std::vector<GameObject*> firePosObject;
	};
}