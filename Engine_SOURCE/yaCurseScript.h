#pragma once
#include "yaScript.h"


namespace ya
{
	class CurseScript : public Script
	{
	public:
		CurseScript();
		~CurseScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


		void SetCurseUpgrade() { bUpgrade = true; }
		void SetWither() { beWither = true;; }
		void Start();
		void Action();
		void End();
		void Reset();

	private:
		bool bUpgrade;
		bool beWither;

	};
}