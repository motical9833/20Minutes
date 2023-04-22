#include "yaCurseScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaMonsterScript.h"
namespace ya
{
	CurseScript::CurseScript()
	{
	}
	CurseScript::~CurseScript()
	{
	}
	void CurseScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"curseAni") = std::bind(&CurseScript::End, this);
	}
	void CurseScript::Update()
	{
	}
	void CurseScript::Render()
	{
	}
	void CurseScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void CurseScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CurseScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void CurseScript::Start()
	{
	}
	void CurseScript::Action()
	{
	}
	void CurseScript::End()
	{
		GameObject* monster = GetOwner()->GetComponent<Transform>()->GetParent()->GetOwner();

		monster->GetScript<MonsterScript>()->CurseActivate();
	}
	void CurseScript::Reset()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"curseAni", false);

		GetOwner()->Death();
	}
}