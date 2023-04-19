#include "yaSkillManager.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "GaleScript.h"
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
	void SkillManager::GaleFire(Vector3 pos,Vector3 dir)
	{
		for (size_t i = 0; i < 20; i++)
		{
			if (SceneManager::GetPlayScene()->GetGale()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetGale()[i]->IsDead() == false)
				continue;

			SceneManager::GetPlayScene()->GetGale()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetGale()[i]->GetScript<GaleScript>()->SetDir(dir);
			SceneManager::GetPlayScene()->GetGale()[i]->Life();
			break;
		}
	}
}