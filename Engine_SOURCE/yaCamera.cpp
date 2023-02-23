#include "yaCamera.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaRenderer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaMaterial.h"
#include "yaBaseRenderer.h"

extern ya::Application application;

namespace ya
{
	// 행렬은 단위행렬로 초기화
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		:Component(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mAspectRatio(1.0f) //종횡비
		, mNear(1.0f)
		, mFar(1000.0f)
		, mScale(1.0f)
	{
		EnableLayerMasks();
	}
	Camera::~Camera()
	{

	}
	void Camera::Initalize()
	{
		//EnableLayerMasks();
		//RegisterCameraInRenderer();
	}
	void Camera::Update()
	{

	}
	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}
	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
	}
	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// Create Translate view Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos); //오브젝트가 앞으로 가면 카메라는 뒤로간다.
		//회전 정보

		Vector3 right = tr->Right();
		Vector3 up = tr->Up();
		Vector3 forward = tr->Forward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = forward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = forward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = forward.z;


		mView *= viewRotate;
	}
	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = 
				Matrix::CreatePerspectiveFieldOfViewLH
				(
					XM_PI / 6.0f, mAspectRatio, mNear, mFar
				);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNear, mFar);
		}
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}
	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();
		
		Scene* scene = SceneManager::GetActiveScene();
		
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				GameObjects gameObjects = layer.GetGameObjects();
		
				if (gameObjects.size() == 0)
					continue;
		
				for (GameObject* obj : gameObjects)
				{
					pushGameObjectToRenderingModes(obj);
				}
			}
		}
	}
	void Camera::renderOpaque()
	{
		for(GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}
	void Camera::renderCutout()
	{
		for (GameObject* obj : mCutoutGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}
	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}
	void Camera::pushGameObjectToRenderingModes(GameObject* gameobj)
	{
		BaseRenderer* renderer = gameobj->GetComponent<BaseRenderer>();

		if (renderer == nullptr)
			return;

		std::shared_ptr<Material> material = renderer->GetMaterial();
		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case ya::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameobj);
			break;
		case ya::graphics::eRenderingMode::cutOut:
			mCutoutGameObjects.push_back(gameobj);
			break;
		case ya::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameobj);
			break;
		case ya::graphics::eRenderingMode::End:
			break;
		default:
			break;
		}
	}
}