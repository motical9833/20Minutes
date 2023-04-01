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
	{
		
	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		//멤버함수 이기 떄문에 어떤 함수인지 풀네임으로 적어줘야 한다.
		animator->GetStartEvent(L"pIdle") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"pIdle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"pIdle") = std::bind(&PlayerScript::End, this);
		animator->GetEvent(L"pIdle",1) = std::bind(&PlayerScript::End, this);
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();


		if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			tr->SetRotation(rot);
		}


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


		if (Input::GetKeyPress(eKeyCode::N_0))
		{
			animator->Play(L"pIdle");
		}
		if (Input::GetKeyPress(eKeyCode::N_1))
		{
			animator->Play(L"pMove");
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

	void PlayerScript::Render()
	{

	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			this->GetOwner()->Death();
		}
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{

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
}