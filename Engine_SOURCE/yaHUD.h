#pragma once
#include "yaUiBase.h"

namespace ya
{
	class HUD : public UiBase
	{
	public:
		HUD(eUIType type);
		~HUD();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		//virtual void OnRender() override;
		virtual void OnClear() override;

	private:

	};
}