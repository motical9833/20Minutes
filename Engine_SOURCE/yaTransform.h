#pragma once
#include "yaComponent.h"

using namespace ya::math;
namespace ya
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

		void SetParent(Transform* parent);
		Transform* GetParent() { return mParent; }
		void setChiled(Transform* chiled) { mChiled.push_back(chiled); }
		Transform* GetChiled(int num) { return mChiled[num]; }
		std::vector<Transform*> GetChileds() { return mChiled; }

		Vector3 GetPosition() { return mPosition; };
		Vector3 GetRotation() { return mRotation; };
		Vector3 GetScale() { return mScale; };

		void SetPosition(Vector3 position) { mPosition = position; };
		void SetRotation(Vector3 degree) { mRotation = degree; };
		void SetScale(Vector3 scale) { mScale = scale; };
		void SetFollowParents(bool bValue) { bFollowParents = bValue; }

		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Left() { return mLeft; }
		Vector3 Up() { return mUp; }

		

		void LeftMove();
		void RightMove();

		Matrix& GetWorldMatrix() { return mWorld; }

	private:
		Transform* mParent;
		std::vector<Transform*> mChiled;
		Vector3 mFoward;
		Vector3 mRight;
		Vector3 mLeft;
		Vector3 mUp;
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;
		Matrix mWorld;
		Matrix mNoScaleWorld;

		bool bFollowParents;
	};
}
