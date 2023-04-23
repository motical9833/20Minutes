#include "yaDragonPetScript.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaColliderCheckScript.h"
#include "yaSkillManager.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaAnimator.h"

namespace ya
{
	DragonPetScript::DragonPetScript()
		:mSpeed(1.0f)
		,mWidth(1.0f)
	    ,mHeight(1.0f)
		,mTime(0.0f)
		,mAttackTime(0.0f)
		,pscene{}
	{

	}
	DragonPetScript::~DragonPetScript()
	{

	}
	void DragonPetScript::Initalize()
	{
		pscene = SceneManager::GetPlayScene();

		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"DragonAttack") = std::bind(&DragonPetScript::End, this);
	}
	void DragonPetScript::Update()
	{
		Circularmotion();
		Attack();
	}
	void DragonPetScript::Render()
	{

	}
	void DragonPetScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void DragonPetScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void DragonPetScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void DragonPetScript::Start()
	{

	}
	void DragonPetScript::Action()
	{

	}
	void DragonPetScript::End()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"DragonIdle", true);
	}
	void DragonPetScript::Reset()
	{

	}
	void DragonPetScript::Attack()
	{
		mAttackTime += Time::DeltaTime();


		if (mAttackTime >= 3)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 a = tr->GetPosition();

			Vector3 b = pscene->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsterPos();

			if (pscene->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsters().size() == 0)
				return;


			Vector3 dir = b - a;  // dir의 xy는 x는 임의로a y는 임의로 b라고 정함

			Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

			double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2)); //피타고라스 R값

			Vector3 dirValue = Vector3(fabsDir.x/value, fabsDir.y/value, 0);

			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"DragonAttack", false);

			SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->GhostFire(a, dirValue);
			mAttackTime = 0;
		}
	}
	void DragonPetScript::Circularmotion()
	{
		mTime += Time::DeltaTime() * mSpeed;

		float x = (std::cos(mTime) * mWidth) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float y = (std::sin(mTime) * mHeight) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().y;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
	}
}