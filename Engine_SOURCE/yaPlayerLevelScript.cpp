#include "yaPlayerLevelScript.h"
#include "yaSceneManager.h"
#include "yaPlayerScript.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaLevelUPEffectScript.h"

#include "yaInput.h"

namespace ya
{
	int mLevel;
	int mCurrentExp;
	int mLevelUpExp;
	PlayerLevelScript::PlayerLevelScript()
		:mLevel(1)
		, mCurrentExp(0)
		, mLevelUpExp(5)
	{

	}
	PlayerLevelScript::~PlayerLevelScript()
	{

	}
	void PlayerLevelScript::Initalize()
	{
		
	}
	void PlayerLevelScript::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			LevelUP();
		}
	}
	void PlayerLevelScript::Render()
	{

	}
	void PlayerLevelScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void PlayerLevelScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void PlayerLevelScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void PlayerLevelScript::Start()
	{

	}
	void PlayerLevelScript::Action()
	{

	}
	void PlayerLevelScript::End()
	{

	}
	void PlayerLevelScript::GameReset()
	{
		mLevel = 1;
		mCurrentExp = 0;
		mLevelUpExp = 5;
	}
	void PlayerLevelScript::LevelUP()
	{
		mLevel++;
		mLevelUpExp += 5;
		mCurrentExp = 0;
		SceneManager::GetPlayScene()->GetLevelUPEffect()->GetScript<LevelUPEffectScript>()->LevelUPEffect();
	}
	void PlayerLevelScript::GetExp()
	{
		mCurrentExp++;


		if (mCurrentExp == mLevelUpExp)
			LevelUP();
	}
}