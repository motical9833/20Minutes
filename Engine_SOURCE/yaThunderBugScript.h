#pragma once
#include "yaScript.h"


namespace ya
{
	class ThunderBugScript : public Script
	{
	public:
		ThunderBugScript(int cnt);
		~ThunderBugScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();
		void Reset();	

		void Circularmotion();
		void LookPayer();

		void SetDir(Vector3 dir) { mDir = dir; }
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

		bool bAttack;
		Vector3 mDir;
	};
}