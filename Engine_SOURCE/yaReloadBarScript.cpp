#include "yaReloadBarScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"

namespace ya
{
	float mCurrentTime;
	float mTimeLimit;
	float mSpeed;
	ReloadBarScript::ReloadBarScript()
		:mCurrentTime(0.0f)
		,mTimeLimit(0.0f)
		,mSpeed(2.0f)
		,mSpeedMul(1.0f)
		, distance(1.0f)
		,killClip(0.0f)
	{

	}
	ReloadBarScript::~ReloadBarScript()
	{

	}
	void ReloadBarScript::Initalize()
	{

	}
	void ReloadBarScript::Update()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		pos.x += (mSpeed * (mSpeedMul + killClip)) * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);

		if (pos.x >= 1.0f)
		{
			for (size_t i = 0; i < 2; i++)
			{
				SceneManager::GetPlayScene()->GetReloadUI()[i]->Death();
				killClip = 0.0f;
			}
		}
	}
	void ReloadBarScript::FixedUpdate()
	{

	}
	void ReloadBarScript::Render()
	{

	}
	void ReloadBarScript::UIOn()
	{
		for (size_t i = 0; i < 2; i++)
		{
			SceneManager::GetPlayScene()->GetReloadUI()[i]->Life();
		}
	}
	void ReloadBarScript::UIOff()
	{
		for (size_t i = 0; i < 2; i++)
		{
			SceneManager::GetPlayScene()->GetReloadUI()[i]->Death();
		}
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(-1.0f, 0.6f, 9.0f));
	}
}