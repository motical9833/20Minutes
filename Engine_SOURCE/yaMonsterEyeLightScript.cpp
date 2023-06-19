#include "yaMonsterEyeLightScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"

namespace ya
{
	MonsterEyeLightScript::MonsterEyeLightScript(Vector3 leftDir, Vector3 rightDir)
		:leftPos(leftDir)
		,rightPos(rightDir)
	{
	}
	MonsterEyeLightScript::~MonsterEyeLightScript()
	{
	}
	void MonsterEyeLightScript::Initalize()
	{
	}
	void MonsterEyeLightScript::Update()
	{
	}
	void MonsterEyeLightScript::SetLeft()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_Left", true);
	}
	void MonsterEyeLightScript::SetRight()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_Right", true);
	}
	void MonsterEyeLightScript::SetLeftCharge()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_LeftCharge", false);
	}
	void MonsterEyeLightScript::SetRightCharge()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_RightCharge", false);
	}
	void MonsterEyeLightScript::SetLeftAttack()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_LeftAttack", false);
	}
	void MonsterEyeLightScript::SetRightAttack()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_RightAttack", false);
	}
	void MonsterEyeLightScript::SetLeftHit()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_LeftHit", false);
	}
	void MonsterEyeLightScript::SetRightHit()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_RightHit", false);
	}
}