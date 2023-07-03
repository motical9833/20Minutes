#pragma once
#include "yaUiBase.h"

namespace ya
{
	class Button : public UiBase
	{
	public:
		Button(eUIType type);
		~Button();

		//virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		//virtual void OnRender() override;
		virtual void OnClear() override;

	private:
	};
}