#include "yaThunderBugScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaColliderCheckScript.h"
#include "yaMonsterScript.h"
#include "yaSkillManager.h"
#include "yaAnimator.h"
#include "yaInput.h"

namespace ya
{
	ThunderBugScript::ThunderBugScript(int cnt)
		:mSpeed(2.0f)
		, mFireSpeed(9.0f)
		, mWidth(0.8f)
		, mHeight(0.8f)
		, mTime(0.0f)
		, mAttackTime(0.0f)
		, value(cnt)
		, bAttack(false)
		, mDir{}
	{

	}
	ThunderBugScript::~ThunderBugScript()
	{

	}
	void ThunderBugScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"BugAttack") = std::bind(&ThunderBugScript::End, this);
	}
	void ThunderBugScript::Update()
	{
		Circularmotion();
		Attack();
	}
	void ThunderBugScript::Render()
	{

	}
	void ThunderBugScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void ThunderBugScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void ThunderBugScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void ThunderBugScript::Start()
	{

	}
	void ThunderBugScript::Action()
	{

	}
	void ThunderBugScript::End()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"BugIdle", true);
	}
	void ThunderBugScript::Reset()
	{

	}
	void ThunderBugScript::Circularmotion()
	{
		if (bAttack)
			return;

		mTime += Time::DeltaTime() * mSpeed;

		float x = (std::cos(mTime + value) * mWidth) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float y = (std::sin(mTime + value) * mHeight) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().y;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
	}
	void ThunderBugScript::LookPayer()
	{

	}
	void ThunderBugScript::Attack()
	{
		mAttackTime += Time::DeltaTime();


		if (mAttackTime >= float(1 + value/10))
		{
			if (SceneManager::GetPlayScene()->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsters().size() == 0)
				return;

			srand((unsigned int)std::time(NULL));

			int range = SceneManager::GetPlayScene()->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsters().size();


			int random = rand() & range -1;

			Vector3 b = SceneManager::GetPlayScene()->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsterPos();
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"BugAttack", false);

			SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->ThunderEnchant(b + Vector3(0.0f, 2.0f, 0.0f));

			mAttackTime = 0;
		}
	}
}