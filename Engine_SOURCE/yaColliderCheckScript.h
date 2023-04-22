#pragma once
#include "yaScript.h"
#include "yaMonster.h"

namespace ya
{
	using namespace std;
	class ColliderCheckScript : public Script
	{
	public:
		ColliderCheckScript();
		~ColliderCheckScript();

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

		list<Monster*> GetMonsters() { return monsters; }

	private:
		list<Monster*> monsters;
	};
}