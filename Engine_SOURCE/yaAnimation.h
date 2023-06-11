#pragma once
#include "yaEntity.h"
#include "yaTexture.h"

using namespace ya::math;
using namespace ya::graphics;
namespace ya
{
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// ���� ��� ��ǥ
			Vector2 size;		// ������ܺ��� �߶� ���� ������ �ȼ� ����
			Vector2 offset;		// ������ ��ġ �����ϱ����� ��ǥ
			Vector2 atlasSize;  // �ؽ�ó �̹����� ũ��
			float duration;		// �����Ӱ��� �ð� ����
			//std::function<void()> action; //�ش� ��������Ʈ(�ε���) ���� ����� �̺�Ʈ �Լ�


			Sprite()
				: leftTop(0.0f, 0.0f)
				, size(0.0f, 0.0f)
				, offset(0.0f, 0.0f)
				, atlasSize(0.0f)
				, duration(0.1f)
			{

			}
		};

		Animation();
		~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLegth, float duration);

		void Create(const std::wstring& name,
			std::shared_ptr<Texture> atlas, Vector2 leftTop,
			Vector2 size, Vector2 offset, float atlasSizeX,
			float atlasSizeY, UINT spriteLegth, float duration);

		void Create(const std::wstring& name,
			std::shared_ptr<Texture> atlas, Vector2 leftTop,
			Vector2 size, Vector2 offset, int loopcnt, int loopnumber, float atlasSizeX,
			float atlasSizeY, UINT spriteLegth, float duration);


		void BindShaderResource();
		void Reset();
		void Clear();

		bool IsComplete() { return mbComplete; }
		std::wstring& AnimationName() { return mAnimationName; }
		void Idle() { mbIdle = true; }
		void Start() { mbIdle = false; }
		bool GetIdleState() { return mbIdle; }
	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		int loopCnt;
		int loopMaxCnt;
		int loopNumber;
		bool mbComplete;
		bool mbIdle;
	};
}
