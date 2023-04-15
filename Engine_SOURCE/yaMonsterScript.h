#pragma once
#include "yaScript.h"


namespace ya
{
	class MonsterScript : public Script
	{
	public:
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

	private:
		int mCurrentHp;
		int mMaxHp;
		float mSpeed;

		Vector2 mColliderSize;
	};
}