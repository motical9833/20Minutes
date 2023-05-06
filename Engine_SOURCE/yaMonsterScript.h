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
		void TakeDamage(int damage,eLayerType type);
		void RitualStack();
		void Respawn();
		void GameReset();

		void DieChack();
		void DieChack(eLayerType type);

		void SetDieBulletOn() { bDieBullet = true; }
		void SetCurseMul(float value) { curseMul += value; }
		void SetFrostbiteOn() { bFrostbite = true; }

		void KillClipOn() { bKillClip = true; }
		void Freeze();
		void Curse();
		void SetCurseActivate() { bCurseActivate = true; }
		void SetBeCursed() { beCursed = true; }
		void SetbWitherOn() { bWitherOn = true; }
		void SetbRitualOn() { bRitualOn = true; }
		void DieBullet();
		bool GetcurseAtivate() { return bCurseActivate; }
		int GetCurrentHP() { return mCurrentHp; }
		int GetMaxHP() { return mMaxHp; }

	private:
		int mCurrentHp;
		int mMaxHp;
		float mSpeed;
		int mDamage;
		int curseMul;

		bool bFreeze;
		bool bFrostbite;
		bool bCurseActivate;
		bool beCursed;
		bool bWitherOn;
		bool bRitualOn;
		bool bDieBullet;
		bool bKillClip;

		float freezeTime;

		Vector2 mColliderSize;

		Player* player;
		Animator* animator;
	};
}