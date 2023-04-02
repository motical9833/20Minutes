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

		void Setdir(Vector3 dir) { direction = dir; }
		void SetSpeed(float speed) { mSpeed = speed; }
		float Getspeed() { return mSpeed; }

		void Start();
		void Action();
		void End();

	private:
		float mSpeed;
		float time;
		Vector3 direction;


		Transform* mTr;
		Scene* playScene;
		Weapon* mWeapon;
	};
}