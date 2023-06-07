#pragma once
#include "yaScript.h"
#include "yaMonsterScript.h"

namespace ya
{
	class HubNigguratScript : public MonsterScript
	{
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


		void ChargeEnd();
		void AttackEnd();
		void DieMonster();

	private:

	};
}