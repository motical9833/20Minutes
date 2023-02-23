#pragma once
#include "yaComponent.h"

namespace ya
{
	using namespace math;
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective,
			Orthographic,
		};

		__forceinline static Matrix& GetViewMatrix() { return View; }
		__forceinline static Matrix& GetProjectionMatrix() { return Projection; }

		Camera();
		virtual ~Camera();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
		
		void CreateViewMatrix();
		void CreateProjectionMatrix();
		void RegisterCameraInRenderer();

		//레이어 OnOff
		void TurnLayerMask(eLayerType layer, bool enable = true);
		void EnableLayerMasks() { mLayerMasks.set(); }
		void DisableLayerMasks() { mLayerMasks.reset(); }

		void SetProjectionType(eProjectionType type) { mType = type; }

		float GetScale() { return mScale; }

	private:
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void pushGameObjectToRenderingModes(GameObject* gameobj);

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;


		eProjectionType mType;
		float mAspectRatio;

		float mNear;
		float mFar;
		float mScale;

		// 배열처럼 사용하면서 메모리를 1비트씩 할당해주는 함수
		std::bitset<(UINT)eLayerType::End> mLayerMasks;

		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
	};
}