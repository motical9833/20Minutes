#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mType(eLayerType::None)
		, mbDontDestroy(false)
		, bStop(false)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent(new Transform());
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			
			delete comp;
			comp = nullptr;
		}

		for (Component* scrComp : mScripts)
		{
			if (scrComp == nullptr)
				continue;

			delete scrComp;
			scrComp = nullptr;
		}
	}

	void GameObject::Initalize()
	{
		//for (Component* comp : mComponents)
		//{
		//	if (comp == nullptr)
		//		continue;

		//	comp->Initalize();
		//}

		//for (Component* script : mScripts)
		//{
		//	if (script == nullptr)
		//		continue;

		//	script->Initalize();
		//}
	}

	void GameObject::Update()
	{
		if (bStop)
			return;

		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->FixedUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			if (comp->GetOwner()->GetState() == Dead)
				continue;


			comp->Render();
		}

		for (Component* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Render();
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		eComponentType order = comp->GetOrder();

		if (order != eComponentType::Script)
		{
			mComponents[(UINT)order] = comp;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(dynamic_cast<Script*>(comp));
			comp->SetOwner(this);
		}
	}
}
