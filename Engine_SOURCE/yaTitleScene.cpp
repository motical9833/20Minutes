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
#include "yaLight.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaAnimator.h"
#include "yaBgEyeScript.h"
#include "yalogoScript.h"
#include "yaLeavesScirpt.h"
#include "yaFaceTextureScript.h"

namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
		, leves{}
		, time(0.0f)
		, bLoadScene(false)
		, bgEye(nullptr)
		, logo(nullptr)
		, tSceneCamera(nullptr)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//{
		//	GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		//	directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
		//	Light* lightComp = directionalLight->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Point);
		//	lightComp->SetRadius(3.0f);
		//	lightComp->SetDiffuse(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		//}

		CreateCamera();
		//CreateLeavs();
		//CreateLogo();
		CreateBg();
		//CreateBgEye();
		//FirstUI();
		CreateSelectPanal();
		for (size_t i = 0; i < 5; i++)
		{
			const std::wstring name = L"Face_" + std::to_wstring(i) + L"Material";
			CreatePlayerFace(name, Vector3(14.0f, 1.0f, 9.9f), Vector3(5.0f, 6.0f, 1.0f));
		}

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			//StartUI();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			//FirstUI();
			//Start(1);
		}
		if(bLoadScene)
		{

		}
		if (time > 2)
		{
			bLoadScene = false;
			time = 0.0f;
			Start(1);
		}

		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			Vector3 pos = Input::GetMousePosition();

			glm::vec2 screenCoord(pos.x, pos.y);
			glm::mat4 viewProjectionMatrix(1.0f);

			int screenWidth = 1600;
			int screenHeight = 900;

			glm::vec2 cameraCoorcd = ScreenToCamera(screenCoord, viewProjectionMatrix, screenWidth, screenHeight);

			Vector3 mousePos = Vector3(cameraCoorcd.x, cameraCoorcd.y, 0.0f);

			int a = 0;
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
		mainCamera = tSceneCamera->GetComponent<Camera>();
	}
	void TitleScene::OnExit()
	{
	}
	void TitleScene::CreateCamera()
	{
		// Main Camera Game Object
		tSceneCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = tSceneCamera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		mainCamera = cameraComp;
		//renderer::cameras[0] = cameraComp;

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		GameObject* mouseObj = object::Instantiate<GameObject>(eLayerType::UI);
		mouseObj->SetName(L"MouseObj");
		mouseObj->DontDestroy(true);
	}
	void TitleScene::CreateLeavs()
	{
		//left
		GameObject* leftLeaves = object::Instantiate<GameObject>(eLayerType::UI);
		leftLeaves->SetLayerType(eLayerType::UI);
		leftLeaves->SetName(L"leftLeavs");
		Transform* leftLeavsTr = leftLeaves->GetComponent<Transform>();
		leftLeavsTr->SetPosition(Vector3(-11.0f, 1.0f, 9.9f));
		leftLeavsTr->SetScale(Vector3(5.0f, 11.0f, 1.0f));
		leftLeaves->AddComponent<LeavesScirpt>(Vector3(-6.0f, 1.0f, 9.9f), Vector3(-11.0f, 1.0f, 9.9f));
		leves.push_back(leftLeaves);

		SpriteRenderer* leftLevesR = leftLeaves->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> leftLeveMat = Resources::Find<Material>(L"leavsLeftMaterial");
		leftLevesR->SetMaterial(leftLeveMat);
		std::shared_ptr<Mesh> leftLevesmesh = Resources::Find<Mesh>(L"RectMesh");
		leftLevesR->SetMesh(leftLevesmesh);

		// right
		GameObject* rightLeaves = object::Instantiate<GameObject>(eLayerType::UI);
		rightLeaves->SetLayerType(eLayerType::UI);
		rightLeaves->SetName(L"RightLeavs");
		Transform* rightLeavsTr = rightLeaves->GetComponent<Transform>();
		rightLeavsTr->SetPosition(Vector3(13.0f, 1.0f, 9.9f));
		rightLeavsTr->SetScale(Vector3(5.0f, 11.0f, 1.0f));
		rightLeaves->AddComponent<LeavesScirpt>(Vector3(8.0f, 1.0f, 9.9f), Vector3(13.0f, 1.0f, 9.9f));
		leves.push_back(rightLeaves);

		SpriteRenderer* rightLevesR = rightLeaves->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> rightLeveMat = Resources::Find<Material>(L"leavsRightMaterial");
		rightLevesR->SetMaterial(rightLeveMat);
		std::shared_ptr<Mesh> rightLevesmesh = Resources::Find<Mesh>(L"RectMesh");
		rightLevesR->SetMesh(rightLevesmesh);
	}
	void TitleScene::CreateLogo()
	{
		// Logo
		logo = object::Instantiate<GameObject>(eLayerType::UI);
		logo->SetLayerType(eLayerType::UI);
		logo->SetName(L"Logo");
		Transform* logoTr = logo->GetComponent<Transform>();
		logoTr->SetPosition(Vector3(1.0f, 3.0f, 9.9f));
		logoTr->SetScale(Vector3(7.0f, 7.0f, 1.0f));
		logo->AddComponent<logoScript>();

		SpriteRenderer* logoRender = logo->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> logoMaterial = Resources::Find<Material>(L"LogoMaterial");
		logoRender->SetMaterial(logoMaterial);
		std::shared_ptr<Mesh> logoMesh = Resources::Find<Mesh>(L"RectMesh");
		logoRender->SetMesh(logoMesh);
	}
	void TitleScene::CreateBg()
	{
		//backgroundMaterial
		GameObject* bg = object::Instantiate<GameObject>(eLayerType::UI);
		bg->SetLayerType(eLayerType::UI);
		bg->SetName(L"bg");
		Transform* bgTr = bg->GetComponent<Transform>();
		bgTr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		bgTr->SetScale(Vector3(25.0f, 20.0f, 1.0f));

		SpriteRenderer* bgRender = bg->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bgMat = Resources::Find<Material>(L"backgroundMaterial");
		bgRender->SetMaterial(bgMat);
		std::shared_ptr<Mesh> bgMesh = Resources::Find<Mesh>(L"RectMesh");
		bgRender->SetMesh(bgMesh);
	}
	void TitleScene::CreateBgEye()
	{
		//EyeBlink
		bgEye = object::Instantiate<GameObject>(eLayerType::UI);
		bgEye->SetLayerType(eLayerType::UI);
		bgEye->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 9.9f));
		bgEye->GetComponent<Transform>()->SetScale(Vector3(7.0f, 5.0f, 1.0f));
		SpriteRenderer* bgEyeRender = bgEye->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bgEyeMat = Resources::Find<Material>(L"EyeBlinkMaterial");
		bgEyeRender->SetMaterial(bgEyeMat);
		std::shared_ptr<Mesh> bgEyeMesh = Resources::Find<Mesh>(L"RectMesh");
		bgEyeRender->SetMesh(bgEyeMesh);
		Animator* bgEyeAni = bgEye->AddComponent<Animator>();
		std::shared_ptr<Texture> bgEyeTexture = Resources::Find<Texture>(L"T_EyeBlink");
		bgEyeAni->Create(L"bgEyeAnimation", bgEyeTexture, Vector2(0.0f, 0.0f), Vector2(336.8f, 111.0f), Vector2::Zero, 336.0f, 224.0f, 5, 0.1f);
		bgEyeAni->Create(L"bgEyeAniRunOnce", bgEyeTexture, Vector2(0.0f, 0.0f), Vector2(336.8f, 111.0f), Vector2::Zero, 336.0f, 224.0f, 3, 0.1f);
		bgEyeAni->Play(L"bgEyeAnimation", false);
		bgEye->AddComponent<BgEyeScript>();
	}
	void TitleScene::CreateSelectPanal()
	{
		GameObject* upPanal = object::Instantiate<GameObject>(eLayerType::UI);
		upPanal->SetLayerType(eLayerType::UI);
		upPanal->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 5.15f, 9.9f));
		upPanal->GetComponent<Transform>()->SetScale(Vector3(20.0f, 2.0f, 1.0f));
		SpriteRenderer* upPanalRender = upPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> upPanalMat = Resources::Find<Material>(L"SelectScreenPanelUPMaterial");
		upPanalRender->SetMaterial(upPanalMat);
		std::shared_ptr<Mesh> upPanalMesh = Resources::Find<Mesh>(L"RectMesh");
		upPanalRender->SetMesh(upPanalMesh);

		GameObject* downPanal = object::Instantiate<GameObject>(eLayerType::UI);
		downPanal->SetLayerType(eLayerType::UI);
		downPanal->GetComponent<Transform>()->SetPosition(Vector3(1.0f, -3.2f, 9.9f));
		downPanal->GetComponent<Transform>()->SetScale(Vector3(20.0f, 2.0f, 1.0f));
		SpriteRenderer* downPanalRender = downPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> downPanalMat = Resources::Find<Material>(L"SelectScreenPanelDownMaterial");
		downPanalRender->SetMaterial(downPanalMat);
		std::shared_ptr<Mesh> downPanalMesh = Resources::Find<Mesh>(L"RectMesh");
		downPanalRender->SetMesh(downPanalMesh);
	}
	void TitleScene::CreatePlayerFace(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* faceObj = object::Instantiate<GameObject>(eLayerType::UI);
		faceObj->SetLayerType(eLayerType::UI);
		faceObj->GetComponent<Transform>()->SetPosition(pos);
		faceObj->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* faceRender = faceObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> faceMaterial = Resources::Find<Material>(key);
		faceRender->SetMaterial(faceMaterial);
		std::shared_ptr<Mesh> faceMesh = Resources::Find<Mesh>(L"RectMesh");
		faceRender->SetMesh(faceMesh);
		faceObj->AddComponent<FaceTextureScript>(Vector3(6.0f, 1.0f, 9.9f),Vector3(14.0f, 1.0f, 9.9f));

		faceObjs.push_back(faceObj);
	}
	void TitleScene::StartUI()
	{
		for (size_t i = 0; i < leves.size(); i++)
		{
			leves[i]->GetScript<LeavesScirpt>()->Next();
		}
		bgEye->GetScript<BgEyeScript>()->Next();
		logo->GetScript<logoScript>()->Next();
	}
	void TitleScene::SelectScreenUI()
	{
	}
	void TitleScene::FirstUI()
	{
		for (size_t i = 0; i < leves.size(); i++)
		{
			leves[i]->GetScript<LeavesScirpt>()->Reset();
		}
		bgEye->GetScript<BgEyeScript>()->Reset();
		logo->GetScript<logoScript>()->Reset();
	}
	glm::vec2 TitleScene::ScreenToCamera(const glm::vec2& screenCoord, const glm::mat4& viewProjectionMatrix, int screenWidth, int screenHeight)
	{
		glm::vec4 normalizedCoord
		(
			(screenCoord.x / screenWidth) * 2,
			(screenCoord.y / screenHeight) * 2,
			0.0f,
			1.0f
		);

		glm::vec4 cameraCoord = viewProjectionMatrix * normalizedCoord;

		return glm::vec2(cameraCoord);
	}
	void TitleScene::Start(int num)
	{
		leves[0]->GetComponent<Transform>()->SetPosition(Vector3(-6.0f, 1.0f, 9.9f));
		leves[1]->GetComponent<Transform>()->SetPosition(Vector3(8.0f, 1.0f, 9.9f));
		SceneManager::GetPlayScene()->ChoosePlayers(num);
		SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->StartSetting();
		SceneManager::LoadScene(eSceneType::Play);
	}
}
