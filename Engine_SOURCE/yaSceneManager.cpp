#include "yaSceneManager.h"
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

#include "yaPlayerMoveScript.h"

namespace ya
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mActiveScene = new Scene();
		mActiveScene->Initalize();

		// Grid Object
		GameObject* gridObject = new GameObject();
		Transform* gridTr = new Transform();
		gridObject->AddComponent(gridTr);
		MeshRenderer* gridMr = new MeshRenderer();
		gridObject->AddComponent(gridMr);
		gridObject->AddComponent(new GridScript());

		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));

		mActiveScene->AddGameObject(gridObject, eLayerType::None);

		// Main Camera Game Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraComp->RegisterCameraInRenderer();
		cameraObj->AddComponent(cameraComp);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		CameraScript* cameraScript = new CameraScript();
		cameraObj->AddComponent(cameraScript);

		mActiveScene->AddGameObject(cameraObj, eLayerType::Camera);
		


		//UI Camera GameObject
		GameObject* cameraUIObj = new GameObject();
		Transform* cameraUITr = new Transform();
		cameraUITr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraUIObj->AddComponent(cameraUITr);
		Camera* cameraUIComp = new Camera();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIObj->AddComponent(cameraUIComp);
		mActiveScene->AddGameObject(cameraUIObj, eLayerType::Camera);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI,true);


		// SMILE RECT
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		GameObject* obj = new GameObject();
		obj->SetName(L"SMAIL");
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.0f, 2.0f, 11.0f));
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		mateiral->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);

		mActiveScene->AddGameObject(obj, eLayerType::Player);
		
		// Light RECT
		GameObject* spriteObj = new GameObject();
		Transform* spriteTr = new Transform();
		spriteObj->SetName(L"LIGHT");
		spriteTr->SetPosition(Vector3(0.0f, -2.0f, 10.0f));
		spriteTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		spriteObj->AddComponent(spriteTr);

		SpriteRenderer* sr = new SpriteRenderer();
		spriteObj->AddComponent(sr);

		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");

		//Vector2 vec2(1.0f, 1.0f);
		//spriteMaterial->SetData(eGPUParam::Vector2, &vec2);

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);

		mActiveScene->AddGameObject(spriteObj, eLayerType::Monster);

	
		//PlayerTest
		GameObject* player = new GameObject();
		Transform* playerTr = new Transform();
		playerTr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		//playerTr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		playerTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		player->AddComponent(playerTr);
		PlayerMoveScript* pMoveScript = new PlayerMoveScript();
		player->AddComponent(pMoveScript);
		SpriteRenderer* pSr = new SpriteRenderer();
		player->AddComponent(pSr);

		std::shared_ptr<Material> playerMaterial = Resources::Find<Material>(L"PlayerMaterial");
		pSr->SetMaterial(playerMaterial);
		pSr->SetMesh(mesh);

		mActiveScene->AddGameObject(player, eLayerType::Player);

		//Player Child
		GameObject* child = new GameObject();
		Transform* childTr = new Transform();
		childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		child->AddComponent(childTr);
		childTr->SetParent(playerTr);
		SpriteRenderer* childSr = new SpriteRenderer();
		child->AddComponent(childSr);
		std::shared_ptr<Material> childMaterial = Resources::Find<Material>(L"PlayerMaterial");
		childSr->SetMaterial(childMaterial);
		childSr->SetMesh(mesh);

		mActiveScene->AddGameObject(child, eLayerType::Player);



		// HPBAR
		GameObject* hpBar = new GameObject();
		Transform* hpBarTr = new Transform();
		hpBarTr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		hpBarTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		hpBar->AddComponent(hpBarTr);
		SpriteRenderer* hpBarSr = new SpriteRenderer();
		hpBar->AddComponent(hpBarSr);
		 
		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpMaterial = Resources::Find<Material>(L"UIMaterial");
		hpBarSr->SetMesh(hpmesh);
		hpBarSr->SetMaterial(hpMaterial);
		mActiveScene->AddGameObject(hpBar, eLayerType::UI);


		mActiveScene->Initalize();
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Release()
	{
		delete mActiveScene;
		mActiveScene = nullptr;
	}
}