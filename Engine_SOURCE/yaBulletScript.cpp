#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaWeapon.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaMonsterScript.h"
#include "yaSkillManager.h"
#include "yaPlayScene.h"

namespace ya
{
	BulletScript::BulletScript()
		:mSpeed(12.0f)
		,mSpeedMul(1.0f)
		,time(0.0f)
		,crashTime(0.0f)
		,mDamage(10)
		,mDamageMul(1.0f)
		,mScaleMul(1.0f)
		,mPenetrate(1)
		,mMaxPenetrate(1)
		,mBounceCnt(1)
		,direction{}
		,mTr(nullptr)
		,mWeapon(nullptr)
		,bCrash(false)
		,bThunder(false)
		,bAssassin(false)
		,bDieBullet(false)
		,bBounce(false)
		,bFreeze(false)
		, bCurse(false)
	{

	}
	BulletScript::~BulletScript()
	{

	}
	void BulletScript::Initalize()
	{

		mTr = GetOwner()->GetComponent<Transform>();

		Scene* playScene = SceneManager::GetPlaySCene();
		mWeapon = dynamic_cast<PlayScene*>(playScene)->GetWeapon();


		Animator* animator = GetOwner()->GetComponent<Animator>();
		//멤버함수 이기 떄문에 어떤 함수인지 풀네임으로 적어줘야 한다.
		animator->GetStartEvent(L"BulletAni") = std::bind(&BulletScript::Start, this);
		animator->GetCompleteEvent(L"BulletAni") = std::bind(&BulletScript::Action, this);
		animator->GetEndEvent(L"BulletAni") = std::bind(&BulletScript::End, this);

		GetOwner()->Death();
	}
	void BulletScript::Update()
	{
		time += Time::DeltaTime();
		Vector3 pos = mTr->GetPosition();

		if (time >= 3.0f)
		{
			Reset();
			GetOwner()->Death();
		}
		else if (bCrash)
		{
			crashTime += Time::DeltaTime();
			if (crashTime >= 0.01f)
			{
				Reset();
				this->GetOwner()->Death();
			}
		}

		if (bDieBullet)
		{
			pos += mTr->Right() * mSpeed * Time::DeltaTime();
		}
		else if(bBounce)
		{
			pos += mTr->Left() * (mSpeed * mSpeedMul) * Time::DeltaTime();
		}
		else
		{
			pos += mTr->Right() * (mSpeed * mSpeedMul) * Time::DeltaTime();
		}

		mTr->SetPosition(pos);

	}
	void BulletScript::Render()
	{

	}
	void BulletScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			Freeze(collider);

			if (collider->GetOwner()->GetScript<MonsterScript>()->GetcurseAtivate() == true)
			{
				int damage = std::round(mDamage * mDamageMul * 2) + 1;

				collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage);
			}
			else
			{
				Curse(collider);

				if (bDieBullet)
				{
					int damage = std::round(mDamage * mDamageMul * 0.1f) + 1;
					collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage);
					GetOwner()->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 1.0f));
				}
				else
				{
					int damage = std::round(mDamage * mDamageMul) + 1;
					collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage);
				}
				if (collider->GetOwner()->GetScript<MonsterScript>()->GetCurrentHP() <= (collider->GetOwner()->GetScript<MonsterScript>()->GetMaxHP() * 0.2f))
				{
					collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(9999);
				}
			}

			if (bThunder)
				SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->ThunderEnchant(collider->GetOwner()->GetComponent<Transform>()->GetPosition() + Vector3(0.0f,2.0f,0.0f));

			if (bBounceTrigger)
			{
				bBounce = true;
				mBounceCnt--;
				if (mBounceCnt <= 0)
					bBounceTrigger = false;
			}
			else
			{
				mPenetrate--;

				if (mPenetrate <= 0)
				{
					Animator* animator = GetOwner()->GetComponent<Animator>();
					animator->Play(L"BulletAni", false);
					animator->Start();
				}
			}
		}
	}
	void BulletScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void BulletScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void BulletScript::Freeze(Collider2D* collider)
	{
		if (bFreeze)
		{
			srand((unsigned int)std::time(NULL));

			int random = rand() & 100 + 1;

			if (random <= 35)
			{
				collider->GetOwner()->GetScript<MonsterScript>()->Freeze();
			}
		}
	}
	void BulletScript::Curse(Collider2D* collider)
	{
		if (bCurse)
		{
			srand((unsigned int)std::time(NULL));

			int random = rand() & 100;

			if (random <= 25)
			{
				collider->GetOwner()->GetScript<MonsterScript>()->Curse();
			}
		}
	}
	void BulletScript::Start()
	{

	}
	void BulletScript::Action()
	{

	}
	void BulletScript::End()
	{
		bCrash = true;
	}
	void BulletScript::Reset()
	{
		time = 0.0f;
		crashTime = 0.0f;
		mPenetrate = mMaxPenetrate;
		mTr->SetPosition(Vector3::Zero);
		mTr->SetRotation(Vector3::Zero);
		mTr->SetScale(Vector3(2.0f * mScaleMul, 2.0f * mScaleMul, 0.0f));
		Vector3 teset = mTr->GetScale();
		mBounceCnt = 1;
		bCrash = false;
		bThunder = false;
		bDieBullet = false;
		bBounce = false;
	}
	void BulletScript::GameReset()
	{
		time = 0.0f;
		crashTime = 0.0f;
		mDamageMul = 1.0f;
		mScaleMul = 1.0f;
		mSpeedMul = 1.0f;
		bCrash = false;
		bThunder = false;
		bDieBullet = false;
		bBounce = false;
		bBounceTrigger = false;
		bCurse = false;
	}
}