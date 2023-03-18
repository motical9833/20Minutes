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
#include "yaWeaponScript.h"

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


		player = object::Instantiate<Player>(eLayerType::Player,this);
		player->SetName(L"Player");
		Transform* pTr = player->GetComponent<Transform>();
		pTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//pTr->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		Collider2D* pCollider = player->AddComponent<Collider2D>();
		pCollider->SetType(eColliderType::Rect);
		pCollider->SetSize(Vector2(0.1f, 0.1f));
		SpriteRenderer* pMr = player->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
		pMr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> pMesh = Resources::Find<Mesh>(L"RectMesh");
		pMr->SetMesh(pMesh);
		player->AddComponent<PlayerScript>();
		Animator* animator = player->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Shana", L"Player\\Shana.png");
		animator->Create(L"pIdle", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
		animator->Create(L"pMove", texture, Vector2(0.0f, 33.3f), Vector2(32.0f, 33.3f), Vector2::Zero, 4, 0.15f);
		animator->Play(L"pIdle", true);


		pWeapon = object::Instantiate<Weapon>(eLayerType::Player, this);
		pWeapon->SetName(L"pWeapon");
		Transform* weaponTr = pWeapon->AddComponent<Transform>();
		weaponTr->SetScale(Vector3(2.0f, 2.0f,1.0f));
		weaponTr->SetParent(pTr);
		weaponTr->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
		SpriteRenderer* pWMr = pWeapon->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> weaponMaterial = Resources::Find<Material>(L"RevolverMaterial");
		pWMr->SetMaterial(weaponMaterial);
		std::shared_ptr<Mesh> revolverMesh = Resources::Find<Mesh>(L"RectMesh");
		pWMr->SetMesh(revolverMesh);
		Animator* weaponAni = pWeapon->AddComponent<Animator>();
		std::shared_ptr<Texture> revolverTexture = Resources::Load<Texture>(L"W_RevolverSprite", L"Weapon\\T_Revolver_SS.png");
		weaponAni->Create(L"Revolver", revolverTexture, Vector2(0.0f, 0.0f), Vector2(9.0f, 15.0f), Vector2::Zero, 5, 0.0f);
		weaponAni->Play(L"Revolver", true);
		pWeapon->AddComponent<WeaponScript>();

		Monster* monster = object::Instantiate<Monster>(eLayerType::Monster, this);
		monster->SetLayerType(eLayerType::Monster);
		monster->SetName(L"Monster");
		Transform* mTr = monster->GetComponent<Transform>();
		mTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		//mTr->SetScale(Vector3(3.0f,3.0f, 1.0f));
		Collider2D* mCollider = monster->AddComponent<Collider2D>();
		mCollider->SetType(eColliderType::Rect);
		mCollider->SetSize(Vector2(0.3f, 0.3f));
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
