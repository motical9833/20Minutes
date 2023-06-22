#pragma once
#include "yaScript.h"
#include "yaGameObject.h"

namespace ya
{
	class PlayerLevelScript : public Script
	{
	public:
		PlayerLevelScript();
		~PlayerLevelScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;


		void Start();
		void Action();
		void End();
		void GameReset();

		void SetCurrentExp() { mCurrentExp++; };

		void LevelUP();
		void GetExp();
		void LevelUICont(int level);

	private:
		GameObject* gaugeObj;

		int mLevel;
		int leveltenStack;

		float mCurrentExp;
		float mLevelUpExp;
	};
}