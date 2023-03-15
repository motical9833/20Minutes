#include "yaPlayScene.h"
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
#include "yaPlayer.h"
#include "yaCollisionManager.h"
#include "yaMonster.h"
#include "yaAnimator.h"


namespace ya
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
		, player(nullptr)
	{
		
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		// Main Camera Game Object
		pSceneCamera = object::Instantiate<GameObject>(eLayerType::Camera,this);
		Camera* cameraComp = pSceneCamera->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera,this);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		//player = object::Instantiate<Player>(eLayerType::Player,this);
		//player->SetName(L"Player");
		//Transform* pTr = player->GetComponent<Transform>();
		//pTr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
		//pTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//Collider2D* pCollider = player->AddComponent<Collider2D>();
		//pCollider->SetType(eColliderType::Rect);
		//SpriteRenderer* pMr = player->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
		//pMr->SetMaterial(mateiral);
		//std::shared_ptr<Mesh> pMesh = Resources::Find<Mesh>(L"RectMesh");
		//pMr->SetMesh(pMesh);
		//player->AddComponent<PlayerScript>();
		//Animator* animator = player->AddComponent<Animator>();
		//std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Shana", L"Player\\Shana.png");
		//animator->Create(L"pIdle", texture, Vector2(0.0f, 0.0f), Vector2(32.5f, 33.0f), Vector2::Zero, 6, 0.1f);
		//animator->Play(L"pIdle", true);

		Monster* monster = object::Instantiate<Monster>(eLayerType::Monster, this);
		monster->SetLayerType(eLayerType::Monster);
		monster->SetName(L"Monster");
		Transform* mTr = monster->GetComponent<Transform>();
		mTr->SetPosition(Vector3(2.0f, 0.0f, 10.0f));
		mTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		Collider2D* mCollider = monster->AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		SpriteRenderer* mMr = monster->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> monsterMat = Resources::Find<Material>(L"MonsterMaterial");
		mMr->SetMaterial(monsterMat);
		std::shared_ptr<Mesh> mMesh = Resources::Find<Mesh>(L"RectMesh");
		mMr->SetMesh(mMesh);
		Animator* mAnimator = monster->AddComponent<Animator>();
		std::shared_ptr<Texture> mTexture = Resources::Load<Texture>(L"BrainMonster", L"Monster\\BrainMonster.png");
		mAnimator->Create(L"BrainMonster_Idle", mTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Play(L"BrainMonster_Idle", true);


		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			//player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
			//player->Life();

			SceneManager::LoadScene(eSceneType::Tilte);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		mainCamera = pSceneCamera->GetComponent<Camera>();
	}

	void PlayScene::OnExit()
	{

	}
}
