#include "yaLevelUPEffectScript.h"
#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaPlayerLevelScript.h"

namespace ya
{
	LevelUPEffectScript::LevelUPEffectScript()
	{
	}
	LevelUPEffectScript::~LevelUPEffectScript()
	{
	}
	void LevelUPEffectScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"LevelUPAni") = std::bind(&LevelUPEffectScript::End, this);
	}
	void LevelUPEffectScript::Update()
	{

	}
	void LevelUPEffectScript::FixedUpdate()
	{
	}
	void LevelUPEffectScript::Render()
	{

	}
	void LevelUPEffectScript::Start()
	{

	}
	void LevelUPEffectScript::Action()
	{

	}
	void LevelUPEffectScript::End()
	{
		//SceneManager::GetPlayScene()->SetStop();
		GetOwner()->Death();
		SceneManager::GetPlayScene()->GetLevelManager()->GetScript<PlayerLevelScript>()->LevelUP();
	}
	void LevelUPEffectScript::Reset()
	{

	}
}