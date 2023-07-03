#pragma once
#include "yaGameObject.h"

namespace ya
{
	class UiBase : public GameObject
	{
	public:
		UiBase(eUIType type);
		virtual ~UiBase();

		//UI�� �ε� �Ǿ��� �� �Ҹ��� �ʱ�ȭ �Լ�
		virtual void Initalize();

		//UI�� Ȱ��ȭ �Ǹ� �Ҹ��� �Լ�
		void Active();
		//UI�� ��Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
		void InActive();

		//UI�� ������Ʈ �ɶ����� ȣ��Ǵ� �Լ�
		virtual void Update();

		void FixedUpdate() override;

		void Render() override;

		//UI�� ������� ȣ��Ǵ� �Լ�
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