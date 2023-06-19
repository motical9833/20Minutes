#include "yaPlayerLevelScript.h"
#include "yaSceneManager.h"
#include "yaPlayerScript.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaLevelUPEffectScript.h"
#include "yaInput.h"
#include "yaAudioSource.h"

namespace ya
{
	int mLevel;
	int mCurrentExp;
	int mLevelUpExp;
	PlayerLevelScript::PlayerLevelScript()
		:mLevel(1)
		, mCurrentExp(0.0f)
		, mLevelUpExp(5.0f)
	{

	}
	PlayerLevelScript::~PlayerLevelScript()
	{

	}
	void PlayerLevelScript::Initalize()
	{
		gaugeObj = SceneManager::GetPlayScene()->GetExpGauge();
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
		mCurrentExp = 0.0f;
		mLevelUpExp = 5.0f;
	}
	void PlayerLevelScript::LevelUP()
	{
		SceneManager::GetPlayScene()->GetSoundObjects(4)->GetComponent<AudioSource>()->Play();
		mLevel++;
		mLevelUpExp += 5.0f;
		mCurrentExp = 0.0f;
		gaugeObj->GetComponent<Transform>()->SetScale(Vector3(0.0f, 0.5f, 1.0f));
		SceneManager::GetPlayScene()->GetLevelUPEffect()->GetScript<LevelUPEffectScript>()->LevelUPEffect();
	}
	void PlayerLevelScript::GetExp()
	{
		mCurrentExp++;
		float gaugeX = mCurrentExp / mLevelUpExp * 38.0f;
		gaugeObj->GetComponent<Transform>()->SetScale(Vector3(gaugeX, 0.5f, 1.0f));

		if (mCurrentExp == mLevelUpExp)
			LevelUP();
	}
}