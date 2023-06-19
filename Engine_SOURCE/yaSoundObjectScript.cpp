#include "yaSoundObjectScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaAudioSource.h"
#include "yaTime.h"

namespace ya
{
	SoundObjectScript::SoundObjectScript()
		:mTime(0.0f)
		, pSceneCamera(nullptr)
	{

	}
	SoundObjectScript::~SoundObjectScript()
	{

	}
	void SoundObjectScript::Initalize()
	{
		pSceneCamera = SceneManager::GetPlayScene()->GetPlaySceneCamera();
	}
	void SoundObjectScript::Update()
	{
		mTime += Time::DeltaTime();
		GetOwner()->GetComponent<Transform>()->SetPosition(pSceneCamera->GetComponent<Transform>()->GetPosition());

		if (mTime >= 1.0f)
		{
			GetOwner()->Death();
			mTime = 0;
		}
	}
	void SoundObjectScript::ObjectOn()
	{
		GetOwner()->Life();
		GetOwner()->GetComponent<AudioSource>()->Play();
	}
}