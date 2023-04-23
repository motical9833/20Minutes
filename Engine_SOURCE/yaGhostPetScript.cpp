#include "yaGhostPetScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaSkillManager.h"
#include "yaPlayScene.h"
#include "yaAnimator.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaColliderCheckScript.h"
namespace ya
{
	GhostPetScript::GhostPetScript()
		:mSpeed(1.5f)
		, mWidth(1.1f)
		, mHeight(1.1f)
		, mTime(0.0f)
		, mAttackTime(0.0f)
		, mDir{}
	{

	}
	GhostPetScript::~GhostPetScript()
	{

	}
	void GhostPetScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"ghostPetAttack") = std::bind(&GhostPetScript::End, this);
	}
	void GhostPetScript::Update()
	{
		Circularmotion();

		Attack();
	}
	void GhostPetScript::Render()
	{

	}
	void GhostPetScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void GhostPetScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void GhostPetScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void GhostPetScript::Start()
	{

	}
	void GhostPetScript::Action()
	{

	}
	void GhostPetScript::End()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"ghostPetIdle", true);
	}
	void GhostPetScript::Reset()
	{

	}
	void GhostPetScript::Attack()
	{
		mAttackTime += Time::DeltaTime();


		if (mAttackTime >= 3)
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 a = tr->GetPosition();

			Vector3 b = SceneManager::GetPlayScene()->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsterPos();

			if (SceneManager::GetPlayScene()->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsters().size() == 0)
				return;

			Vector3 dir = b - a;

			Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

			double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2)); //피타고라스 R값

			Vector3 dirValue = Vector3(fabsDir.x / value, fabsDir.y / value, 0);
			
		    Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"ghostPetAttack",false);

		    SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->GhostFire(a, dirValue);
			mAttackTime = 0;
		}
	}
	
	void GhostPetScript::Circularmotion()
	{
		mTime += Time::DeltaTime() * mSpeed;

		float x = (std::cos(mTime) * mWidth) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float y = (std::sin(mTime) * mHeight) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().y;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
	}
}