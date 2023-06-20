#include "yaGhostPetScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaSkillManager.h"
#include "yaPlayScene.h"
#include "yaAnimator.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaColliderCheckScript.h"
#include "yaAudioSource.h"

namespace ya
{
	GhostPetScript::GhostPetScript()
		:mSpeed(1.5f)
		, mAttackSpeedMul(1.0f)
		, mWidth(1.1f)
		, mHeight(1.1f)
		, mTime(0.0f)
		, mAttackTime(0.0f)
		, mDir{}
		, bVengefulGhost(false)
		, bTargetToMouse(false)
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

		if (bTargetToMouse && bVengefulGhost)
		{
			MousePosActtack(3);
		}
		else if(bTargetToMouse)
		{
			MousePosActtack(1);
		}
		else
		{
			Attack();
		}
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


		if (mAttackTime >= (3 * mAttackSpeedMul +1))
		{
			GetOwner()->GetComponent<AudioSource>()->Play();

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
	void GhostPetScript::MousePosActtack(int BulletCnt)
	{
		mAttackTime += Time::DeltaTime();

		if (mAttackTime >= (3 * mAttackSpeedMul + 1))
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 rot = SceneManager::GetPlayScene()->GetGhostPetRotObj()->GetComponent<Transform>()->GetRotation();

			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"ghostPetAttack", false);


			for (size_t i = 0; i < BulletCnt; i++)
			{
				if (bVengefulGhost)
					rot = SceneManager::GetPlayScene()->GetGhostPetRotObj()->GetComponent<Transform>()->GetRotation() + Vector3(0.0f, 0.0f, (-0.2f + (i * 0.2f)));;

				SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->GhostFireToMouse(pos, rot);
			}

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
	void GhostPetScript::GameReset()
	{
		mTime = 0.0f;
		mAttackTime = 0.0f;
		bVengefulGhost = false;
		bTargetToMouse = false;
	}
}