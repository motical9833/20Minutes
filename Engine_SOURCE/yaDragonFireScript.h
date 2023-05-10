#pragma once
#include "yaScript.h"

namespace ya
{
	class DragonFireScript : public Script
	{
	public:
		DragonFireScript();
		~DragonFireScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetDir(Vector3 dir) { mDir = dir; }

		void SetDamage(int value) { mDamage += value; }
		void SetDamage(float value) { mDamageMul += value; }
		void SetDragonBondOn() { bDragonBond = true; }

		void Start();
		void Action();
		void End();
		void TakeDamage(int damage);
		void Reset();
		void GameReset();

	private:
		int mDamage;

		float mSpeed;
		float mTime;
		float crashTime;
		float mDamageMul;
		Vector3 mDir;

		bool bCrash;
		bool bDragonBond;
	};
}