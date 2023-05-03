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
		void Respawn();
		void GameReset();

		void SetDieBulletOn() { bDieBullet = true; }

		void KillClipOn() { bKillClip = true; }
		void Freeze();
		void Curse();
		void CurseActivate() { bCurse = true; }
		void DieBullet();
		bool GetcurseAtivate() { return bCurse; }
		int GetCurrentHP() { return mCurrentHp; }
		int GetMaxHP() { return mMaxHp; }

	private:
		int mCurrentHp;
		int mMaxHp;
		float mSpeed;
		int mDamage;

		bool bFreeze;
		bool bCurse;
		bool bDieBullet;
		bool bKillClip;

		float freezeTime;

		Vector2 mColliderSize;

		Player* player;
		Animator* animator;
	};
}