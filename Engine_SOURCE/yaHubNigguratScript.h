#pragma once
#include "yaMonsterScript.h"

namespace ya
{
	class HubNigguratScript : public MonsterScript
	{
		enum class States
		{
			MOVE,
			CHARGE,
			ATTACK,
		};
		States state = States::MOVE;

	public:
		HubNigguratScript();
		HubNigguratScript(int hp);
		virtual ~HubNigguratScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void TakeDamage(int damage);
		void TakeDamage(int damage, eLayerType type);

		void DieChack();
		void DieChack(eLayerType type);

		void ChargeEnd();
		void AttackEnd();
		void DieMonster();

		void Idle();
		void Move();
		void Charge();
		void Attack();
		void HitEvent();

		void Respawn();
		void GameReset();
		void GameEnd();
		void DeadEvent();
	private:
		bool bAttack;

		float mCoolTime;
		Vector3 attackPos;
	};
}