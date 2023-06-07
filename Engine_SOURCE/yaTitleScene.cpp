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
#include "yaSelectPanalScript.h"
#include "yaBubbleUIScript.h"
#include "yaUIPanalMoveScript.h"
#include "yaTitleUIManager.h"
#include "yaCursorUIScript.h"
#include "yaAudioListener.h"
#include "yaAudioSource.h"


#define SHANA 0
#define ABBY 1
#define DIAMOND 2
#define HINA 3
#define LILITH 4

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
		, selectCharNum(0)
		, selectWeaponNum(0)
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

		GameObject* cursorObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		SpriteRenderer* cursorRender = cursorObject->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> cursorMat = Resources::Find<Material>(L"CursorMaterial");
		cursorRender->SetMaterial(cursorMat);
		std::shared_ptr<Mesh> cursorMesh = Resources::Find<Mesh>(L"RectMesh");
		cursorRender->SetMesh(cursorMesh);
		cursorObject->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cursorObject->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.0f));
		cursorObject->AddComponent<CursorUIScript>();

		//{
		//	GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
		//	directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
		//	Light* lightComp = directionalLight->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Point);
		//	lightComp->SetRadius(3.0f);
		//	lightComp->SetDiffuse(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		//}

		faceParent = object::Instantiate<GameObject>(eLayerType::UI);
		faceParent->SetLayerType(eLayerType::UI);
		faceParent->GetComponent<Transform>()->SetPosition(Vector3(17.0f, 1.0f, 9.9f));
		faceParent->AddComponent<UIPanalMoveScript>(Vector3(5.0f, 1.0f, 9.9f));

		CreateUIPanal(Vector3(1.0f, -0.5f, 9.9f));
		CreateUIPanal(Vector3(1.0f, -1.2f, 9.9f));
		CreateUIPanal(Vector3(1.0f, -1.9f, 9.9f));
		CreateUIPanal(Vector3(1.0f, -2.6f, 9.9f));
		CreateUIManager();
		CreateCamera();
		CreateLeavs();
		CreateLogo();
		CreateBg();
		CreateBgEye();
		CreateFaceImg();
		FirstUI();
		CreateBubblePanal();
		CreateBubbleUI();
		CreateLockObjet();
		CreateSelectPanal();
		CreatePanal();
		CreateSelectCharacter();
		CreateWeaponImg();
		Scene::Initalize();
	}
	void TitleScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N))
		{
			WeaponSelectUI();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			CharacterSelectUI();
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

			uiManager->GetScript<TitleUIManager>()->SetMousePos(UIMousePos());
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
		tUICamera->GetComponent<AudioSource>()->Play();
	}
	void TitleScene::OnExit()	
	{
		tUICamera->GetComponent<AudioSource>()->Stop();
	}
	void TitleScene::CreateCamera()
	{
		Resources::Load<AudioClip>(L"TitleBGM", L"..\\Resources\\Sound\\PrettyDungeonLOOP.wav");

		// Main Camera Game Object
		tSceneCamera = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = tSceneCamera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		tSceneCamera->AddComponent<AudioListener>();

		mainCamera = cameraComp;
		//renderer::cameras[0] = cameraComp;
		
		GameObject* soundObj = object::Instantiate<GameObject>(eLayerType::None);

		// UI Camera
		tUICamera = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = tUICamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		AudioSource* audio = tUICamera->AddComponent<AudioSource>();
		audio->SetClip(Resources::Find<AudioClip>(L"TitleBGM"));
		audio->SetLoop(true);
		audio->Play();



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
	void TitleScene::CreateUIManager()
	{
		uiManager = object::Instantiate<GameObject>(eLayerType::UI);
		uiManager->AddComponent<TitleUIManager>();
	}
	void TitleScene::CreateSelectPanal()
	{
		GameObject* upPanal = object::Instantiate<GameObject>(eLayerType::UI);
		upPanal->SetLayerType(eLayerType::UI);
		upPanal->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 10.15f, 9.9f));
		upPanal->GetComponent<Transform>()->SetScale(Vector3(20.0f, 2.0f, 1.0f));
		SpriteRenderer* upPanalRender = upPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> upPanalMat = Resources::Find<Material>(L"SelectScreenPanelUPMaterial");
		upPanalRender->SetMaterial(upPanalMat);
		std::shared_ptr<Mesh> upPanalMesh = Resources::Find<Mesh>(L"RectMesh");
		upPanalRender->SetMesh(upPanalMesh);
		upPanal->AddComponent<SelectPanalScript>(Vector3(1.0f, 5.15f, 9.9f),Vector3(1.0f, 10.15f, 9.9f));
		selectPanals.push_back(upPanal);

		GameObject* downPanal = object::Instantiate<GameObject>(eLayerType::UI);
		downPanal->SetLayerType(eLayerType::UI);
		downPanal->GetComponent<Transform>()->SetPosition(Vector3(1.0f, -8.2f, 9.9f));
		downPanal->GetComponent<Transform>()->SetScale(Vector3(20.0f, 2.0f, 1.0f));
		SpriteRenderer* downPanalRender = downPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> downPanalMat = Resources::Find<Material>(L"SelectScreenPanelDownMaterial");
		downPanalRender->SetMaterial(downPanalMat);
		std::shared_ptr<Mesh> downPanalMesh = Resources::Find<Mesh>(L"RectMesh");
		downPanalRender->SetMesh(downPanalMesh);
		downPanal->AddComponent<SelectPanalScript>(Vector3(1.0f, -3.2f, 9.9f), Vector3(1.0f, -8.2f, 9.9f));
		selectPanals.push_back(downPanal);
	}
	void TitleScene::CreatePlayerFace(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* faceObj = object::Instantiate<GameObject>(eLayerType::UI);
		faceObj->SetLayerType(eLayerType::UI);
		faceObj->GetComponent<Transform>()->SetParent(faceParent->GetComponent<Transform>());
		faceObj->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		faceObj->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* faceRender = faceObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> faceMaterial = Resources::Find<Material>(key);
		faceRender->SetMaterial(faceMaterial);
		std::shared_ptr<Mesh> faceMesh = Resources::Find<Mesh>(L"RectMesh");
		faceRender->SetMesh(faceMesh);
		faceObj->AddComponent<FaceTextureScript>();
		faceObj->Death();
		faceObjs.push_back(faceObj);
	}
	void TitleScene::CreateFaceImg()
	{
		for (size_t i = 0; i < 10; i++)
		{
			const std::wstring name = L"Face_" + std::to_wstring(i) + L"Material";
			CreatePlayerFace(name, Vector3(17.0f, 1.0f, 9.9f), Vector3(5.0f, 6.0f, 1.0f));
		}
		faceObjs[0]->Life();
	}
	void TitleScene::CreateWeaponUI(const std::wstring& key, GameObject* parent, Vector3 pos)
	{
		GameObject* faceObj = object::Instantiate<GameObject>(eLayerType::UI);
		faceObj->SetLayerType(eLayerType::UI);
		faceObj->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		faceObj->GetComponent<Transform>()->SetPosition(pos);
		faceObj->GetComponent<Transform>()->SetScale(Vector3(0.5f,0.5f,1.0f));
		SpriteRenderer* faceRender = faceObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> faceMaterial = Resources::Find<Material>(key);
		faceRender->SetMaterial(faceMaterial);
		std::shared_ptr<Mesh> faceMesh = Resources::Find<Mesh>(L"RectMesh");
		faceRender->SetMesh(faceMesh);
	}
	void TitleScene::CreateWeaponImg()
	{
		for (size_t i = 0; i < 6; i++)
		{
			const std::wstring name = L"Weapon_" + std::to_wstring(i) + L"Material";
			CreateWeaponUI(name, bubbleParents[1], Vector3(-6.0f + (1.5f * i), 0.0f, 0.0f));
		}
		for (size_t i = 0; i < 2; i++)
		{
			const std::wstring name = L"Weapon_" + std::to_wstring(i + 6) + L"Material";
			CreateWeaponUI(name, bubbleParents[1], Vector3(-6.0f + (1.5f * i), -1.5f, 0.0f));
		}
	}
	void TitleScene::CreateBubble(std::vector<GameObject*>& keepArray,Vector3 pos)
	{
		GameObject* pbubble = object::Instantiate<GameObject>(eLayerType::UI);
		pbubble->SetLayerType(eLayerType::UI);
		pbubble->GetComponent<Transform>()->SetParent(bubbleParents[0]->GetComponent<Transform>());
		pbubble->GetComponent<Transform>()->SetPosition(pos);
		pbubble->GetComponent<Transform>()->SetScale(Vector3(2.0f,2.0f,1.0f));
		SpriteRenderer* render = pbubble->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SelectorBubbleMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		Animator* animator = pbubble->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"T_SelectorBubble");
		animator->Create(L"BubbleAni", texture, Vector2(0.0f,0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 2, 0.1f);
		animator->Play(L"BubbleAni", false);
		animator->Stop();

		keepArray.push_back(pbubble);
	}
	void TitleScene::CreateBubble(std::vector<GameObject*>& keepArray,GameObject* parent, Vector3 pos)
	{
		GameObject* pbubble = object::Instantiate<GameObject>(eLayerType::UI);
		pbubble->SetLayerType(eLayerType::UI);
		pbubble->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		pbubble->GetComponent<Transform>()->SetPosition(pos);
		pbubble->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		SpriteRenderer* render = pbubble->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SelectorBubbleMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		Animator* animator = pbubble->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"T_SelectorBubble");
		animator->Create(L"BubbleAni", texture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 2, 0.1f);
		animator->Play(L"BubbleAni", false);
		animator->Stop();

		keepArray.push_back(pbubble);
	}
	void TitleScene::CreateBubbleUI()
	{
		for (size_t i = 0; i < 6; i++)
		{
			CreateBubble(playerBubbles,bubbleParents[0], Vector3(-6.0f + (1.5f * i), 0.0f, 0.0f));
		}
		for (size_t i = 0; i < 4; i++)
		{
			CreateBubble(playerBubbles, bubbleParents[0],Vector3(-6.0f + (1.5f * i), -1.5f, 0.0f));
		}
		for (size_t i = 0; i < 6; i++)
		{
			CreateBubble(weaponBubbles, bubbleParents[1],Vector3(-6.0f + (1.5f * i), 0.0f, 0.0f));
		}
		for (size_t i = 0; i < 2; i++)
		{
			CreateBubble(weaponBubbles, bubbleParents[1],Vector3(-6.0f + (1.5f * i), -1.5f, 0.0f));
		}
	}
	void TitleScene::CreateLock(GameObject* parent, Vector3 pos)
	{
		GameObject* lock = object::Instantiate<GameObject>(eLayerType::UI);
		lock->SetLayerType(eLayerType::UI);
		lock->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		lock->GetComponent<Transform>()->SetPosition(pos);
		lock->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.4f, 1.0f));
		SpriteRenderer* render = lock->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"UILockMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);
		lockObjs.push_back(lock);
	}
	void TitleScene::CreateLockObjet()
	{
		for (size_t i = 0; i < 6; i++)
		{
			CreateLock(bubbleParents[0], Vector3(-6.0f + (1.5f * i), 0.0f, -0.01f));
		}
		for (size_t i = 0; i < 4; i++)
		{
			CreateLock(bubbleParents[0], Vector3(-6.0f + (1.5f * i), -1.5f, -0.01f));
		}
		for (size_t i = 0; i < 6; i++)
		{
			CreateLock(bubbleParents[1], Vector3(-6.0f + (1.5f * i), 0.0f, -0.01f));
		}
		for (size_t i = 0; i < 2; i++)
		{
			CreateLock(bubbleParents[1], Vector3(-6.0f + (1.5f * i), -1.5f, -0.01f));
		}
		lockObjs[0]->Death();
		lockObjs[10]->Death();
	}
	void TitleScene::CreateCharacterImg(const std::wstring& key, Vector3 pos)
	{
		GameObject* character = object::Instantiate<GameObject>(eLayerType::UI);
		character->SetLayerType(eLayerType::UI);
		character->GetComponent<Transform>()->SetParent(bubbleParents[0]->GetComponent<Transform>());
		character->GetComponent<Transform>()->SetPosition(pos);
		character->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		SpriteRenderer* render = character->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"PlayerMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		Animator* animator = character->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(key);

		animator->Create(key + L"Ani", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 31.5f), Vector2::Zero, 6, 0.2f);
		animator->Play(key + L"Ani", true);

		uiPlayers.push_back(character);
	}
	void TitleScene::CreateSelectCharacter()
	{
		for (size_t i = 0; i < 6; i++)
		{
			const std::wstring name = L"Player_" + std::to_wstring(i);
			CreateCharacterImg(name, Vector3(-6.0f + (1.5f * i), 0.0f, 0.0f));
		}
		for (size_t i = 0; i < 4; i++)
		{
			const std::wstring name = L"Player_" + std::to_wstring(i + 6);
			CreateCharacterImg(name, Vector3(-6.0f + (1.5f * i), -1.5f, 0.0f));
		}
		uiPlayers[0]->GetComponent<Transform>()->SetPosition(Vector3(-6.1f, 0.0f, 0.0f));
	}
	void TitleScene::CreatePanal()
	{
		CreateUIPanal(L"PanalMaterial", selectPanals[0], Vector3(-7.0f, 0.7f, 0.0f));
		CreateUIPanal(L"PanalMaterial", selectPanals[0], Vector3(-3.5f, 0.7f, 0.0f));
		CreateUIPanal(L"PanalMaterial", selectPanals[1], Vector3(-7.0f, -0.2f, 0.0f), Vector3(-3.0f, 1.0f, 1.0f));
		CreateUIPanal(L"PanalMaterial", selectPanals[1], Vector3(-3.5f, -0.2f, 0.0f), Vector3(-3.0f, 1.0f, 1.0f));
	}
	void TitleScene::CreateUIPanal(Vector3 pos)
	{
		GameObject* panal = object::Instantiate<GameObject>(eLayerType::UI);
		panal->SetLayerType(eLayerType::UI);
		panal->GetComponent<Transform>()->SetPosition(pos);
		panal->GetComponent<Transform>()->SetScale(Vector3(3.0f, 0.5f, 1.0f));
		SpriteRenderer* render = panal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"PanalMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);
		mainUIbutterns.push_back(panal);
	}
	void TitleScene::CreateUIPanal(const std::wstring& key, GameObject* parent,Vector3 pos)
	{
		GameObject* panal = object::Instantiate<GameObject>(eLayerType::UI);
		panal->SetLayerType(eLayerType::UI);
		panal->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		panal->GetComponent<Transform>()->SetPosition(pos);
		panal->GetComponent<Transform>()->SetScale(Vector3(3.0f, 1.0f, 1.0f));
		SpriteRenderer* render = panal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(key);
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);
	}
	void TitleScene::CreateUIPanal(const std::wstring& key, GameObject* parent, Vector3 pos, Vector3 scale)
	{
		GameObject* panal = object::Instantiate<GameObject>(eLayerType::UI);
		panal->SetLayerType(eLayerType::UI);
		panal->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		panal->GetComponent<Transform>()->SetPosition(pos);
		panal->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* render = panal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(key);
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);
	}
	void TitleScene::CreateBubblePanal()
	{
		int a = 1;
		for (size_t i = 0; i < 2; i++)
		{
			if (i == 1)
				a = -2;
			else
				a = 1;

			GameObject* panal = object::Instantiate<GameObject>(eLayerType::UI);
			panal->SetLayerType(eLayerType::UI);
			panal->GetComponent<Transform>()->SetPosition(Vector3(-10.0f * a, 0.0f, 9.0f));
			panal->AddComponent<UIPanalMoveScript>(Vector3(0.0f, 0.0f, 9.0f));
			bubbleParents.push_back(panal);
		}
	}
	void TitleScene::StartUI()
	{
		for (size_t i = 0; i < leves.size(); i++)
		{
			leves[i]->GetScript<LeavesScirpt>()->Next();
		}
		bgEye->GetScript<BgEyeScript>()->Next();
		logo->GetScript<logoScript>()->Next();
		
		faceParent->GetScript<UIPanalMoveScript>()->Next();

		for (size_t i = 0; i < selectPanals.size(); i++)
		{
			selectPanals[i]->GetScript<SelectPanalScript>()->Next();
		}
		for (size_t i = 0; i < mainUIbutterns.size(); i++)
		{
			mainUIbutterns[i]->Death();
		}
		bubbleParents[0]->GetScript<UIPanalMoveScript>()->Next();
	}
	void TitleScene::WeaponSelectUI()
	{
		bubbleParents[0]->GetScript<UIPanalMoveScript>()->Back();
		bubbleParents[1]->GetScript<UIPanalMoveScript>()->Next();
	}
	void TitleScene::CharacterSelectUI()
	{
		bubbleParents[0]->GetScript<UIPanalMoveScript>()->Next();
		bubbleParents[1]->GetScript<UIPanalMoveScript>()->Back();
	}
	void TitleScene::ClickCharacter(int num)
	{
		for (size_t i = 0; i < faceObjs.size(); i++)
		{
			faceObjs[i]->Death();
		}
		faceObjs[num]->Life();

		if (num == 1)
		{
			selectCharNum = DIAMOND;
		}
		else if (num == 3)
		{
			selectCharNum = HINA;
		}
		else if (num == 5)
		{
			selectCharNum = LILITH;
		}
		else if (num == 6)
		{
			selectCharNum = ABBY;
		}
		else
		{
			selectCharNum = SHANA;
		}
	}
	void TitleScene::ClickWeapon(int num)
	{
		selectWeaponNum = num;
	}
	void TitleScene::SelectScreenUI()
	{
		for (size_t i = 0; i < leves.size(); i++)
		{
			leves[i]->GetScript<LeavesScirpt>()->Back();
		}
		bgEye->GetScript<BgEyeScript>()->Reset();
		logo->GetScript<logoScript>()->Reset();

		faceParent->GetScript<UIPanalMoveScript>()->Back();
		for (size_t i = 0; i < selectPanals.size(); i++)
		{
			selectPanals[i]->GetScript<SelectPanalScript>()->Back();
		}
		for (size_t i = 0; i < mainUIbutterns.size(); i++)
		{
			mainUIbutterns[i]->Life();
		}

		bubbleParents[0]->GetScript<UIPanalMoveScript>()->Back();
	}
	Vector3 TitleScene::UIMousePos()
	{
		Vector3 pos = Input::GetMousePosition();

		glm::vec2 screenCoord(pos.x, pos.y);
		glm::mat4 viewProjectionMatrix(1.0f);

		int screenWidth = 1600;
		int screenHeight = 900;

		glm::vec2 cameraCoorcd = ScreenToCamera(screenCoord, viewProjectionMatrix, screenWidth, screenHeight);

		Vector3 mousePos = Vector3(cameraCoorcd.x, cameraCoorcd.y, 0.0f);

		return mousePos;
	}
	void TitleScene::TemporaryPanal()
	{

	}
	void TitleScene::UIReset()
	{
		for (size_t i = 0; i < leves.size(); i++)
		{
			leves[i]->GetScript<LeavesScirpt>()->Reset();
		}
		for (size_t i = 0; i < mainUIbutterns.size(); i++)
		{
			mainUIbutterns[i]->Life();
		}
		for (size_t i = 0; i < bubbleParents.size(); i++)
		{
			bubbleParents[i]->GetScript<UIPanalMoveScript>()->Reset();
		}
		for (size_t i = 0; i < selectPanals.size(); i++)
		{
			selectPanals[i]->GetScript<SelectPanalScript>()->Reset();
		}
		faceParent->GetScript<UIPanalMoveScript>()->Reset();
		bgEye->GetScript<BgEyeScript>()->Reset();
		logo->GetScript<logoScript>()->Reset();
		uiManager->GetScript<TitleUIManager>()->Reset();
	}
	void TitleScene::FirstUI()
	{
		for (size_t i = 0; i < leves.size(); i++)
		{
			leves[i]->GetScript<LeavesScirpt>()->Back();
		}
		bgEye->GetScript<BgEyeScript>()->Reset();
		logo->GetScript<logoScript>()->Reset();

		for (size_t i = 0; i < selectPanals.size(); i++)
		{
			selectPanals[i]->GetScript<SelectPanalScript>()->Back();
		}
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
		UIReset();
		SceneManager::LoadScene(eSceneType::Play);
	}
	void TitleScene::Start()
	{
		leves[0]->GetComponent<Transform>()->SetPosition(Vector3(-6.0f, 1.0f, 9.9f));
		leves[1]->GetComponent<Transform>()->SetPosition(Vector3(8.0f, 1.0f, 9.9f));
		SceneManager::GetPlayScene()->ChoosePlayers(selectCharNum);
		SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->StartSetting();
		UIReset();
		SceneManager::LoadScene(eSceneType::Play);
	}
}
