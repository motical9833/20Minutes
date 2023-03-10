#include "yaTitleScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaCollider2D.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaTime.h"

namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
		,objTr{}
		,time(0.0f)
		,bLoadScene(false)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		
		//renderer::cameras[0] = cameraComp;

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		
		 
		//left
		GameObject* leftLeaves = object::Instantiate<GameObject>(eLayerType::None);
		leftLeaves->SetName(L"leftLeavs");
		Transform* leftLeavsTr = leftLeaves->GetComponent<Transform>();
		objTr.push_back(leftLeavsTr);
		leftLeavsTr->SetPosition(Vector3(-6.0f, 1.0f, 9.9f));
		leftLeavsTr->SetScale(Vector3(5.0f, 11.0f, 1.0f));

		SpriteRenderer* leftLevesR = leftLeaves->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> leftLeveMat = Resources::Find<Material>(L"leavsLeftMaterial");
		leftLevesR->SetMaterial(leftLeveMat);
		std::shared_ptr<Mesh> leftLevesmesh = Resources::Find<Mesh>(L"RectMesh");
		leftLevesR->SetMesh(leftLevesmesh);

		// right
		GameObject* rightLeaves = object::Instantiate<GameObject>(eLayerType::None);
		rightLeaves->SetName(L"RightLeavs");
		Transform* rightLeavsTr = rightLeaves->GetComponent<Transform>();
		objTr.push_back(rightLeavsTr);
		rightLeavsTr->SetPosition(Vector3(8.0f, 1.0f, 9.9f));
		rightLeavsTr->SetScale(Vector3(5.0f, 11.0f, 1.0f));

		SpriteRenderer* rightLevesR = rightLeaves->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> rightLeveMat = Resources::Find<Material>(L"leavsRightMaterial");
		rightLevesR->SetMaterial(rightLeveMat);
		std::shared_ptr<Mesh> rightLevesmesh = Resources::Find<Mesh>(L"RectMesh");
		rightLevesR->SetMesh(rightLevesmesh);

		// Logo
		GameObject* logo = object::Instantiate<GameObject>(eLayerType::None);
		logo->SetName(L"Logo");
		Transform* logoTr = logo->GetComponent<Transform>();
		logoTr->SetPosition(Vector3(1.0f, 3.0f, 9.9f));
		logoTr->SetScale(Vector3(7.0f, 7.0f, 1.0f));

		SpriteRenderer* logoRender = logo->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> logoMaterial = Resources::Find<Material>(L"LogoMaterial");
		logoRender->SetMaterial(logoMaterial);
		std::shared_ptr<Mesh> logoMesh = Resources::Find<Mesh>(L"RectMesh");
		logoRender->SetMesh(logoMesh);

		//backgroundMaterial
		GameObject* bg = object::Instantiate<GameObject>(eLayerType::None);
		bg->SetName(L"bg");
		Transform* bgTr = bg->GetComponent<Transform>();
		bgTr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		bgTr->SetScale(Vector3(25.0f, 20.0f, 1.0f));

		SpriteRenderer* bgRender = bg->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bgMat = Resources::Find<Material>(L"backgroundMaterial");
		bgRender->SetMaterial(bgMat);
		std::shared_ptr<Mesh> bgMesh = Resources::Find<Mesh>(L"RectMesh");
		bgRender->SetMesh(bgMesh);

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			bLoadScene = true;
		}
		if(bLoadScene)
		{
			objTr[0]->LeftMove();
			objTr[1]->RightMove();
			time += Time::DeltaTime();
		}
		
		if (time > 2)
		{
			bLoadScene = false;
			time = 0.0f;
			objTr[0]->SetPosition(Vector3( - 6.0f, 1.0f, 9.9f));
			objTr[1]->SetPosition(Vector3(8.0f, 1.0f, 9.9f));
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}
