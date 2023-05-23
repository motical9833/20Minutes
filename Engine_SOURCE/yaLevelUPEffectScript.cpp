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
		SceneManager::GetPlayScene()->LevelUPUI();
		GetOwner()->Death();
	}
	void LevelUPEffectScript::Reset()
	{

	}
	void LevelUPEffectScript::LevelUPEffect()
	{
		GetOwner()->Life();
		GetOwner()->GetComponent<Animator>()->Play(L"LevelUPAni", false);
	}
}