#include "yaAudioSource.h"
#include "yaAudioClip.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaResources.h"

namespace ya
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, mAudioClip(nullptr)
		,mAudioClips{}
		, clipsNumber(0)
	{

	}

	AudioSource::~AudioSource()
	{

	}

	void AudioSource::Initalize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Foward();

		mAudioClip->Set3DAttributes(pos, foward);

		if(mAudioClips.size() != 0)
		mAudioClips[clipsNumber]->Set3DAttributes(pos, foward);
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play()
	{
		mAudioClip->Play();
	}
	void AudioSource::Stop()
	{
		mAudioClip->Stop();

	}
	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
	void AudioSource::Play(int number)
	{

		if (mAudioClips.size() > number)
			mAudioClips[number]->Play();
	}
	void AudioSource::Stop(int number)
	{
		if (mAudioClips.size() > number)
			mAudioClips[number]->Stop();
	}
	void AudioSource::SetLoop(int number, bool loop)
	{
		if (mAudioClips.size() > number)
			mAudioClips[number]->SetLoop(loop);
	}
}