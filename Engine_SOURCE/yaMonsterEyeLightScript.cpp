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
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(1000.0f, 1000.0f, 10.0f));
	}
	void MonsterEyeLightScript::Update()
	{
	}
	void MonsterEyeLightScript::SetLeft()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_Left", true);
		GetOwner()->GetComponent<Transform>()->SetPosition(leftPos);
	}
	void MonsterEyeLightScript::SetRight()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_Right", true);
		GetOwner()->GetComponent<Transform>()->SetPosition(rightPos);
	}
	void MonsterEyeLightScript::SetLeftCharge()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_LeftCharge", false);
		GetOwner()->GetComponent<Transform>()->SetPosition(leftPos);
	}
	void MonsterEyeLightScript::SetRightCharge()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_RightCharge", false);
		GetOwner()->GetComponent<Transform>()->SetPosition(rightPos);
	}
	void MonsterEyeLightScript::SetLeftAttack()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_LeftAttack", false);
		GetOwner()->GetComponent<Transform>()->SetPosition(leftPos);
	}
	void MonsterEyeLightScript::SetRightAttack()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_RightAttack", false);
		GetOwner()->GetComponent<Transform>()->SetPosition(rightPos);
	}
	void MonsterEyeLightScript::SetLeftHit()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_LeftHit", false);
		GetOwner()->GetComponent<Transform>()->SetPosition(leftPos);
	}
	void MonsterEyeLightScript::SetRightHit()
	{
		GetOwner()->GetComponent<Animator>()->Play(L"m_RightHit", false);
		GetOwner()->GetComponent<Transform>()->SetPosition(rightPos);
	}
}