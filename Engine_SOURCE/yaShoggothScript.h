#pragma once
#include "yaMonsterScript.h"


namespace ya
{
	class ShoggothScript : public MonsterScript
	{
		enum class States
		{
			MOVE,
			CHARGE,
			ATTACK,
		};
		States state = States::MOVE;

	public:
		ShoggothScript();
		ShoggothScript(int hp);
		virtual ~ShoggothScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


		void ChargeEnd();
		void AttackEnd();
		void DieMonster();

		void Idle();
		void Move();
		void Charge();
		void Attack();

	private:

		bool bAttack;

		float mCoolTime;
		Vector3 attackPos;
	};
}