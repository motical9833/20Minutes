#pragma once
#include "yaScript.h"

namespace ya
{
	class PlayScene;
	class DragonPetScript : public Script
	{
	public:
		DragonPetScript();
		~DragonPetScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetmAttackSpeedMul(float value) { mAttackSpeedMul += value; }
		void SetmAttackSpeedRed(float value) { mAttackSpeedMul -= value; }
		void Start();
		void Action();
		void End();
		void GameReset();

		void Attack();

		void Circularmotion();


	private:
		float mSpeed;
		float mWidth;
		float mHeight;
		float mTime;
		float mAttackTime;
		float mincubatorTime;
		float mAttackSpeedMul;

		bool bAttack;
		bool bHatch;

		PlayScene* pscene;
	};
}