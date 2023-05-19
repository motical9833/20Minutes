#pragma once
#include "yaScript.h"

namespace ya
{
	class ExpMarbleObject : public Script
	{
	public:
		ExpMarbleObject();
		virtual ~ExpMarbleObject();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
		

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


		void Start();
		void Action();
		void End();
		void GameReset();
		void Reset();


	private:

		bool bTarget;
		float mTime;
		float mSpeed;

		Vector3 mDir;
		GameObject* mTarget;
	};
}