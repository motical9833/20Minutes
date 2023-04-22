#include "yaColliderCheckScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"

namespace ya
{
	using namespace std;
	ColliderCheckScript::ColliderCheckScript()
	{

	}
	ColliderCheckScript::~ColliderCheckScript()
	{

	}
	void ColliderCheckScript::Initalize()
	{

	}
	void ColliderCheckScript::Update()
	{
		Vector3 pos = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void ColliderCheckScript::Render()
	{

	}
	void ColliderCheckScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			for (Monster* monster  : monsters)
			{
				if (collider->GetID() == monster->GetComponent<Collider2D>()->GetID())
				{
					return;
				}
				else
				{
					continue;
				}
			}
			monsters.push_back((Monster*)collider->GetOwner());
		}
	}
	void ColliderCheckScript::OnCollisionStay(Collider2D* collider)
	{
		
	}
	void ColliderCheckScript::OnCollisionExit(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			list<Monster*>::iterator iter = monsters.begin();

			for (iter = monsters.begin(); iter != monsters.end(); iter++)
			{
				if (collider->GetID() == (*iter)->GetComponent<Collider2D>()->GetID())
				{
					monsters.erase(iter);
					return;
				}
				else
				{
					continue;
				}
			}
		}
	}
	void ColliderCheckScript::Start()
	{

	}
	void ColliderCheckScript::Action()
	{

	}
	void ColliderCheckScript::End()
	{

	}
	void ColliderCheckScript::Reset()
	{

	}
}