#include "yaUIManager.h"


namespace ya
{

	std::unordered_map<eUIType, UiBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mReQuestUIQueue;
	std::stack<UiBase*> UIManager::mUIBases;
	UiBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initalize()
	{
		// �޸� ui �Ҵ�

	}
	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UiBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}
	void UIManager::Update()
	{
		if (mReQuestUIQueue.size() > 0)
		{
			//UI �ε�
			eUIType requstUI = mReQuestUIQueue.front();
			mReQuestUIQueue.pop();

			OnLoad(requstUI);
		}
	}
	void UIManager::Render()
	{
		std::stack<UiBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Render();
			}
			uiBases.pop();
		}
	}
	void UIManager::OnComplete(UiBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initalize();
		addUI->Active();
		addUI->Update();

		if (addUI->GetIsFullScreen())
		{
			std::stack<UiBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UiBase* uiBase = uiBases.top();
				uiBases.pop();

				if (uiBase->GetIsFullScreen())
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
	}
	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}

	void UIManager::Push(eUIType type)
	{
		mReQuestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		std::stack<UiBase*> tempStack;

		UiBase* uiBase = nullptr;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			// pop �ϴ� ui�� ��üȭ�� �� ��쿡
			// ����  ui�߿� ��üȭ���� ���� �����
			//ui�� Ȱ��ȭ ������Ѵ�.
			
			if (uiBase->GetType() == type)
			{
				if (uiBase->GetIsFullScreen())
				{
					std::stack<UiBase*> uiBases = mUIBases;
					while (!uiBases.empty())
					{
						UiBase* uiBase = uiBases.top();
						uiBases.pop();

						if (uiBase->GetIsFullScreen())
						{
							uiBase->Active();
							break;
						}
					}
				}
				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase);
			}
		}

		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}
	}
}