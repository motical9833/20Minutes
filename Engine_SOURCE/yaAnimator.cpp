#include "yaAnimator.h"


namespace ya
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{

	}
	Animator::~Animator()
	{
		for (auto anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}

		for (auto evt : mEvents)
		{
			delete evt.second;
			evt.second = nullptr;
		}
	}
	void Animator::Initalize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		Events* events
			= FindEvents(mActiveAnimation->AnimationName());
		if (mActiveAnimation->IsComplete())
		{
			if(events)
				events->mCompleteEvent();

			if(mbLoop)
			    mActiveAnimation->Reset();
		}

		UINT spriteIndex = mActiveAnimation->Update();
		if (spriteIndex != -1 && events->mEvents[spriteIndex].mEvent)
		{
			events->mEvents[spriteIndex].mEvent();
		}
	}
	void Animator::FixedUpdate()
	{
	}
	void Animator::Render()
	{
	}

	bool Animator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT spriteLegth, float duration)
	{
		if (atlas == nullptr)
			return false;

		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;

		animation = new Animation();
		animation->Create(name, atlas, leftTop
			, size, offset
			, spriteLegth, duration);


		mAnimations.insert(std::make_pair(name, animation));
		Events* events = new Events();
		events->mEvents.resize(spriteLegth);
		mEvents.insert(std::make_pair(name, events));
	}

	bool Animator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size, Vector2 offset, float atlasSizeX, float atlasSizeY, UINT spriteLegth, float duration)
	{
		if (atlas == nullptr)
			return false;

		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;

		animation = new Animation();
		animation->Create(name, atlas, leftTop, size,
			offset, atlasSizeX,atlasSizeY, spriteLegth, duration);


		mAnimations.insert(std::make_pair(name, animation));
		Events* events = new Events();
		events->mEvents.resize(spriteLegth);
		mEvents.insert(std::make_pair(name, events));
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	//void Animator::FindAnimationAndDuration(const std::wstring& name, float duration)
	//{
	//	std::map<std::wstring, Animation*>::iterator iter
	//		= mAnimations.find(name);

	//	//iter->second->
	//}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	void Animator::Play(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mActiveAnimation;
		Events* events = nullptr;
		if (prevAnimation)
			events = FindEvents(prevAnimation->AnimationName());

		if (events)
			events->mEndEvent();

		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mbLoop = loop;

		events = FindEvents(mActiveAnimation->AnimationName());

		if (events)
			events->mStartEvent();
	}

	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->BindShaderResource();
	}

	void Animator::Clear()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Clear();
	}

	void Animator::Stop()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Reset();
		mActiveAnimation->Idle();
	}

	void Animator::Start()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Reset();
		mActiveAnimation->Start();
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mEndEvent.mEvent;
	}
	std::function<void()>& Animator::GetEvent(const std::wstring& name, UINT index)
	{
		Events* events = FindEvents(name);

		return events->mEvents[index].mEvent;
	}
}
