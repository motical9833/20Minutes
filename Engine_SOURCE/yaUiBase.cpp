#include "yaUiBase.h"
#include "yaResources.h"
#include "yaTexture.h"

namespace ya
{
	UiBase::UiBase(eUIType type)
		:mType(type)
		,mbFullScreen(false)
		,mbnable(false)
		,mParent(nullptr)
		,mPos(Vector3::Zero)
		,mSize(Vector3::One)
	{
	}
	UiBase::~UiBase()
	{
	}
	void UiBase::Initalize()
	{
		OnInit();
	}
	void UiBase::Active()
	{
		mbnable = true;
		OnActive();
	}
	void UiBase::InActive()
	{
		mbnable = false;
		OnInActive();
	}
	void UiBase::Update()
	{
		if (mbnable == false)
			return;

		OnUpdate();
	}
	void UiBase::FixedUpdate()
	{

	}
	void UiBase::Render()
	{
		GameObject::Render();
	}
	void UiBase::UIClear()
	{
		OnClear();
	}
}