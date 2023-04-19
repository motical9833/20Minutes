#include "yaHolyShieldScript.h"
#include "yaAnimator.h"
#include "yaGameObject.h"
namespace ya
{
	HolyShieldScript::HolyShieldScript()
		:player{}
		,rotTime(0.0f)
	{

	}
	HolyShieldScript::~HolyShieldScript()
	{

	}
	void HolyShieldScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"HolyShieldBreak") = std::bind(&HolyShieldScript::End, this);
	}
	void HolyShieldScript::Update()
	{

	}
	void HolyShieldScript::Render()
	{

	}
	void HolyShieldScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void HolyShieldScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void HolyShieldScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void HolyShieldScript::Start()
	{

	}
	void HolyShieldScript::Action()
	{

	}
	void HolyShieldScript::End()
	{
		GetOwner()->Death();

		Animator* ani = GetOwner()->GetComponent<Animator>();

		ani->Play(L"HolyShieldIdle", true);
	}
	void HolyShieldScript::Reset()
	{

	}
	void HolyShieldScript::Break()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		ani->Play(L"HolyShieldBreak", false);
	}
}