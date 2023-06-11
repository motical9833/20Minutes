#include "yaAnimation.h"
#include "yaTime.h"
#include "yaRenderer.h"

namespace ya
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
		, mbIdle(false)
		, loopCnt(0)
		, loopMaxCnt(0)
		, loopNumber(0)
	{

	}

	Animation::~Animation()
	{
	}

	UINT Animation::Update()
	{
		if (mbComplete)
			return -1;

		if (mbIdle)
			return mIndex;

		// 시간 체크
		mTime += Time::DeltaTime();

		// 누적 시간이 해당 프레임의 유지시간을 넘어서면 다음프레임으로 이동
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			//mTime = 0.0f;
			//++mIndex;

			////
			//if (mSpriteSheet.size() <= mIndex)
			//{
			//	mbComplete = true;
			//	mIndex = mSpriteSheet.size() - 1;
			//}

			//return mIndex;

			if (loopNumber != 0)
			{
				mTime = 0.0f;
				if (mIndex == loopNumber && loopCnt < loopMaxCnt)
				{
					--mIndex;
					loopCnt++;
					//
					if (mSpriteSheet.size() <= mIndex)
					{
						mbComplete = true;
						loopCnt = 0;
						mIndex = mSpriteSheet.size() - 1;
					}

					return mIndex;
				}
				else
				{
					mTime = 0.0f;
					++mIndex;

					//
					if (mSpriteSheet.size() <= mIndex)
					{
						mbComplete = true;
						loopCnt = 0;
						mIndex = mSpriteSheet.size() - 1;
					}

					return mIndex;
				}
			}
			else
			{
				mTime = 0.0f;
				++mIndex;

				//
				if (mSpriteSheet.size() <= mIndex)
				{
					mbComplete = true;
					loopCnt = 0;
					mIndex = mSpriteSheet.size() - 1;
				}

				return mIndex;
			}
		}

		return -1;
	}

	void Animation::FixedUpdate()
	{
	}

	void Animation::Render()
	{
	}

	void Animation::Create(const std::wstring& name
		, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT spriteLegth, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < spriteLegth; i++)
		{
			// API 와는 다르게 0~1 사이의 비율좌표로 위치를 표현해야한다.
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (size.x * (float)i)) / width
				, (leftTop.y) / height);
			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2(100.0f / width, 100.0f / height);

			mSpriteSheet.push_back(sprite);
		}
	}
	void Animation::Create(const std::wstring& name,
		std::shared_ptr<Texture> atlas, Vector2 leftTop, 
		Vector2 size, Vector2 offset, float atlasSizeX,
		float atlasSizeY, UINT spriteLegth, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < spriteLegth; i++)
		{
			// API 와는 다르게 0~1 사이의 비율좌표로 위치를 표현해야한다.
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (size.x * (float)i)) / width
				, (leftTop.y) / height);
			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2(atlasSizeX / width, atlasSizeY / height);

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size, Vector2 offset, int loopcnt, int loopnumber, float atlasSizeX, float atlasSizeY, UINT spriteLegth, float duration)
	{
		mAnimationName = name;

		mAtlas = atlas;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		loopMaxCnt = loopcnt;
		loopNumber = loopnumber;

		for (size_t i = 0; i < spriteLegth; i++)
		{
			// API 와는 다르게 0~1 사이의 비율좌표로 위치를 표현해야한다.
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (size.x * (float)i)) / width
				, (leftTop.y) / height);
			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2(atlasSizeX / width, atlasSizeY / height);

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::BindShaderResource()
	{
		mAtlas->BindShaderResource(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.size = mSpriteSheet[mIndex].size;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->Setdata(&info);
		cb->BindSRV(eShaderStage::PS);
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

	void Animation::Clear()
	{
		//Texture Clear
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::None;

		cb->Setdata(&info);
		cb->BindSRV(eShaderStage::PS);
	}

}
