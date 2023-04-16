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
#include "yaCollisionManager.h"
#include "yaAnimator.h"
#include "yaWeaponScript.h"
#include "yaPaintShader.h"
#include "yaParticleSystem.h"
#include "yaBulletScript.h"
#include "yaMonsterScript.h"
#include "yaThunderScript.h"

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

		//Particle
		//GameObject* particle = object::Instantiate<Player>(eLayerType::Particle,this);
		//particle->SetName(L"Particle");
		//Transform* particleTr = particle->GetComponent<Transform>();
		//particleTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
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
		pSceneCamera->SetName(L"PSMCamera");
		Camera* cameraComp = pSceneCamera->AddComponent<Camera>();
		Transform* mainCameraTr = pSceneCamera->GetComponent<Transform>();
		mainCameraTr->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		cameraComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		pSceneCamera->AddComponent<CameraScript>();


		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera,this);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		{
			player = object::Instantiate<Player>(eLayerType::Player, this);
			player->SetLayerType(eLayerType::Player);
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
			Animator* animator = player->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Shana", L"Player\\Shana.png");
			animator->Create(L"pIdle", texture, Vector2(0.0f, 0.0f), Vector2(32.0f, 33.3f), Vector2::Zero, 6, 0.2f);
			animator->Create(L"pMove", texture, Vector2(0.0f, 33.3f), Vector2(32.0f, 33.3f), Vector2::Zero, 4, 0.15f);
			animator->Play(L"pIdle", true);
			mainCameraTr->SetParent(pTr);
			mainCameraTr->SetPosition(pTr->GetPosition() + Vector3(0.0f,0.0f,-10.0f));
			player->AddComponent<PlayerScript>();
			player->GetScript<PlayerScript>()->Reset(); 


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

			for (size_t i = 0; i < 4; i++)
			{
				GameObject* firePosObject = object::Instantiate<GameObject>(eLayerType::None, this);
				firePosObject->SetName(L"FirePosObject" + i);
				firePosObject->GetComponent<Transform>()->SetParent(weaponTr);
				firePosObject->GetComponent<Transform>()->SetPosition(Vector3(0.3f, 0.0f, 0.0f));
				firePosObject->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
				pWeapon->GetScript<WeaponScript>()->SetFirePosObject(firePosObject);
			}

			for (size_t i = 0; i < 100; i++)
			{
				Bullet* bulletobj = object::Instantiate<Bullet>(eLayerType::Bullet, this);
				bullets.push_back(bulletobj);
				bullets[i]->SetLayerType(eLayerType::Bullet);
				bullets[i]->SetName(L"Bullet" + i);
				bullets[i]->GetComponent<Transform>()->SetParent(weaponTr);
				bullets[i]->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				bullets[i]->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				bullets[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
				Collider2D* bulletColloder = bullets[i]->AddComponent<Collider2D>();
				bulletColloder->SetType(eColliderType::Rect);
				bulletColloder->SetSize(Vector2(0.1f, 0.1f));
				SpriteRenderer* render = bullets[i]->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"BulletMaterial");
				render->SetMaterial(bulletMaterial);
				std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
				render->SetMesh(bulletMesh);
				Animator* bulletAnimator = bullets[i]->AddComponent<Animator>();
				std::shared_ptr<Texture> bulletTexture = Resources::Find<Texture>(L"BulletTexture");
				bulletAnimator->Create(L"BulletAni", bulletTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 14.0f), Vector2::Zero, 2, 0.0f);
				bulletAnimator->Play(L"BulletAni", true);
				bulletAnimator->Stop();
				bullets[i]->AddComponent<BulletScript>();
				pWeapon->GetScript<WeaponScript>()->SetBullets(bullets[i]->GetComponent<Transform>());
			}

			for (size_t i = 0; i < 20; i++)
			{
				GameObject* thunderObject = object::Instantiate<GameObject>(eLayerType::Bullet, this);
				thunders.push_back(thunderObject);
				thunders[i]->SetLayerType(eLayerType::Bullet);
				thunders[i]->GetComponent<Transform>()->SetScale(Vector3(1.0f, 5.0f, 1.0f));
				thunders[i]->GetComponent<Transform>()->SetPosition(Vector3::Zero);
				Collider2D* thunderCollider = thunders[i]->AddComponent<Collider2D>();
				thunderCollider->SetType(eColliderType::Rect);
				thunderCollider->SetSize(Vector2(1.0f,0.2f));
				thunderCollider->SetCenter(Vector2(0.0f, -2.0f));
				SpriteRenderer* render = thunders[i]->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> thunderMaterial = Resources::Find<Material>(L"ThunderMaterial");
				render->SetMaterial(thunderMaterial);
				std::shared_ptr<Mesh> thunderMesh = Resources::Find<Mesh>(L"RectMesh");
				render->SetMesh(thunderMesh);
				Animator* thunderAnimator = thunders[i]->AddComponent<Animator>();
				std::shared_ptr<Texture>thunderTexture = Resources::Find<Texture>(L"S_Thunder");
				thunderAnimator->Create(L"ThunderAni", thunderTexture, Vector2::Zero, Vector2(32.0f, 450.0f), Vector2::Zero, 8, 0.05f);
				thunderAnimator->Play(L"ThunderAni", false);
				thunders[i]->AddComponent<ThunderScript>();
				thunders[i]->Death();
			}
		}

		// Monster
		{
			CreateBrainMonster();
			CreateEyeMonster();
			CreateTreeMonster();
			CreateBommerMonster();
		}


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
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster, true);
		Scene::Initalize();
	}

	void PlayScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			pWeapon->GetScript<WeaponScript>()->Reset();
			player->Life();
			pWeapon->Life();
			mBoomerMonsters[0]->GetScript<MonsterScript>()->Reset();
			mBrainMonsters[0]->GetScript<MonsterScript>()->Reset();
			mEyeMonsters[0]->GetScript<MonsterScript>()->Reset();


			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i]->GetScript<BulletScript>()->Reset();
				bullets[i]->Death();
			}
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
	void PlayScene::CreateBrainMonster()
	{
		Monster* m_Brain = object::Instantiate<Monster>(eLayerType::Monster, this);
		m_Brain->SetLayerType(eLayerType::Monster);
		m_Brain->SetName(L"Monster");
		M_DefaultTr(m_Brain, Vector3(2.0f, 0.0f, 0.0f), Vector3(3.0f, 3.0f, 1.0f));
		CreateCollider(m_Brain, eColliderType::Rect, Vector2(0.5f, 0.5f));
		CreateSpriteRenderer(m_Brain, L"MonsterMaterial");
		Animator* mAnimator = m_Brain->AddComponent<Animator>();
		std::shared_ptr<Texture> mTexture = Resources::Find<Texture>(L"BrainMonster");
		std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		mAnimator->Create(L"m_Idle", mTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Play(L"m_Idle", true);
		m_Brain->AddComponent<MonsterScript>(50);
		mBrainMonsters.push_back(m_Brain);

	}
	void PlayScene::CreateTreeMonster()
	{
		Monster* m_tree = object::Instantiate<Monster>(eLayerType::Monster, this);
		m_tree->SetLayerType(eLayerType::Monster);
		m_tree->SetName(L"tree");
		M_DefaultTr(m_tree, Vector3(2.0f, 2.0f, 0.0f), Vector3(2.0f, 2.0f, 1.0f));
		CreateCollider(m_tree, eColliderType::Rect, Vector2(0.7f, 0.9f));
		CreateSpriteRenderer(m_tree, L"TreeMaterial");
		Animator* treeAnimator = m_tree->AddComponent<Animator>();
		std::shared_ptr<Texture> treeTexture = Resources::Find<Texture>(L"TreeSprite");
		std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		treeAnimator->Create(L"m_Idle", treeTexture, Vector2(0.0f, 0.0f), Vector2(110.0f, 160.0f), Vector2::Zero, 3, 0.5f);
		treeAnimator->Play(L"m_Idle", true);
		m_tree->AddComponent<MonsterScript>();
		mTreeMonsters.push_back(m_tree);
	}
	void PlayScene::CreateEyeMonster()
	{
		Monster* eyeMonster = object::Instantiate<Monster>(eLayerType::Monster, this);
		eyeMonster->SetLayerType(eLayerType::Monster);
		eyeMonster->SetName(L"EyeMonster");
		M_DefaultTr(eyeMonster, Vector3(2.0f, -2.0f, 0.0f), Vector3(3.0f, 3.0f, 1.0f));
		CreateCollider(eyeMonster, eColliderType::Rect, Vector2(0.3f, 0.3f));
		CreateSpriteRenderer(eyeMonster, L"EyeMonsterMaterial");
		Animator* m_EyeAnimator = eyeMonster->AddComponent<Animator>();
		std::shared_ptr<Texture> m_EyeTexture = Resources::Find<Texture>(L"EyeMonsterSprite");
		std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		m_EyeAnimator->Create(L"m_Idle", m_EyeTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 3, 0.2f);
		m_EyeAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		m_EyeAnimator->Play(L"m_Idle", true);
		eyeMonster->AddComponent<MonsterScript>(50);
		mEyeMonsters.push_back(eyeMonster);
	}
	void PlayScene::CreateBommerMonster()
	{
		Monster* mBoomer = object::Instantiate<Monster>(eLayerType::Monster, this);
		mBoomer->SetLayerType(eLayerType::Monster);
		mBoomer->SetName(L"BigBoomer");
		M_DefaultTr(mBoomer, Vector3(4.0f, 0.0f, 0.0f), Vector3(2.0f, 2.0f, 1.0f));
		CreateCollider(mBoomer, eColliderType::Rect,Vector2(0.5f,0.5f));
		CreateSpriteRenderer(mBoomer, L"BoomerMonsterMaterial");
		Animator* boomerAnimator = mBoomer->AddComponent<Animator>();
		std::shared_ptr<Texture> boomerTexture = Resources::Find<Texture>(L"BoomerMonsterSprite");
		std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		boomerAnimator->Create(L"m_Idle", boomerTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.2f);
		boomerAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		boomerAnimator->Play(L"m_Idle", true);
		mBoomer->AddComponent<MonsterScript>(50);
		mBoomerMonsters.push_back(mBoomer);
	}

	void PlayScene::CreateCollider(auto* object, eColliderType type,Vector2 size)
	{
		Collider2D* collider = object->AddComponent<Collider2D>();
		collider->SetType(type);
		collider->SetSize(size);
	}

	void PlayScene::M_DefaultTr(auto* object,Vector3 pos,Vector3 scale)
	{
		Transform* mboomerTr = object->GetComponent<Transform>();
		mboomerTr->SetPosition(pos);
		mboomerTr->SetScale(scale);
	}

	void PlayScene::CreateDeathFX()
	{
		GameObject* deathObj = object::Instantiate<GameObject>(eLayerType::None, this);
		deathObj->Death();
		Transform* deathObjTr = deathObj->GetComponent<Transform>();
		deathObjTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		deathObjTr->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		SpriteRenderer* deathRender = deathObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> deathMr = Resources::Find<Material>(L"M_DeathMaterial");
		deathRender->SetMaterial(deathMr);
		std::shared_ptr<Mesh> deathMesh = Resources::Find<Mesh>(L"RectMesh");
		deathRender->SetMesh(deathMesh);
		Animator* deathAni = deathObj->AddComponent<Animator>();
		std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		deathAni->Create(L"m_Idle", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.2f);
		deathAni->Play(L"m_Idle", false);
	}

	void PlayScene::CreateSpriteRenderer(auto* object, const std::wstring& materialKey)
	{
		SpriteRenderer* spriteRender = object->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(materialKey);
		spriteRender->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		spriteRender->SetMesh(mesh);
	}

	void PlayScene::CreateAnimator(auto* object)
	{
		
	}
}
