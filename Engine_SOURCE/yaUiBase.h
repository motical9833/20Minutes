#pragma once
#include "yaGameObject.h"

namespace ya
{
	class UiBase : public GameObject
	{
	public:
		UiBase(eUIType type);
		virtual ~UiBase();

		//UI가 로드 되었을 때 불리는 초기화 함수
		virtual void Initalize();

		//UI가 활성화 되면 불리는 함수
		void Active();
		//UI가 비활성화되면 불리는 함수
		void InActive();

		//UI가 업데이트 될때마다 호출되는 함수
		virtual void Update();

		void FixedUpdate() override;

		void Render() override;

		//UI가 사라질때 호출되는 함수
		void UIClear();

		eUIType GetType() { return mType; }
		eUIType SetType() { return mType; }
		bool GetIsFullScreen() { return mbFullScreen; }
		void SetIsFullScreen(bool enable) { mbFullScreen = enable; }
		void SetParent(UiBase* parent) { mParent = parent; }


	protected:
		//std::shared_ptr<Texture> mImage;
		Vector3 mPos;
		Vector3 mSize;


	private:
		virtual void OnInit() {};
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnUpdate() {};
		//virtual void OnRender() {};
		virtual void OnClear() {};

	private:
		UiBase* mParent;
		eUIType mType;
		bool mbFullScreen;
		bool mbnable;
	};
}