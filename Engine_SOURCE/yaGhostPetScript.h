#pragma once
#include "yaScript.h"


namespace ya
{
	class GhostPetScript : public Script
	{
	public:
		GhostPetScript();
		~GhostPetScript();

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

		void Attack();

		void Circularmotion();


	private:
		float mSpeed;
		float mWidth;
		float mHeight;
		float mTime;
		float mAttackTime;

		Vector3 mDir;
	}; 
}