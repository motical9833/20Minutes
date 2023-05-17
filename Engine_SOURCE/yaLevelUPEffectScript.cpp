#include "yaLevelUPEffectScript.h"
#include "yaAnimator.h"
#include "yaGameObject.h"

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
		GetOwner()->Death();
	}
	void LevelUPEffectScript::Reset()
	{

	}
}