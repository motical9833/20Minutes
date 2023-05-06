#pragma once
#include "yaScript.h"

namespace ya
{
	class GaleScript : public Script
	{
	public:
		GaleScript();
		~GaleScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


		void SetDir(Vector3 dir) { mDir = dir; }
		void SetWindBorneOn() { bWindBorne = true; }
		void SetEyeoftheStormOn() { bEyeoftheStorm = true; }
		void SetDamageUP(int damage) { mDamage += damage; }

		void Start();
		void Action();
		void End();
		void TakeDamage(int damage);
		void Reset();
		void GameReset();
	private:

		bool bWindBorne;
		bool bEyeoftheStorm;
		int mDamage;

		float mSpeed;
		float mTime;
		float mEyeoftheTime;
		Vector3 mDir;
	};
}