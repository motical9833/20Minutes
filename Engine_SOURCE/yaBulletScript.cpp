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
		:mSpeed(10.0f)
		,time(0.0f)
		,crashTime(0.0f)
		,mDamage(10)
		,direction{}
		,mTr(nullptr)
		,mWeapon(nullptr)
		,bCrash(false)
		,bThunder(false)
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


		pos += mTr->Right() * mSpeed * Time::DeltaTime();

		mTr->SetPosition(pos);

	}
	void BulletScript::Render()
	{

	}
	void BulletScript::OnCollisionEnter(Collider2D* collider)
	{
		int a = 0;

		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"BulletAni",false);
			animator->Start();


			collider->GetOwner()->GetScript<MonsterScript>()->Freeze();

			if (collider->GetOwner()->GetScript<MonsterScript>()->GetcurseAtivate() == true)
			{
				collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage * 2);
			}
			else
			{
				collider->GetOwner()->GetScript<MonsterScript>()->Curse();
				collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
			}

			if (bThunder)
				SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->ThunderEnchant(collider->GetOwner()->GetComponent<Transform>()->GetPosition() + Vector3(0.0f,2.0f,0.0f));
		}
	}
	void BulletScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void BulletScript::OnCollisionExit(Collider2D* collider)
	{

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
		mSpeed = 10.0f;
		mTr->SetPosition(Vector3::Zero);
		mTr->SetRotation(Vector3::Zero);
		mTr->SetScale(Vector3(2.0f, 2.0f, 0.0f));
		bCrash = false;
		bThunder = false;
	}
}