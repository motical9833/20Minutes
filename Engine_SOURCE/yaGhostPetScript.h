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
		void MousePosActtack(int BulletCnt);

		void SetAttackSpeedMul(float vlaue) { mAttackSpeedMul += vlaue; }
		void SetAttackSpeedRed(float vlaue) { mAttackSpeedMul -= vlaue; }
		void SetVengefulGhostOn() { bVengefulGhost = true; }
		void SetTargetToMouseOn() { bTargetToMouse = true; }
		void Circularmotion();
		void GameReset();

	private:
		float mSpeed;
		float mWidth;
		float mHeight;
		float mTime;
		float mAttackTime;
		float mAttackSpeedMul;

		bool bVengefulGhost;
		bool bTargetToMouse;

		Vector3 mDir;
	}; 
}