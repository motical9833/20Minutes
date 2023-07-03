#pragma once
#include "yaEntity.h"
#include "yaUiBase.h"

using namespace ya::enums;
namespace ya
{
	class UIManager
	{
	public:
		static void Initalize();
		static void OnLoad(eUIType type);
		static void Update();
		static void Render();
		static void OnComplete(UiBase* addUI);
		static void OnFail();
		
		static void Push(eUIType type);
		static void Pop(eUIType type);

	private:
		static std::unordered_map<eUIType, UiBase*> mUIs;
		static std::queue<eUIType> mReQuestUIQueue;
		static std::stack<UiBase*> mUIBases;
		static UiBase* mCurrentData;

	};
}