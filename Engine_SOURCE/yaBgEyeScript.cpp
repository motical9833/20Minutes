#include "yaBgEyeScript.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"

namespace ya
{
	BgEyeScript::BgEyeScript()
		:mTime(0.0f)
		, mSpeed(0.05f)
		, bCycle(true)
		, bStop(false)
	{

	}
	BgEyeScript::~BgEyeScript()
	{

	}
	void BgEyeScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"T_EyeBlink");

		animator->GetCompleteEvent(L"bgEyeAnimation") = std::bind(&BgEyeScript::End, this);
	}
	void BgEyeScript::Update()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (pos.y > 0.1f)
		{
			mSpeed = -0.05f;
		}
		else if (pos.y < 0.0f)
		{
			mSpeed = 0.05f;
		}

		pos.y += mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);


		if (bStop && bCycle)
		{
			mTime += Time::DeltaTime();

			if (mTime >= 2)
			{
				mTime = 0;
				bStop = false;
				Animator* ani = GetOwner()->GetComponent<Animator>();
				ani->Start();
			}
		}
	}
	void BgEyeScript::FixedUpdate()
	{

	}
	void BgEyeScript::Render()
	{

	}
	void BgEyeScript::End()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Stop();
		bStop = true;
	}
	void BgEyeScript::Next()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		bCycle = false;
		ani->Play(L"bgEyeAniRunOnce", false);
	}
	void BgEyeScript::Reset()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		bCycle = true;
		ani->Play(L"bgEyeAnimation", false);
	}
}