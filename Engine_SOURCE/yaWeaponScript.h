#pragma once
#include "yaScript.h"
#include "yaAnimator.h"
#include "yaTransform.h"

namespace ya
{
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


		void Start();
		void Action();
		void End();
	private:

		bool bReload;
		bool bReloading;
		float time;
		float reloadTime;
		int maxBullet;
		int currentBullet;

		Animator* mAnimator;
		Transform* mTransform;

	};
}