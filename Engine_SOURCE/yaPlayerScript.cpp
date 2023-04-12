#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
		, bMove(false)
		, mHp(3)
		, bHitImmune(false)
		,immuneTime(0.0f)
	{
		
	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		//����Լ� �̱� ������ � �Լ����� Ǯ�������� ������� �Ѵ�.
		animator->GetStartEvent(L"pIdle") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"pIdle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"pIdle") = std::bind(&PlayerScript::End, this);
		animator->GetEvent(L"pIdle",1) = std::bind(&PlayerScript::End, this);
	}

	void PlayerScript::Update()
	{
		Move();

		if (bHitImmune)
		{
			immuneTime += Time::DeltaTime();

			if (immuneTime >= 3)
			{
				bHitImmune = false;
				immuneTime = 0;
			}
		}
	}

	void PlayerScript::Render()
	{

	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			if (bHitImmune)
				return;

			mHp--;
			bHitImmune = true;

			if (mHp <= 0)
				this->GetOwner()->Death();
		}
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{

	}

	void PlayerScript::Move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKeyPress(eKeyCode::D))
		{
			if (bMove == false)
			{
				bMove = true;
				animator->Play(L"pMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyPress(eKeyCode::A))
		{
			if (bMove == false)
			{
				bMove = true;
				animator->Play(L"pMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyPress(eKeyCode::W))
		{
			if (bMove == false)
			{
				bMove = true;
				animator->Play(L"pMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.y += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyPress(eKeyCode::S))
		{
			if (bMove == false)
			{
				bMove = true;
				animator->Play(L"pMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.y -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::NONE &&
			Input::GetKeyState(eKeyCode::D) == eKeyState::NONE &&
			Input::GetKeyState(eKeyCode::W) == eKeyState::NONE &&
			Input::GetKeyState(eKeyCode::S) == eKeyState::NONE &&
			bMove == true)
		{
			animator->Play(L"pIdle");
			bMove = false;
		}
	}

	void PlayerScript::Start()
	{

	}

	void PlayerScript::Action()
	{

	}
	void PlayerScript::End()
	{

	}
	void PlayerScript::Reset()
	{

	}
}