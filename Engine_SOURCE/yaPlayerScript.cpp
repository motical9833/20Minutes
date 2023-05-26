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
		, characterNumber(0)
		, mCurrentHP(0)
		, mMaxHP(3)
		, dodgeRate(0)
		, immuneTime(0.0f)
		, hitBuffTime(0.0f)
		, regenerationTime(0.0f)
		, slowTime(0.0f)
		, mSpeed(6.0f)
		, mslowSpeed(2.5f)
		, mSpeedMul(1.0f)
		, mslowSPeedMul(1.0f)
		, mScaleMul(1.0f)
		, bShield(true)
		, bMove(false)
		, bIdle(false)
		, bHitImmune(false)
		, bPlayerHit(false)
		, bAngerPointTrigger(false)
		, bRegeneration(false)
		, bShooting(false)
		, bReflex(false)
	{
		
	}

	PlayerScript::PlayerScript(int characterNum, int maxHP)
		: Script()
		, characterNumber(characterNum)
		, mCurrentHP(0)
		, mMaxHP(maxHP)
		, dodgeRate(0)
		, immuneTime(0.0f)
		, hitBuffTime(0.0f)
		, regenerationTime(0.0f)
		, slowTime(0.0f)
		, mSpeed(6.0f)
		, mslowSpeed(2.5f)
		, mSpeedMul(1.0f)
		, mslowSPeedMul(1.0f)
		, mScaleMul(1.0f)
		, bShield(true)
		, bMove(false)
		, bIdle(false)
		, bHitImmune(false)
		, bPlayerHit(false)
		, bAngerPointTrigger(false)
		, bRegeneration(false)
		, bShooting(false)
		, bReflex(false)
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initalize()
	{
		switch (characterNumber)
		{
		case 0:
			ShanaAnimation();
			break;
		case 1:
			AbbyAnimation();
			break;
		case 2:
			DiamondAnimation();
			break;
		case 3:
			HinaAnimation();
			break;
		case 4:
			LilithAnimation();
			break;
		}
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
				immuneTime = 0.0f;
			}
		}

		if (bPlayerHit)
		{
			hitBuffTime += Time::DeltaTime();

			if (hitBuffTime >= 15)
			{
				bPlayerHit = false;
				hitBuffTime = 0.0f;
			}
		}

		if (bRegeneration && mMaxHP > mCurrentHP)
		{
			regenerationTime += Time::DeltaTime();

			if (regenerationTime >= 90)
			{
				mCurrentHP++;
				HPReset();
				regenerationTime = 0.0f;
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

		if (bShooting)
		{
			slowTime += Time::DeltaTime();

			if (slowTime >= 0.5f)
			{
				mSpeed = 6;
				slowTime = 0;
				bShooting = false;

				if (animator->GetActiveAnimation()->AnimationName() == L"pRightAttackMove")
					animator->Play(L"pRightMove");
				else if (animator->GetActiveAnimation()->AnimationName() == L"pLeftAttackMove")
					animator->Play(L"pLeftMove");
			}
		}

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


		if (Input::GetKeyPress(eKeyCode::D) && bShooting)
		{
			if (bMove == false || ani->AnimationName() == L"pRightMove")
			{
				bMove = true;
				animator->Play(L"pRightAttackMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.x += mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKeyPress(eKeyCode::D) && bShooting == false)
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

		if (Input::GetKeyPress(eKeyCode::A) && bShooting)
		{
			if (bMove == false || ani->AnimationName() == L"pLeftMove")
			{
				bMove = true;
				animator->Play(L"pLeftAttackMove");
			}

			Vector3 pos = tr->GetPosition();
			pos.x -= mSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKeyPress(eKeyCode::A) && bShooting == false)
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
		bPlayerHit = false;
		bAngerPointTrigger = false;
		bRegeneration = false;
		bShooting = false;
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
		if (Evasion() == true)
			return;

		if(bAngerPointTrigger)
			bPlayerHit = true;

		if (bHitImmune)
			return;

		if (bShield)
		{
			bShield = false;
			bHitImmune = true;
			SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->HolyShieldBreak();
			return;
		}

		SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->IntheWindReset();
		SceneManager::GetPlayScene()->GetHpObjects()[mCurrentHP-1]->GetComponent<Animator>()->Play(L"heartArrest");
		mCurrentHP -= damage;
		bHitImmune = true;

		if (mCurrentHP <= 0)
			this->GetOwner()->Death();
	}
	void PlayerScript::SetScaleMul(float value)
	{
		mScaleMul += value;
		Vector3 scale = GetOwner()->GetComponent<Transform>()->GetScale();
		Vector2 colliderScale = GetOwner()->GetComponent<Collider2D>()->GetSize();
		GetOwner()->GetComponent<Transform>()->SetScale(Vector3(scale.x * mScaleMul, scale.y * mScaleMul, scale.z));
		GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2(colliderScale.x * mScaleMul, colliderScale.y * mScaleMul));
	}
	void PlayerScript::SetScaleRed(float value)
	{
		mScaleMul -= value;
		Vector3 scale = GetOwner()->GetComponent<Transform>()->GetScale();
		Vector2 colliderScale = GetOwner()->GetComponent<Collider2D>()->GetSize();
		GetOwner()->GetComponent<Transform>()->SetScale(Vector3(scale.x * mScaleMul, scale.y * mScaleMul, scale.z));
		GetOwner()->GetComponent<Collider2D>()->SetSize(Vector2(colliderScale.x * mScaleMul, colliderScale.y * mScaleMul));
	}
	void PlayerScript::FireSlow()
	{
		mSpeed = mslowSpeed * mslowSPeedMul;
		slowTime = 0.0f;
		bShooting = true;
	}
	void PlayerScript::StartSetting()
	{
		for (size_t i = 0; i < mMaxHP; i++)
		{
			SceneManager::GetPlayScene()->GetHpObjects()[i]->Life();
		}
	}
	void PlayerScript::HPReset()
	{
		for (size_t i = 0; i < mMaxHP; i++)
		{
			SceneManager::GetPlayScene()->GetHpObjects()[i]->Life();
			SceneManager::GetPlayScene()->GetHpObjects()[i]->GetComponent<Animator>()->Play(L"heartArrest", false);
		}

		for (size_t i = 0; i < mCurrentHP; i++)
		{
			SceneManager::GetPlayScene()->GetHpObjects()[i]->GetComponent<Animator>()->Play(L"heartbeat", true);
		}
	}
	bool PlayerScript::Evasion()
	{
		srand((unsigned int)std::time(NULL));

		int random = rand() & 100 + 1;
		int rate = dodgeRate;

		if (bReflex)
			rate = dodgeRate + ((mSpeedMul * 100) - 100);

		if (random <= rate)
		{
			return true;
		}

		return false;
	}
	void PlayerScript::AbbyAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> textureAbby = Resources::Find<Texture>(L"Abby");


		animator->Create(L"pRightIdle", textureAbby, Vector2(0.0f, 0.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftIdle", textureAbby, Vector2(0.0f, 96.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightMove", textureAbby, Vector2(0.0f, 32.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 4, 0.2f);
		animator->Create(L"pLeftMove", textureAbby, Vector2(0.0f, 128.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 4, 0.2f);
		animator->Create(L"pRightAttackMove", textureAbby, Vector2(0.0f, 65.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 8, 0.2f);
		animator->Create(L"pLeftAttackMove", textureAbby, Vector2(0.0f, 161.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 8, 0.2f);

		animator->GetStartEvent(L"pRightIdle") = std::bind(&PlayerScript::IdleAniStart, this);
		animator->GetStartEvent(L"pLeftIdle") = std::bind(&PlayerScript::IdleAniStart, this);

		animator->GetStartEvent(L"pLeftMove") = std::bind(&PlayerScript::MoveAniStart, this);
		animator->GetStartEvent(L"pRightMove") = std::bind(&PlayerScript::MoveAniStart, this);

		animator->Play(L"pRightIdle", true);
	}
	void PlayerScript::DiamondAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> textureDiamond = Resources::Find<Texture>(L"Diamond");

		animator->Create(L"pRightIdle", textureDiamond, Vector2(0.0f, 0.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftIdle", textureDiamond, Vector2(0.0f, 96.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightMove", textureDiamond, Vector2(0.0f, 32.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);
		animator->Create(L"pLeftMove", textureDiamond, Vector2(0.0f, 128.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);
		animator->Create(L"pRightAttackMove", textureDiamond, Vector2(0.0f, 64.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftAttackMove", textureDiamond, Vector2(0.0f, 160.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);

		animator->GetStartEvent(L"pRightIdle") = std::bind(&PlayerScript::IdleAniStart, this);
		animator->GetStartEvent(L"pLeftIdle") = std::bind(&PlayerScript::IdleAniStart, this);

		animator->GetStartEvent(L"pLeftMove") = std::bind(&PlayerScript::MoveAniStart, this);
		animator->GetStartEvent(L"pRightMove") = std::bind(&PlayerScript::MoveAniStart, this);

		animator->Play(L"pRightIdle", true);
	}
	void PlayerScript::HinaAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> textureHina = Resources::Find<Texture>(L"Hina");

		animator->Create(L"pRightIdle", textureHina, Vector2(0.0f, -1.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftIdle", textureHina, Vector2(0.0f, 95.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightAttackMove", textureHina, Vector2(0.0f, 64.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftAttackMove", textureHina, Vector2(0.0f, 160.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightMove", textureHina, Vector2(0.0f, 32.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);
		animator->Create(L"pLeftMove", textureHina, Vector2(0.0f, 128.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);

		animator->GetStartEvent(L"pRightIdle") = std::bind(&PlayerScript::IdleAniStart, this);
		animator->GetStartEvent(L"pLeftIdle") = std::bind(&PlayerScript::IdleAniStart, this);

		animator->GetStartEvent(L"pLeftMove") = std::bind(&PlayerScript::MoveAniStart, this);
		animator->GetStartEvent(L"pRightMove") = std::bind(&PlayerScript::MoveAniStart, this);

		animator->Play(L"pRightIdle", true);
	}
	void PlayerScript::LilithAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> textureLilith = Resources::Find<Texture>(L"Lilith");

		animator->Create(L"pRightIdle", textureLilith, Vector2(0.0f, -1.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftIdle", textureLilith, Vector2(0.0f, 95.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightAttackMove", textureLilith, Vector2(0.0f, 64.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftAttackMove", textureLilith, Vector2(0.0f, 160.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightMove", textureLilith, Vector2(0.0f, 32.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);
		animator->Create(L"pLeftMove", textureLilith, Vector2(0.0f, 128.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);

		animator->GetStartEvent(L"pRightIdle") = std::bind(&PlayerScript::IdleAniStart, this);
		animator->GetStartEvent(L"pLeftIdle") = std::bind(&PlayerScript::IdleAniStart, this);

		animator->GetStartEvent(L"pLeftMove") = std::bind(&PlayerScript::MoveAniStart, this);
		animator->GetStartEvent(L"pRightMove") = std::bind(&PlayerScript::MoveAniStart, this);

		animator->Play(L"pRightIdle", true);
	}
	void PlayerScript::ShanaAnimation()
	{

		Animator* animator = GetOwner()->GetComponent<Animator>();
		//멤버함수 이기 떄문에 어떤 함수인지 풀네임으로 적어줘야 한다.
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"Shana");

		animator->Create(L"pRightIdle", texture, Vector2(0.0f, 0.5f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftIdle", texture, Vector2(0.0f, 95.5f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightAttackMove", texture, Vector2(0.0f, 65.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pLeftAttackMove", texture, Vector2(0.0f, 160.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pRightMove", texture, Vector2(0.0f, 33.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);
		animator->Create(L"pLeftMove", texture, Vector2(0.0f, 128.0f), Vector2(32.0f, 33.0f), Vector2::Zero, 4, 0.15f);

		animator->GetStartEvent(L"pRightIdle") = std::bind(&PlayerScript::IdleAniStart, this);
		animator->GetStartEvent(L"pLeftIdle") = std::bind(&PlayerScript::IdleAniStart, this);

		animator->GetStartEvent(L"pLeftMove") = std::bind(&PlayerScript::MoveAniStart, this);
		animator->GetStartEvent(L"pRightMove") = std::bind(&PlayerScript::MoveAniStart, this);

		animator->Play(L"pRightIdle", true);
	}
}