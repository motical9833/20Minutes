#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"

namespace ya
{
	class Animator : public Component
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> func)
				{
					mEvent = std::move(func);
				}
				void operator()()
				{
					if (mEvent)
						mEvent();
				}

				std::function<void()> mEvent;
			};

			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;

			std::vector<Event> mEvents;
		};

		Animator();
		~Animator();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLegth, float duration);

		bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas,
			Vector2 leftTop, Vector2 size, Vector2 offset, float atlasSizeX,
			float atlasSizeY, UINT spriteLegth, float duration);

		bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas,
			Vector2 leftTop, Vector2 size, Vector2 offset,int loopcnt,int loopnumber ,float atlasSizeX,
			float atlasSizeY, UINT spriteLegth, float duration);

		Animation* FindAnimation(const std::wstring& name);
		Animation* GetActiveAnimation() { return mActiveAnimation; }

		//void FindAnimationAndDuration(const std::wstring& name, float duration);
		Events* FindEvents(const std::wstring& name);
		void Play(const std::wstring& name, bool loop = true);
		void Play(const std::wstring& name,int loopNumber ,bool loop = true);
		void Binds();
		void Clear();
		void ResetStop();
		void Pause();
		void PlayAgain();
		void Start();

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		std::function<void()>& GetEvent(const std::wstring& name, UINT index);

	private:

		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		bool mbLoop;
		bool mbIdle;
	};
}