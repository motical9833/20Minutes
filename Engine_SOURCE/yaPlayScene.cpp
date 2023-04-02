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
#include "yaPaintShader.h"
#include "yaParticleSystem.h"

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
		//paint Shader
		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		paintShader->SetTarget(Resources::Find<Texture>(L"PaintTexture"));
		paintShader->OnExcute();

		// Particle
		//GameObject* particle = object::Instantiate<Player>(eLayerType::Particle,this);
		//particle->SetName(L"Particle");
		//Transform* particleTr = particle->GetComponent<Transform>();
		//particleTr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
		//particle->AddComponent<ParticleSystem>();




		//SMILE RECT
		{
			Player* smile = object::Instantiate<Player>(eLayerType::None);
			smile->SetName(L"SMILE");
			Transform* smileTr = smile->GetComponent<Transform>();
			smileTr->SetPosition(Vector3(-2.0f, 0.0f, 0.0f));
			SpriteRenderer* smileMr = smile->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			smileMr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> smileMesh = Resources::Find<Mesh>(L"RectMesh");
			smileMr->SetMesh(smileMesh);
			object::DontDestroyOnLoad(smile);
		}

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player,this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Main Camera Game Object
		pSceneCamera = object::Instantiate<GameObject>(eLayerType::Camera,this);
		Camera* cameraComp = pSceneCamera->AddComponent<Camera>();
		Transform* mainCameraTr = pSceneCamera->GetComponent<Transform>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		//pSceneCamera->AddComponent<CameraScript>();

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera,this);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		{
			player = object::Instantiate<Player>(eLayerType::Player, this);
			player->SetName(L"Player");
			Transform* pTr = player->GetComponent<Transform>();
			pTr->SetPosition(Vector3(-3.0f, 0.0f, 0.0f));
			pTr->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			Collider2D* pCollider = player->AddComponent<Collider2D>();
			pCollider->SetType(eColliderType::Rect);
			pCollider->SetSize(Vector2(0.2f, 0.2f));
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
			//mainCameraTr->SetParent(pTr);

			pWeapon = object::Instantiate<Weapon>(eLayerType::Player, this);
			pWeapon->SetName(L"pWeapon");
			Transform* weaponTr = pWeapon->GetComponent<Transform>();
			weaponTr->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			weaponTr->SetParent(pTr);
			weaponTr->SetPosition(Vector3(0.13f, 0.02f, 0.0f));
			SpriteRenderer* pWMr = pWeapon->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> weaponMaterial = Resources::Find<Material>(L"RevolverMaterial");
			pWMr->SetMaterial(weaponMaterial);
			std::shared_ptr<Mesh> revolverMesh = Resources::Find<Mesh>(L"RectMesh");
			pWMr->SetMesh(revolverMesh);
			Animator* weaponAni = pWeapon->AddComponent<Animator>();
			std::shared_ptr<Texture> revolverTexture = Resources::Load<Texture>(L"W_RevolverSprite", L"Weapon\\T_Revolver_SS.png");
			weaponAni->Create(L"Revolver", revolverTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 15.0f), Vector2::Zero, 5, 0.0f);
			weaponAni->Play(L"Revolver", true);
			pWeapon->AddComponent<WeaponScript>();


			bullet = object::Instantiate<Bullet>(eLayerType::Bullet,this);
			Transform* bulletTr = bullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			SpriteRenderer* bMr = bullet->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"BulletMaterial");
			bMr->SetMaterial(bulletMaterial);
			std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
			bMr->SetMesh(bulletMesh);
			Animator* bulletAni = bullet->AddComponent<Animator>();
			std::shared_ptr<Texture> bulletTexture = Resources::Find<Texture>(L"BulletTexture");
			bulletAni->Create(L"Bullet", bulletTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 14.0f), Vector2::Zero, 1, 0.0f);
			bulletAni->Play(L"Bullet", false);

		}

		// Monster
		{
			Monster* m_Brain = object::Instantiate<Monster>(eLayerType::Monster, this);
			m_Brain->SetLayerType(eLayerType::Monster);
			m_Brain->SetName(L"Monster");
			Transform* mTr = m_Brain->GetComponent<Transform>();
			mTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
			mTr->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			Collider2D* mCollider = m_Brain->AddComponent<Collider2D>();
			mCollider->SetType(eColliderType::Rect);
			mCollider->SetSize(Vector2(0.5f, 0.5f));
			SpriteRenderer* mMr = m_Brain->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> monsterMat = Resources::Find<Material>(L"MonsterMaterial");
			mMr->SetMaterial(monsterMat);
			std::shared_ptr<Mesh> mMesh = Resources::Find<Mesh>(L"RectMesh");
			mMr->SetMesh(mMesh);
			Animator* mAnimator = m_Brain->AddComponent<Animator>();
			std::shared_ptr<Texture> mTexture = Resources::Load<Texture>(L"BrainMonster", L"Monster\\BrainMonster.png");
			mAnimator->Create(L"BrainMonster_Idle", mTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
			mAnimator->Play(L"BrainMonster_Idle", true);

			Monster* m_tree = object::Instantiate<Monster>(eLayerType::Monster, this);
			m_tree->SetLayerType(eLayerType::Monster);
			m_tree->SetName(L"tree");
			Transform* mTreeTr = m_tree->GetComponent<Transform>();
			mTreeTr->SetPosition(Vector3(2.0f, 2.0f, 0.0f));
			mTreeTr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			Collider2D* mTreeCollider = m_tree->AddComponent<Collider2D>();
			mTreeCollider->SetType(eColliderType::Rect);
			mTreeCollider->SetSize(Vector2(0.7f, 0.9f));
			SpriteRenderer* mTreeRender = m_tree->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> m_treeMat = Resources::Find<Material>(L"TreeMaterial");
			mTreeRender->SetMaterial(m_treeMat);
			std::shared_ptr<Mesh> treeMesh = Resources::Find<Mesh>(L"RectMesh");
			mTreeRender->SetMesh(treeMesh);
			Animator* treeAnimator = m_tree->AddComponent<Animator>();
			std::shared_ptr<Texture> treeTexture = Resources::Find<Texture>(L"TreeSprite");
			treeAnimator->Create(L"Tree_Idle", treeTexture, Vector2(0.0f, 0.0f), Vector2(110.0f, 160.0f), Vector2::Zero, 3, 0.5f);
			treeAnimator->Play(L"Tree_Idle", true);


			Monster* eyeMonster = object::Instantiate<Monster>(eLayerType::Monster, this);
			eyeMonster->SetLayerType(eLayerType::Monster);
			eyeMonster->SetName(L"EyeMonster");
			Transform* mEyeTr = eyeMonster->GetComponent<Transform>();
			mEyeTr->SetPosition(Vector3(2.0f, -2.0f, 0.0f));
			mEyeTr->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			Collider2D* mEyeCollider = eyeMonster->AddComponent<Collider2D>();
			mEyeCollider->SetType(eColliderType::Rect);
			mEyeCollider->SetSize(Vector2(0.3f, 0.3f));
			SpriteRenderer* mEyeRender = eyeMonster->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> m_EyeMat = Resources::Find<Material>(L"EyeMonsterMaterial");
			mEyeRender->SetMaterial(m_EyeMat);
			std::shared_ptr<Mesh> m_EyeMesh = Resources::Find<Mesh>(L"RectMesh");
			mEyeRender->SetMesh(m_EyeMesh);
			Animator* m_EyeAnimator = eyeMonster->AddComponent<Animator>();
			std::shared_ptr<Texture> m_EyeTexture = Resources::Find<Texture>(L"EyeMonsterSprite");
			m_EyeAnimator->Create(L"EyeMonsterAnimation", m_EyeTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 3, 0.2f);
			m_EyeAnimator->Play(L"EyeMonsterAnimation", true);

			Monster* mBoomer = object::Instantiate<Monster>(eLayerType::Monster, this);
			mBoomer->SetLayerType(eLayerType::Monster);
			mBoomer->SetName(L"BigBoomer");
			Transform* mboomerTr = mBoomer->GetComponent<Transform>();
			mboomerTr->SetPosition(Vector3(4.0f, 0.0f, 0.0f));
			mboomerTr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			Collider2D* mBoomerCollider = mBoomer->AddComponent<Collider2D>();
			mBoomerCollider->SetType(eColliderType::Rect);
			mBoomerCollider->SetSize(Vector2(0.5f, 0.5f));
			SpriteRenderer* mBoomerRender = mBoomer->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mBoomerMat = Resources::Find<Material>(L"BoomerMonsterMaterial");
			mBoomerRender->SetMaterial(mBoomerMat);
			std::shared_ptr<Mesh> mBoomerMesh = Resources::Find<Mesh>(L"RectMesh");
			mBoomerRender->SetMesh(mBoomerMesh);
			Animator* boomerAnimator = mBoomer->AddComponent<Animator>();
			std::shared_ptr<Texture> boomerTexture = Resources::Find<Texture>(L"BoomerMonsterSprite");
			boomerAnimator->Create(L"BoomerAnimation", boomerTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.2f);
			boomerAnimator->Play(L"BoomerAnimation", true);
		}


		std::vector<GameObject*> hpUiObj;
		std::vector<SpriteRenderer*> hpSprite;
		std::vector<Animator*> hpani;
		for (size_t i = 0; i < 10; i++)
		{
			GameObject* uiobj = object::Instantiate<GameObject>(eLayerType::UI, this);
			hpUiObj.push_back(uiobj);
			hpUiObj[i]->SetLayerType(eLayerType::UI);
			hpUiObj[i]->SetName(L"HP" + i);
			hpUiObj[i]->GetComponent<Transform>()->SetPosition(Vector3(-7.5f + (float)i, 4.0f, 10.0f));
			hpUiObj[i]->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			hpUiObj[i]->GetComponent<Transform>()->SetParent(cameraUIObj->GetComponent<Transform>());
			SpriteRenderer* render = hpUiObj[i]->AddComponent<SpriteRenderer>();
			hpSprite.push_back(render);
			std::shared_ptr<Material> hpMaterial = Resources::Find<Material>(L"HpMaterial");
			hpSprite[i]->SetMaterial(hpMaterial);
			std::shared_ptr<Mesh> hpMesh = Resources::Find<Mesh>(L"RectMesh");
			hpSprite[i]->SetMesh(hpMesh);
			Animator* uiAnimator = hpUiObj[i]->AddComponent<Animator>();
			hpani.push_back(uiAnimator);
			std::shared_ptr<Texture> aniamtionTexture = Resources::Load<Texture>(L"HPHeart", L"UI\\T_HeartAnimation.png");
			hpani[i]->Create(L"hpAniamtion", aniamtionTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.1f);
			hpani[i]->Play(L"hpAniamtion", true);
		}


		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
			player->Life();
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			bullet->Death();
		}

		Transform* tr = pSceneCamera->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

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
