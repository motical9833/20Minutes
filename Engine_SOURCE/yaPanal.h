#pragma once
#include "yaUiBase.h"

namespace ya
{
	class Panal : public UiBase
	{
	public:
		Panal(eUIType type);
		~Panal();

		//virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		//virtual void OnRender() override;
		virtual void OnClear() override;

		void AddUIBase(UiBase uiBase);

	private:
		std::vector<UiBase*> mChilds;
	};
}