#pragma once
#include "yaScript.h"


namespace ya
{
	class Player;
	class Animator;
	class MonsterScript : public Script
	{
	public:
		MonsterScript();
		MonsterScript(int hp);
		~MonsterScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


		void Start();
		void Action();
		void End();
		void TakeDamage(int damage);
		void Reset();

		void Freeze();
		void Curse();
		void CurseActivate() { bCurse = true; }
		bool GetcurseAtivate() { return bCurse; }

	private:
		int mCurrentHp;
		int mMaxHp;
		float mSpeed;
		int mDamage;

		bool bFreeze;
		bool bCurse;

		float freezeTime;

		Vector2 mColliderSize;

		Player* player;
		Animator* animator;
	};
}