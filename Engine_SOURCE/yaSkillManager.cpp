#include "yaSkillManager.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"

namespace ya
{
	SkillManager::SkillManager()
	{

	}
	SkillManager::~SkillManager()
	{

	}
	void SkillManager::Initalize()
	{

	}
	void SkillManager::Update()
	{

	}
	void SkillManager::FixedUpdate()
	{

	}
	void SkillManager::Render()
	{

	}
	void SkillManager::ThunderEnchant(Vector3 Enchantobject)
	{

		for (size_t i = 0; i < 20; i++)
		{
			if (SceneManager::GetPlayScene()->GetThunders()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetThunders()[i]->IsDead() == false)
				continue;

			SceneManager::GetPlayScene()->GetThunders()[i]->GetComponent<Transform>()->SetPosition(Enchantobject);
			SceneManager::GetPlayScene()->GetThunders()[i]->Life();
			break;
		}
	}
}