#pragma once
#include "yaScript.h"


namespace ya
{
	class GhostBullet :public Script
	{
	public:
		GhostBullet();
		~GhostBullet();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetDir(Vector3 dir) { mDir = dir; }
		void SetDamageMul(float value) { mDamageMul += value; }
		void SetTargetMouse() { bTargetMouse = true; }

		void Start();
		void Action();
		void End();
		void TakeDamage(int damage);
		void Reset();
		void GameReset();

		void TargetMouse();
		void TargetMonster();
	private:
		int mDamage;

		float mSpeed;
		float mTime;
		float mDamageMul;

		bool bTargetMouse;

		Vector3 mDir;
	};
}