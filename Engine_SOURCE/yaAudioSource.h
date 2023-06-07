#pragma once
#include "yaComponent.h"
#include "yaAudioClip.h"

namespace ya
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void Play();
		void Stop();
		void SetLoop(bool loop);
		void Play(int number);
		void Stop(int number);
		void SetLoop(int number,bool loop);

		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }
		void SetClips(std::shared_ptr<AudioClip> clip) { mAudioClips.push_back(clip); }
		void SetClipsNum(int num) { clipsNumber = num; }

		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }
		std::shared_ptr<AudioClip> GetClips(int num) { return mAudioClips[num]; }
	private:
		int clipsNumber;

		std::shared_ptr<AudioClip> mAudioClip;
		std::vector<std::shared_ptr<AudioClip>> mAudioClips;
	};
}