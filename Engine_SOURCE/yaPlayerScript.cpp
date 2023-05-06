#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSkillManager.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
namespace ya
{
	PlayerScript::PlayerScript()
		: Script()
		, bMove(false)
		, mCurrentHP(0)
		, mMaxHP(3)
		, bHitImmune(false)
		, immuneTime(0.0f)
		, mSpeed(6.0f)
		, mSpeedMul(1.0f)
		, bShield(true)
		, bIdle(false)
		//, rotTime(0.0f)
	{
		
	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		//멤버함수 이기 떄문에 어떤 함수인지 풀네임으로 적어줘야 한다.
		animator->GetStartEvent(L"pRightIdle") = std::bind(&PlayerScript::IdleAniStart, this);
		animator->GetStartEvent(L"pLeftIdle") = std::bind(&PlayerScript::IdleAniStart, this);

		animator->GetStartEvent(L"pLeftMove") = std::bind(&PlayerScript::MoveAniStart, this);
		animator->GetStartEvent(L"pRightMove") = std::bind(&PlayerScript::MoveAniStart, this);
	}

	void PlayerScript::Update()
	{
	    Move();
		//rotTime += Time::DeltaTime();

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
			int a = 0;
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

		Animation* ani = animator->GetActiveAnimation();
		{
			if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED && 
				Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED &&
				Input::GetKeyState(eKeyCode::W) == eKeyState::NONE&&
				Input::GetKeyState(eKeyCode::S) == eKeyState::NONE)
			{
				return;
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::D) == eKeyState::DOWN)
			{
				animator->Play(L"pLeftIdle");
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::DOWN && Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				animator->Play(L"pRightIdle");
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::D) == eKeyState::UP)
			{
				animator->Play(L"pLeftMove");
			}
			else if (Input::GetKeyState(eKeyCode::A) == eKeyState::UP && Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				animator->Play(L"pRightMove");
			}
		}
		{
			if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED&&
				Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED&&
				Input::GetKeyState(eKeyCode::A) == eKeyState::NONE&&
				Input::GetKeyState(eKeyCode::D) == eKeyState::NONE)
			{
				return;
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::W) == eKeyState::DOWN && ani->AnimationName() == L"pRightMove"
				|| Input::GetKeyState(eKeyCode::S) == eKeyState::DOWN && Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED && ani->AnimationName() == L"pRightMove")
			{
				animator->Play(L"pRightIdle");
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::W) == eKeyState::DOWN && ani->AnimationName() == L"pLeftMove"
				|| Input::GetKeyState(eKeyCode::S) == eKeyState::DOWN && Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED && ani->AnimationName() == L"pLeftMove")
			{
				animator->Play(L"pLeftIdle");
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::W) == eKeyState::UP && ani->AnimationName() == L"pLeftIdle")
			{
				animator->Play(L"pLeftMove");
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::W) == eKeyState::UP && ani->AnimationName() == L"pRightIdle")
			{
				animator->Play(L"pRightMove");
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::UP && Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED && ani->AnimationName() == L"pLeftIdle")
			{
				animator->Play(L"pLeftMove");
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::UP && Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED && ani->AnimationName() == L"pRightIdle")
			{
				animator->Play(L"pRightMove");
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::D) == eKeyState::DOWN && ani->AnimationName() == L"pLeftMove")
			{
				animator->Play(L"pRightMove");
			}
			else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::A) == eKeyState::DOWN && ani->AnimationName() == L"pRightMove")
			{
				animator->Play(L"pLeftMove");
			}
			else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::D) == eKeyState::DOWN && ani->AnimationName() == L"pLeftMove")
			{
				animator->Play(L"pRightMove");
			}
			else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED && Input::GetKeyState(eKeyCode::A) == eKeyState::DOWN && ani->AnimationName() == L"pRightMove")
			{
				animator->Play(L"pLeftMove");
			}
		}


		if (Input::GetKeyPress(eKeyCode::D))
		{
			if (bMove == false)
			{
				bMove = true;
				animator->Play(L"pRightMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.x += mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyPress(eKeyCode::A))
		{
			if (bMove == false)
			{
				bMove = true;
				animator->Play(L"pLeftMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.x -= mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::W) && ani->AnimationName() == L"pRightIdle")
		{
			animator->Play(L"pRightMove");
		}
		else if (Input::GetKeyDown(eKeyCode::W) && ani->AnimationName() == L"pLeftIdle") 
		{
			animator->Play(L"pLeftMove");
		}
		else if (Input::GetKeyPress(eKeyCode::W))
		{
			if (bMove == false)
			{
				bMove = true;
			}
			Vector3 pos = tr->GetPosition();
			pos.y += mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKeyUp(eKeyCode::W) && ani->AnimationName() == L"pRightMove")
		{
			animator->Play(L"pRightIdle");
			bMove = false;
		}
		else if (Input::GetKeyUp(eKeyCode::W) && ani->AnimationName() == L"pLeftMove")
		{
			animator->Play(L"pLeftIdle");
			bMove = false;
		}

		if (Input::GetKeyDown(eKeyCode::S) && ani->AnimationName() == L"pRightIdle")
		{
			animator->Play(L"pRightMove");
		}
		else if (Input::GetKeyDown(eKeyCode::S) && ani->AnimationName() == L"pLeftIdle")
		{
			animator->Play(L"pLeftMove");
		}
		else if (Input::GetKeyPress(eKeyCode::S))
		{
			if (bMove == false)
			{
				bMove = true;
			}
			Vector3 pos = tr->GetPosition();
			pos.y -= mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKeyUp(eKeyCode::S) && ani->AnimationName() == L"pRightMove")
		{
			animator->Play(L"pRightIdle");
			bMove = false;
		}
		else if (Input::GetKeyUp(eKeyCode::S) && ani->AnimationName() == L"pLeftMove")
		{
			animator->Play(L"pLeftIdle");
			bMove = false;
		}




		if (Input::GetKeyState(eKeyCode::A) == eKeyState::NONE &&
			Input::GetKeyState(eKeyCode::D) == eKeyState::NONE&&
			Input::GetKeyState(eKeyCode::W) == eKeyState::NONE&&
			Input::GetKeyState(eKeyCode::S) == eKeyState::NONE&& bMove == true && ani->AnimationName() == L"pLeftMove")
		{
			animator->Play(L"pLeftIdle");
			bMove = false;
		}
		if (Input::GetKeyState(eKeyCode::D) == eKeyState::NONE &&
			Input::GetKeyState(eKeyCode::A) == eKeyState::NONE &&
			Input::GetKeyState(eKeyCode::W) == eKeyState::NONE &&
			Input::GetKeyState(eKeyCode::S) == eKeyState::NONE && bMove == true && ani->AnimationName() == L"pRightMove")
		{
			animator->Play(L"pRightIdle");
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
		SetCurrentHP();
	}
	void PlayerScript::GameReset()
	{
		mMaxHP = 3;
		bHitImmune = false;
		bMove = false;
		immuneTime = 0.0f;
		bShield = true;
	}
	void PlayerScript::IdleAniStart()
	{
		bIdle = true;
	}
	void PlayerScript::MoveAniStart()
	{
		bIdle = false;
	}
	void PlayerScript::TakeDamage(int damage)
	{
		if (bHitImmune)
			return;

		if (bShield)
		{
			bShield = false;
			bHitImmune = true;
			SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->HolyShieldBreak();
			return;
		}

		SceneManager::GetPlayScene()->GetHpObjects()[mCurrentHP-1]->GetComponent<Animator>()->Play(L"heartArrest");
		mCurrentHP -= damage;
		bHitImmune = true;

		if (mCurrentHP <= 0)
			this->GetOwner()->Death();
	}
	void PlayerScript::StartSetting()
	{
		for (size_t i = 0; i < mMaxHP; i++)
		{
			SceneManager::GetPlayScene()->GetHpObjects()[i]->Life();
		}
	}
}