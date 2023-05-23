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
#include "yaSkillManager.h"
#include "GaleScript.h"
#include "yaHolyShieldScript.h"
#include "yaMagicLensScript.h"
#include "yaCurseScript.h"
#include "yaDragonPetScript.h"
#include "yaGhostPetScript.h"
#include "yaGhostBullet.h"
#include "yaScytheScript.h"
#include "yaColliderCheckScript.h"
#include "yaSmiteScript.h"
#include "yaSpearScript.h"
#include "yaDragonFireScript.h"
#include "yaUpgradeScript.h"
#include "yaThunderBugScript.h"
#include "yaIcicleScript.h"
#include "yaRotScript.h"
#include "yaPlayerLevelScript.h"
#include "yaLevelUPEffectScript.h"
#include "yaExpMarbleObject.h"

#define SHANA 0
#define ABBY 1
#define DIAMOND 2
#define HINA 3
#define LILITH 4


namespace ya
{

	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
		, player(nullptr)
		, uiOn(false)
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
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Perspective);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		for (size_t i = 0; i < 5; i++)
		{
			Player* playerObj = object::Instantiate<Player>(eLayerType::Player, this);
			playerObj->SetLayerType(eLayerType::Player);
			Transform* pTr = playerObj->GetComponent<Transform>();
			pTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			pTr->SetScale(Vector3(4.0f, 4.0f, 1.0f));
			Collider2D* pCollider = playerObj->AddComponent<Collider2D>();
			pCollider->SetType(eColliderType::Rect);
			pCollider->SetSize(Vector2(0.2f, 0.2f));
			SpriteRenderer* pMr = playerObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			pMr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> pMesh = Resources::Find<Mesh>(L"RectMesh");
			pMr->SetMesh(pMesh);
			playerObj->AddComponent<Animator>();
			playerObj->AddComponent<PlayerScript>(i, 3);
			playerObj->GetScript<PlayerScript>()->Reset();
			playerObj->Death();
			players.push_back(playerObj);
		}




		pWeapon = object::Instantiate<Weapon>(eLayerType::Player, this);
		pWeapon->SetName(L"pWeapon");
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

		for (size_t i = 0; i < 5; i++)
		{
			GameObject* firePosObject = object::Instantiate<GameObject>(eLayerType::None, this);
			firePosObject->SetName(L"FirePosObject" + i);
			firePosObject->GetComponent<Transform>()->SetParent(pWeapon->GetComponent<Transform>());
			if (i == 4)
			{
				firePosObject->GetComponent<Transform>()->SetPosition(Vector3(-1.0f, 0.0f, 0.0f));
				firePosObject->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, -3.1f));
			}
			else
			{
				firePosObject->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
				firePosObject->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			}
			pWeapon->GetScript<WeaponScript>()->SetFirePosObject(firePosObject);
		}

		for (size_t i = 0; i < 1000; i++)
		{
			Bullet* bulletobj = object::Instantiate<Bullet>(eLayerType::Bullet, this);
			bullets.push_back(bulletobj);
			bullets[i]->SetLayerType(eLayerType::Bullet);
			bullets[i]->SetName(L"Bullet" + i);
			bullets[i]->GetComponent<Transform>()->SetParent(pWeapon->GetComponent<Transform>());
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


		// Monster
		{
			CreateBrainMonster();
			CreateEyeMonster();
			CreateTreeMonster();
			CreateBommerMonster();
		}


		// SKill
		CreateThunder();

		pulseObject = object::Instantiate<GameObject>(eLayerType::Skill, this);
		pulseObject->SetLayerType(eLayerType::Skill);

		CreateGale();
		CreateHolyShiled();


		CreateLevelUpEffect();

		for (size_t i = 0; i < 200; i++)
		{
			GameObject* freeze = object::Instantiate<GameObject>(eLayerType::Skill, this);
			freeze->GetComponent<Transform>()->SetPosition(Vector3::Zero);
			freeze->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			freeze->SetLayerType(eLayerType::Skill);
			SpriteRenderer* FreezeRender = freeze->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> freezeMaterial = Resources::Find<Material>(L"FreezeMaterial");
			FreezeRender->SetMaterial(freezeMaterial);
			std::shared_ptr<Mesh> freezeMesh = Resources::Find<Mesh>(L"RectMesh");
			FreezeRender->SetMesh(freezeMesh);

			Animator* freezeAnimator = freeze->AddComponent<Animator>();
			std::shared_ptr<Texture> freezeTexture = Resources::Find<Texture>(L"S_Freeze");

			freezeAnimator->Create(L"freezeAni", freezeTexture, Vector2::Zero, Vector2(64.0f, 64.0f), Vector2::Zero, 5, 0.1f);
			freezeAnimator->Play(L"freezeAni", true);
			freeze->Death();
			freezes.push_back(freeze);
		}
		freezes[0]->GetComponent<Transform>()->SetParent(mBrainMonsters[0]->GetComponent<Transform>());
		freezes[1]->GetComponent<Transform>()->SetParent(mBoomerMonsters[0]->GetComponent<Transform>());
		freezes[2]->GetComponent<Transform>()->SetParent(mEyeMonsters[0]->GetComponent<Transform>());
		freezes[3]->GetComponent<Transform>()->SetParent(mTreeMonsters[0]->GetComponent<Transform>());

		for (size_t i = 0; i < 200; i++)
		{
			GameObject* curse = object::Instantiate<GameObject>(eLayerType::Skill, this);
			curse->SetLayerType(eLayerType::Skill);
			curse->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			curse->GetComponent<Transform>()->SetPosition(Vector3::Zero);
			SpriteRenderer* curseRender = curse->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> curseMaterial = Resources::Find<Material>(L"CurseMaterial");
			curseRender->SetMaterial(curseMaterial);
			std::shared_ptr<Mesh> curseMesh = Resources::Find<Mesh>(L"RectMesh");
			curseRender->SetMesh(curseMesh);

			Animator* curseAnimator = curse->AddComponent<Animator>();
			std::shared_ptr<Texture> curseTexture = Resources::Find<Texture>(L"S_Curse");

			curseAnimator->Create(L"curseAni", curseTexture, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.2f);
			curseAnimator->Create(L"curseUpgrade", curseTexture, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.4f);
			curseAnimator->Play(L"curseAni", false);

			curse->AddComponent<CurseScript>();

			curse->Death();
			curses.push_back(curse);
		}
		curses[0]->GetComponent<Transform>()->SetParent(mBrainMonsters[0]->GetComponent<Transform>());
		curses[1]->GetComponent<Transform>()->SetParent(mBoomerMonsters[0]->GetComponent<Transform>());
		curses[2]->GetComponent<Transform>()->SetParent(mEyeMonsters[0]->GetComponent<Transform>());
		curses[3]->GetComponent<Transform>()->SetParent(mTreeMonsters[0]->GetComponent<Transform>());

		CreateSmite();
		CreateMagicLens();
		CreateDragonPet();
		CreateDragonPetBullet();
		CreateGhostPet();
		CreateGhostPetBullet();
		CreateScythe();
		CreateColliderChackObj();
		CreateSpear();
		CreateThunderBug();
		CreateIcicle();
		CreateExpMarble();
		CreateGameManagers();
		CreateHpUIobj(cameraUIObj);
		CreateSkillUI(cameraUIObj);
		CreateAbilityIcon(cameraUIObj);


		//Particle
		//GameObject* particle = object::Instantiate<Player>(eLayerType::Particle, this);
		//particle->SetName(L"Particle");
		//Transform* particleTr = particle->GetComponent<Transform>();
		//particleTr->SetPosition(Vector3::Zero);
		//particle->AddComponent<ParticleSystem>();
		//particleTr->SetParent(player->GetComponent<Transform>());


		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::ExpMarble, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::ColliderChack, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::ColliderChack, eLayerType::ExpMarble, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill_Smite, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill, eLayerType::Bullet, true);
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
			player->GetScript<PlayerScript>()->GameReset();
			pWeapon->Life();
			pWeapon->GetScript<WeaponScript>()->GameReset();
			mBoomerMonsters[0]->GetScript<MonsterScript>()->GameReset();
			mBrainMonsters[0]->GetScript<MonsterScript>()->GameReset();
			mEyeMonsters[0]->GetScript<MonsterScript>()->GameReset();
			skillManager->GetScript<SkillManager>()->GameReset();
			holyShield->GetScript<HolyShieldScript>()->GameReset();
			dragonPet->GetScript<DragonPetScript>()->GameReset();
			ghostPet->GetScript<GhostPetScript>()->GameReset();
			levelManager->GetScript<PlayerLevelScript>()->GameReset();

			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i]->GetScript<BulletScript>()->Reset();
				bullets[i]->Death();
			}

			for (size_t i = 0; i < gales.size(); i++)
			{
				gales[i]->GetScript<GaleScript>()->GameReset();
				gales[i]->Death();
			}

			for (size_t i = 0; i < thunders.size(); i++)
			{
				thunders[i]->GetScript<ThunderScript>()->GameReset();
				thunders[i]->Death();
			}

			for (size_t i = 0; i < smites.size(); i++)
			{
				smites[i]->GetScript<SmiteScript>()->GameReset();
				smites[i]->Death();
			}

			for (size_t i = 0; i < ghostBullets.size(); i++)
			{
				ghostBullets[i]->GetScript<GhostBullet>()->GameReset();
				ghostBullets[i]->Death();
			}

			for (size_t i = 0; i < expMarbles.size(); i++)
			{
				expMarbles[i]->GetScript<ExpMarbleObject>()->GameReset();
				expMarbles[i]->Death();
			}
		}

		Transform* tr = pSceneCamera->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::NUM_1))
		{
			//ALLSKILL();
		}
		if (Input::GetKeyDown(eKeyCode::NUM_2))
		{
			SetStart(); 
			uiOn = false;
			for (size_t i = 0; i < uiObjects.size(); i++)
			{
				uiObjects[i]->Death();
			}
			for (size_t i = 0; i < iconObjects.size(); i++)
			{
				iconObjects[i]->Death();
			}
		}

		if (Input::GetKeyDown(eKeyCode::P))
		{
			mBrainMonsters[0]->GetScript<MonsterScript>()->Respawn();
			mBrainMonsters[0]->Life();
			expMarbles[0]->Life();
		}


		if (Input::GetKeyDown(eKeyCode::LBTN) && uiOn)
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
	void PlayScene::ChoosePlayers(int num)
	{
		players[num]->Life();
		player = players[num];

		Transform* mainCameraTr = pSceneCamera->GetComponent<Transform>();
		mainCameraTr->SetParent(player->GetComponent<Transform>());
		mainCameraTr->SetPosition(player->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, 0.0f, -10.0f));

		Transform* weaponTr = pWeapon->GetComponent<Transform>();
		weaponTr->SetParent(player->GetComponent<Transform>());
		weaponTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		weaponTr->SetPosition(Vector3(0.3f, 0.02f, 0.0f));

		levelUPEffectObj->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());
		levelUPEffectObj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.7f, 0.0f));
		levelUPEffectObj->GetComponent<Transform>()->SetScale(Vector3(2.0f, 5.0f, 1.0f));

		holyShield->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

		for (size_t i = 0; i < mBrainMonsters.size(); i++)
		{
			mBrainMonsters[i]->GetScript<MonsterScript>()->SetPlayer(players[num]);
		}
		for (size_t i = 0; i < mTreeMonsters.size(); i++)
		{
			mTreeMonsters[i]->GetScript<MonsterScript>()->SetPlayer(players[num]);
		}
		for (size_t i = 0; i < mEyeMonsters.size(); i++)
		{
			mEyeMonsters[i]->GetScript<MonsterScript>()->SetPlayer(players[num]);
		}
		for (size_t i = 0; i < mBoomerMonsters.size(); i++)
		{
			mBoomerMonsters[i]->GetScript<MonsterScript>()->SetPlayer(players[num]);
		}
	}
	void PlayScene::CreatePlayer()
	{

	}
	void PlayScene::CreateBrainMonster()
	{
		Monster* m_Brain = object::Instantiate<Monster>(eLayerType::Monster, this);
		m_Brain->SetLayerType(eLayerType::Monster);
		m_Brain->SetName(L"brain");
		M_DefaultTr(m_Brain, Vector3(-2.0f, 0.0f, 0.0f), Vector3(2.0f,2.0f,1.0f));
		CreateCollider(m_Brain, eColliderType::Rect, Vector2(0.5f, 0.5f));
		CreateSpriteRenderer(m_Brain, L"BrainMonsterMaterial");
		Animator* mAnimator = m_Brain->AddComponent<Animator>();
		std::shared_ptr<Texture> mTexture = Resources::Find<Texture>(L"BrainMonster");
		std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		mAnimator->Create(L"m_Right", mTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Create(L"m_Left", mTexture, Vector2(0.0f, 64.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		mAnimator->Play(L"m_Left", true);
		m_Brain->AddComponent<MonsterScript>(10);
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
		treeAnimator->Create(L"m_Right", treeTexture, Vector2(0.0f, 0.0f), Vector2(110.0f, 160.0f), Vector2::Zero, 3, 0.5f);
		treeAnimator->Create(L"m_Left", treeTexture, Vector2(0.0f, 0.0f), Vector2(110.0f, 160.0f), Vector2::Zero, 3, 0.5f);
		treeAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		treeAnimator->Play(L"m_Right", true);
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
		m_EyeAnimator->Create(L"m_Right", m_EyeTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 3, 0.1f);
		m_EyeAnimator->Create(L"m_Left", m_EyeTexture, Vector2(0.0f, 40.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 3, 0.1f);
		m_EyeAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		m_EyeAnimator->Play(L"m_Left", true);
		eyeMonster->AddComponent<MonsterScript>(400);
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
		boomerAnimator->Create(L"m_Right", boomerTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.2f);
		boomerAnimator->Create(L"m_Left", boomerTexture, Vector2(0.0f, 58.5f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.2f);
		boomerAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		boomerAnimator->Play(L"m_Left", true);
		mBoomer->AddComponent<MonsterScript>(500);
		mBoomerMonsters.push_back(mBoomer);
	}

	void PlayScene::CreateDragonPet()
	{
		dragonPet = CreateSkillObject(eLayerType::Skill, L"DragonMaterial");
		dragonPet->SetLayerType(eLayerType::Skill);
		dragonPet->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		Animator* dragonAnimator = dragonPet->AddComponent<Animator>();
		std::shared_ptr<Texture> dragonEggTexture = Resources::Find<Texture>(L"S_DragonEgg");
		std::shared_ptr<Texture> dragonTexture = Resources::Find<Texture>(L"S_Dragon");
		dragonAnimator->Create(L"DragonEgg", dragonEggTexture, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 1, 255);
		dragonAnimator->Create(L"DragonIdle", dragonTexture, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 6, 0.1f);
		dragonAnimator->Create(L"DragonAttack", dragonTexture, Vector2(0, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		dragonAnimator->Play(L"DragonEgg", true);
		dragonPet->AddComponent<DragonPetScript>();
		dragonPet->Death();
	}

	void PlayScene::CreateDragonPetBullet()
	{
		for (size_t i = 0; i < 20; i++)
		{
			Bullet* bullet = object::Instantiate<Bullet>(eLayerType::Skill, this);
			bullet->SetLayerType(eLayerType::Skill);
			Transform* bTr = bullet->GetComponent<Transform>();
			bTr->SetPosition(Vector3::Zero);
			bTr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			Collider2D* bulletColloder = bullet->AddComponent<Collider2D>();
			bulletColloder->SetType(eColliderType::Rect);
			bulletColloder->SetSize(Vector2(0.1f, 0.1f));
			SpriteRenderer* render = bullet->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"BulletMaterial");
			render->SetMaterial(bulletMaterial);
			std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
			render->SetMesh(bulletMesh);
			Animator* bulletAnimator = bullet->AddComponent<Animator>();
			std::shared_ptr<Texture> bulletTexture = Resources::Find<Texture>(L"BulletTexture");
			bulletAnimator->Create(L"BulletAni", bulletTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 14.0f), Vector2::Zero, 2, 0.0f);
			bulletAnimator->Play(L"BulletAni", true);
			bulletAnimator->Stop();
			bullet->AddComponent<DragonFireScript>();
			bullet->Death();
			dragonFires.push_back(bullet);
		}
	}

	void PlayScene::CreateGhostPet()
	{
		ghostPet = CreateSkillObject(eLayerType::Skill, L"DragonMaterial");
		ghostPet->SetLayerType(eLayerType::Skill);
		ghostPet->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		Animator* ghostPetAnimator = ghostPet->AddComponent<Animator>();
		std::shared_ptr<Texture> ghostPetTexture = Resources::Find<Texture>(L"S_GhostPet");
		ghostPetAnimator->Create(L"ghostPetIdle", ghostPetTexture, Vector2::Zero, Vector2(16.0f, 16.0f), Vector2::Zero, 6, 0.1f);
		ghostPetAnimator->Create(L"ghostPetAttack", ghostPetTexture, Vector2(0, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 4, 0.1f);
		ghostPetAnimator->Play(L"ghostPetIdle", true);
		ghostPet->AddComponent<GhostPetScript>();
		ghostPet->Death();
	}

	void PlayScene::CreateGhostPetBullet()
	{
		for (size_t i = 0; i < 20; i++)
		{
			Bullet* bullet = object::Instantiate<Bullet>(eLayerType::Skill, this);
			bullet->SetLayerType(eLayerType::Skill);
			Transform* bTr = bullet->GetComponent<Transform>();
			bTr->SetPosition(Vector3::Zero);
			bTr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			Collider2D* bulletColloder = bullet->AddComponent<Collider2D>();
			bulletColloder->SetType(eColliderType::Rect);
			bulletColloder->SetSize(Vector2(0.1f, 0.1f));
			SpriteRenderer* render = bullet->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"BulletMaterial");
			render->SetMaterial(bulletMaterial);
			std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
			render->SetMesh(bulletMesh);
			Animator* bulletAnimator = bullet->AddComponent<Animator>();
			std::shared_ptr<Texture> bulletTexture = Resources::Find<Texture>(L"BulletTexture");
			bulletAnimator->Create(L"BulletAni", bulletTexture, Vector2(0.0f, 0.0f), Vector2(16.0f, 14.0f), Vector2::Zero, 2, 0.0f);
			bulletAnimator->Play(L"BulletAni", true);
			bulletAnimator->Stop();
			bullet->AddComponent<GhostBullet>();
			bullet->Death();
			ghostBullets.push_back(bullet);
		}
	}

	void PlayScene::CreateSmite()
	{
		for (size_t i = 0; i < 30; i++)
		{
			GameObject* smite = CreateSkillObject(eColliderType::Rect, eLayerType::Skill_Smite, L"SmiteFXMaterial");
			smite->SetLayerType(eLayerType::Skill_Smite);
			smite->GetComponent<Transform>()->SetPosition(Vector3::Zero);
			smite->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			smite->GetComponent<Collider2D>()->SetSize(Vector2(0.3f, 0.3f));
			smite->GetComponent<Collider2D>()->SetCenter(Vector2(0.0f, -0.6f));
			Animator* smiteAnimator = smite->AddComponent<Animator>();
			std::shared_ptr<Texture> smiteTexture = Resources::Find<Texture>(L"S_SmiteFX");
			smiteAnimator->Create(L"Smite", smiteTexture, Vector2::Zero, Vector2(32.0f, 96.0f), Vector2::Zero, 4, 0.1f);
			smiteAnimator->Play(L"Smite", false);
			smite->AddComponent<SmiteScript>();
			smite->Death();
			smites.push_back(smite);
		}

		ghostPetRotobject = object::Instantiate<GameObject>(eLayerType::None, this);
		ghostPetRotobject->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		ghostPetRotobject->AddComponent<RotScript>();
	}

	void PlayScene::CreateMagicLens()
	{
		magicLens = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"MagicLensMaterial");
		magicLens->SetLayerType(eLayerType::Skill);
		magicLens->GetComponent<Transform>()->SetPosition(Vector3(-4.0f, 0.0f, 0.0f));
		magicLens->GetComponent<Collider2D>()->SetSize(Vector2(0.2f, 1.0f));
		Collider2D* lensCollider = magicLens->GetComponent<Collider2D>();
		lensCollider->SetCenter(Vector2::Zero);
		Animator* lensAnimator = magicLens->AddComponent<Animator>();
		std::shared_ptr<Texture> lensTexture = Resources::Find<Texture>(L"S_MagicLens");
		magicLens->AddComponent<MagicLensScript>();
		magicLens->Death();
	}

	void PlayScene::CreateHolyShiled()
	{
		holyShield = CreateSkillObject(eLayerType::Skill, L"HolyShieldMaterial");
		holyShield->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		Animator* shieldAnimator = holyShield->AddComponent<Animator>();
		std::shared_ptr<Texture> ShieldIdle = Resources::Find<Texture>(L"S_HolyShieldIdle");
		std::shared_ptr<Texture> ShieldIHit = Resources::Find<Texture>(L"S_HolyShieldIHit");
		std::shared_ptr<Texture> shieldBreak = Resources::Find<Texture>(L"S_HolyShieldBreak");
		shieldAnimator->Create(L"HolyShieldIdle", ShieldIdle, Vector2::Zero, Vector2(48.0f, 48.0f), Vector2::Zero, 7, 0.1f);
		shieldAnimator->Create(L"HolyShieldIHit", ShieldIHit, Vector2::Zero, Vector2(48.0f, 48.0f), Vector2::Zero, 5, 0.1f);
		shieldAnimator->Create(L"HolyShieldBreak", shieldBreak, Vector2::Zero, Vector2(52.0f, 52.0f), Vector2::Zero, 3, 0.1f);
		shieldAnimator->Play(L"HolyShieldIdle", true);
		holyShield->AddComponent<HolyShieldScript>();
		holyShield->Death();
	}

	void PlayScene::CreateThunder()
	{
		for (size_t i = 0; i < 50; i++)
		{
			GameObject* thunderObject = object::Instantiate<GameObject>(eLayerType::Skill, this);
			thunderObject->SetLayerType(eLayerType::Skill);
			thunderObject->GetComponent<Transform>()->SetScale(Vector3(1.0f, 5.0f, 1.0f));
			thunderObject->GetComponent<Transform>()->SetPosition(Vector3::Zero);
			Collider2D* thunderCollider = thunderObject->AddComponent<Collider2D>();
			thunderCollider->SetType(eColliderType::Rect);
			thunderCollider->SetSize(Vector2(0.2f, 1.0f));
			thunderCollider->SetCenter(Vector2(0.0f, 0.0f));
			SpriteRenderer* render = thunderObject->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> thunderMaterial = Resources::Find<Material>(L"ThunderMaterial");
			render->SetMaterial(thunderMaterial);
			std::shared_ptr<Mesh> thunderMesh = Resources::Find<Mesh>(L"RectMesh");
			render->SetMesh(thunderMesh);
			Animator* thunderAnimator = thunderObject->AddComponent<Animator>();
			std::shared_ptr<Texture>thunderTexture = Resources::Find<Texture>(L"S_Thunder");
			thunderAnimator->Create(L"ThunderAni", thunderTexture, Vector2::Zero, Vector2(32.0f, 450.0f), Vector2::Zero, 8, 0.05f);
			thunderAnimator->Play(L"ThunderAni", false);
			thunderObject->AddComponent<ThunderScript>();
			thunderObject->Death();
			thunders.push_back(thunderObject);
		}
	}

	void PlayScene::CreateGale()
	{
		for (size_t i = 0; i < 20; i++)
		{
			gales.push_back(CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"GaleMaterial"));
			Animator* galesAnimator = gales[i]->AddComponent<Animator>();
			gales[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			std::shared_ptr<Texture> galesTexture = Resources::Find<Texture>(L"S_Gale");
			galesAnimator->Create(L"galeAni", galesTexture, Vector2::Zero, Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.01f);
			galesAnimator->Play(L"galeAni", true);
			gales[i]->Death();
			gales[i]->AddComponent<GaleScript>();
		}

	}

	void PlayScene::CreateScythe()
	{
		scythe = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"ScytheMaterial");
		scythe->SetLayerType(eLayerType::Skill);
		scythe->Death();
		scythe->AddComponent<ScytheScript>();
	}

	void PlayScene::CreateColliderChackObj()
	{
		colliderCheck = object::Instantiate<GameObject>(eLayerType::ColliderChack, this);
		colliderCheck->SetLayerType(eLayerType::ColliderChack);
		Transform* checkTr = colliderCheck->GetComponent<Transform>();
		checkTr->SetPosition(Vector3::Zero);
		checkTr->SetScale(Vector3::One);
		Collider2D* checkCollider = colliderCheck->AddComponent<Collider2D>();
		checkCollider->SetType(eColliderType::Rect);
		checkCollider->SetType(eColliderType::Rect);
		checkCollider->SetSize(Vector2(5.0f, 5.0f));
		colliderCheck->AddComponent<ColliderCheckScript>();
	}

	void PlayScene::CreateSpear()
	{
		for (size_t i = 0; i < 2; i++)
		{
			GameObject* spear = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"SpearMaterial");
			spear->SetLayerType(eLayerType::Skill);
			Collider2D* spearCollider = spear->GetComponent<Collider2D>();
			spearCollider->SetSize(Vector2(0.5f, 1.0f));
			spear->Death();
			spears.push_back(spear);
		}
		spears[0]->AddComponent<SpearScript>(3);
		spears[1]->AddComponent<SpearScript>(0);
	}

	void PlayScene::CreateThunderBug()
	{
		for (size_t i = 0; i < 2; i++)
		{
			GameObject* thunderBug = CreateSkillObject(eLayerType::None, L"ThunderBugMaterial");
			thunderBug->SetLayerType(eLayerType::None);
			thunderBug->Death();
			thunderBugs.push_back(thunderBug);
			Animator* bugAnimator = thunderBug->AddComponent<Animator>();
			std::shared_ptr<Texture> bugTexture = Resources::Find<Texture>(L"S_ThunderBug");
			bugAnimator->Create(L"BugIdle", bugTexture, Vector2::Zero, Vector2(16.0f, 16.0f), Vector2::Zero, 6, 0.1f);
			bugAnimator->Create(L"BugAttack", bugTexture, Vector2(0, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 3, 0.1f);
			bugAnimator->Play(L"BugIdle", true);

		}
		thunderBugs[0]->AddComponent<ThunderBugScript>(5);
		thunderBugs[1]->AddComponent<ThunderBugScript>(2);
	}

	void PlayScene::CreateIcicle()
	{
		for (size_t i = 0; i < 100; i++)
		{
			GameObject* icicle = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"IcicleMaterial");
			icicle->SetLayerType(eLayerType::Skill);
			icicle->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.3f, 1.0f));
			Collider2D* icicleCollider = icicle->GetComponent<Collider2D>();
			icicle->AddComponent<IcicleScript>();
			icicle->Death();
			icicles.push_back(icicle);
		}
	}

	void PlayScene::CreateExpMarble()
	{
		for (size_t i = 0; i < 100; i++)
		{
			GameObject* expObj = object::Instantiate<GameObject>(eLayerType::ExpMarble, this);
			expObj->SetLayerType(eLayerType::ExpMarble);
			expObj->GetComponent<Transform>()->SetPosition(Vector3(-5.0f, 1.0f, 0.0f));
			expObj->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.0f));
			expObj->AddComponent<Collider2D>();
			expObj->GetComponent<Collider2D>()->SetType(eColliderType::Rect);
			SpriteRenderer* expRender = expObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> expMaterial = Resources::Find<Material>(L"ExpObjectMaterial");
			expRender->SetMaterial(expMaterial);
			std::shared_ptr<Mesh> expMesh = Resources::Find<Mesh>(L"RectMesh");
			expRender->SetMesh(expMesh);
			expObj->AddComponent<ExpMarbleObject>();
			expObj->Death();
			expMarbles.push_back(expObj);
		}
		expMarbles[0]->Life();
	}

	void PlayScene::CreateGameManagers()
	{
		levelManager = object::Instantiate<GameObject>(eLayerType::None, this);
		levelManager->AddComponent<PlayerLevelScript>();

		skillManager = object::Instantiate<GameObject>(eLayerType::None, this);
		skillManager->AddComponent<SkillManager>();

		upgradeobj = object::Instantiate<GameObject>(eLayerType::None, this);
		upgradeobj->AddComponent<UpgradeScript>();
	}

	void PlayScene::CreateHpUIobj(GameObject* parent)
	{
		for (size_t i = 0; i < 10; i++)
		{
			GameObject* hpObject = object::Instantiate<GameObject>(eLayerType::UI, this);
			hpObject->SetLayerType(eLayerType::UI);
			hpObject->GetComponent<Transform>()->SetPosition(Vector3(-10.0f + (float)i, 5.2f, 10.0f));
			hpObject->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			hpObject->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
			SpriteRenderer* render = hpObject->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> hpMaterial = Resources::Find<Material>(L"HpMaterial");
			render->SetMaterial(hpMaterial);
			std::shared_ptr<Mesh> hpMesh = Resources::Find<Mesh>(L"RectMesh");
			render->SetMesh(hpMesh);
			Animator* uiAnimator = hpObject->AddComponent<Animator>();
			std::shared_ptr<Texture> hpTexture = Resources::Find<Texture>(L"HPHeart");
			uiAnimator->Create(L"heartbeat", hpTexture, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.1f);
			uiAnimator->Create(L"heartArrest", hpTexture, Vector2(96.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 100.0f);
			uiAnimator->Play(L"heartbeat", true);
			hpObject->Death();
			hpObjects.push_back(hpObject);
		}
	}

	void PlayScene::CreateAbilityIcon(GameObject* parent)
	{
		for (size_t i = 0; i < 100; i++)
		{
			const std::wstring name = L"Icon_Ability_" + std::to_wstring(i) + L"Material";
			CreateSkillIcon(name, parent, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		}
	}

	void PlayScene::CreateLevelUpEffect()
	{
		levelUPEffectObj = object::Instantiate<GameObject>(eLayerType::Skill_Buff, this);
		SpriteRenderer* levelUPEffectRender = levelUPEffectObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> levelUPMaterial = Resources::Find<Material>(L"LevelUPEffectMaterial");
		levelUPEffectRender->SetMaterial(levelUPMaterial);
		std::shared_ptr<Mesh> levelUPEffectMesh = Resources::Find<Mesh>(L"RectMesh");
		levelUPEffectRender->SetMesh(levelUPEffectMesh);
		Animator* levelupAniamtor = levelUPEffectObj->AddComponent<Animator>();
		std::shared_ptr<Texture> levelUPTexture = Resources::Find<Texture>(L"LevelUP");
		levelupAniamtor->Create(L"LevelUPAni", levelUPTexture, Vector2::Zero, Vector2(96.0f, 1110.0f), Vector2::Zero, 9, 0.1f);
		levelUPEffectObj->Death();
		levelUPEffectObj->AddComponent<LevelUPEffectScript>();
	}

	void PlayScene::CreateUIPanal(GameObject* parent,Vector3 pos ,Vector3 scale)
	{
		GameObject* uiPanal = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiPanal->SetLayerType(eLayerType::UI);
		uiPanal->GetComponent<Transform>()->SetPosition(pos);
		uiPanal->GetComponent<Transform>()->SetScale(scale);
		uiPanal->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		SpriteRenderer* panalRender = uiPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> panalMaterial = Resources::Find<Material>(L"PanalMaterial");
		panalRender->SetMaterial(panalMaterial);
		std::shared_ptr<Mesh> panalMesh = Resources::Find<Mesh>(L"RectMesh");
		panalRender->SetMesh(panalMesh);

		uiObjects.push_back(uiPanal);
	}

	void PlayScene::CreateUILeader(const std::wstring& key,GameObject* parent, Vector3 pos, Vector3 scale)
	{
		GameObject* uiLeader = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiLeader->SetLayerType(eLayerType::UI);
		uiLeader->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		uiLeader->GetComponent<Transform>()->SetPosition(pos);
		uiLeader->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* leaderRender = uiLeader->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> leaderMaterial = Resources::Find<Material>(key);
		leaderRender->SetMaterial(leaderMaterial);
		std::shared_ptr<Mesh> leaderMesh = Resources::Find<Mesh>(L"RectMesh");
		leaderRender->SetMesh(leaderMesh);

		uiObjects.push_back(uiLeader);
	}

	void PlayScene::CreatePowerUpFrame(GameObject* parent, Vector3 pos, Vector3 scale)
	{
		GameObject* frame = object::Instantiate<GameObject>(eLayerType::UI, this);
		frame->SetLayerType(eLayerType::UI);
		frame->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		frame->GetComponent<Transform>()->SetPosition(pos);
		frame->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* render = frame->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"PowerupFrameMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		GameObject* frameBG = object::Instantiate<GameObject>(eLayerType::UI, this);
		frameBG->SetLayerType(eLayerType::UI);
		frameBG->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		frameBG->GetComponent<Transform>()->SetPosition(pos - Vector3(0.0f,0.0f,-0.01f));
		frameBG->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* bgRender = frameBG->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bgMaterial = Resources::Find<Material>(L"PowerupIconBGMaterial");
		bgRender->SetMaterial(bgMaterial);
		std::shared_ptr<Mesh> bgMesh = Resources::Find<Mesh>(L"RectMesh");
		bgRender->SetMesh(bgMesh);


		uiObjects.push_back(frame);
		uiObjects.push_back(frameBG);
	}

	void PlayScene::CreateSkillUI(GameObject* parent)
	{
		CreateUIPanal(parent, Vector3(0.0f, 0.0f, 1.0f), Vector3(1.2f, 0.4f, 1.0f));
		CreateUIPanal(parent, Vector3(0.0f, -0.3f, 1.0f), Vector3(0.8f, 0.1f, 1.0f));
		CreateUIPanal(parent, Vector3(0.0f, -0.42f, 1.0f), Vector3(0.8f, 0.1f, 1.0f));
		CreateUILeader(L"LeftDownLeaderMaterial", parent, Vector3(0.3f, 0.08f, 1.0f), Vector3(0.05f, 0.05f, 1.0f));
		CreateUILeader(L"RightDownLeaderMaterial", parent, Vector3(0.5f, 0.08f, 1.0f), Vector3(0.05f, 0.05f, 1.0f));
		CreateUILeader(L"DownRightLeaderMaterial", parent, Vector3(0.3f, -0.12f, 1.0f), Vector3(0.05f, 0.05f, 1.0f));
		CreateUILeader(L"DownLeftLeaderMaterial", parent, Vector3(0.5f, -0.12f, 1.0f), Vector3(0.05f, 0.05f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(0.28f, -0.02f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(0.52f, -0.02f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(0.4f, 0.08f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(0.4f, -0.12f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));

		CreatePowerUpFrame(parent, Vector3(-0.3f, 0.26f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(-0.15f, 0.26f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(0.0f, 0.26f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(0.15f, 0.26f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
		CreatePowerUpFrame(parent, Vector3(0.3f, 0.26f, 1.0f), Vector3(0.08f, 0.08f, 1.0f));
	}

	void PlayScene::CreateSkillIcon(const std::wstring& key, GameObject* parent, Vector3 pos, Vector3 scale)
	{
		GameObject* iconObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		iconObj->SetLayerType(eLayerType::UI);
		iconObj->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		iconObj->GetComponent<Transform>()->SetPosition(pos);
		iconObj->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* iconRender = iconObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> iconMaterial = Resources::Find<Material>(key);
		iconRender->SetMaterial(iconMaterial);
		std::shared_ptr<Mesh> iconMesh = Resources::Find<Mesh>(L"RectMesh");
		iconRender->SetMesh(iconMesh);

		iconObj->Death();
		iconObjects.push_back(iconObj);
	}

	void PlayScene::CreateCollider(auto* object, eColliderType type,Vector2 size)
	{
		Collider2D* collider = object->AddComponent<Collider2D>();
		collider->SetType(type);
		collider->SetSize(size);
	}

	GameObject* PlayScene::CreateSkillObject(eColliderType type, eLayerType layertype, const std::wstring& materialKey)
	{
		GameObject* object = object::Instantiate<GameObject>(eLayerType::Skill, this);
		object->SetLayerType(eLayerType::Skill);
		object->GetComponent<Transform>()->SetScale(Vector3::One);
		object->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		Collider2D* collider = object->AddComponent<Collider2D>();
		collider->SetType(type);
		SpriteRenderer* render = object->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(materialKey);
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		return object;
	}

	GameObject* PlayScene::CreateSkillObject(eLayerType layertype, const std::wstring& materialKey)
	{
		GameObject* object = object::Instantiate<GameObject>(eLayerType::Skill, this);
		object->SetLayerType(eLayerType::Skill);
		object->GetComponent<Transform>()->SetScale(Vector3::One);
		object->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		SpriteRenderer* render = object->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(materialKey);
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		return object;
	}

	void PlayScene::M_DefaultTr(auto* object,Vector3 pos,Vector3 scale)
	{
		Transform* mboomerTr = object->GetComponent<Transform>();
		mboomerTr->SetPosition(pos);
		mboomerTr->SetScale(scale);
	}

	void PlayScene::ALLSKILL()
	{
		upgradeobj->GetScript<UpgradeScript>()->TakeAim();
		upgradeobj->GetScript<UpgradeScript>()->Penteration();
		upgradeobj->GetScript<UpgradeScript>()->Smiper();
		upgradeobj->GetScript<UpgradeScript>()->Assassin(); 
		upgradeobj->GetScript<UpgradeScript>()->PowerShot();
		upgradeobj->GetScript<UpgradeScript>()->Splinter(); 
		upgradeobj->GetScript<UpgradeScript>()->BigShot();
		upgradeobj->GetScript<UpgradeScript>()->ReaperRounds();
		upgradeobj->GetScript<UpgradeScript>()->RapidFire(); 
		upgradeobj->GetScript<UpgradeScript>()->LightBullets();
		upgradeobj->GetScript<UpgradeScript>()->RubberBullets();
		upgradeobj->GetScript<UpgradeScript>()->Siege(); 
		upgradeobj->GetScript<UpgradeScript>()->DoubleShot();
		upgradeobj->GetScript<UpgradeScript>()->FanFire(); 
		upgradeobj->GetScript<UpgradeScript>()->SplitFire();
		upgradeobj->GetScript<UpgradeScript>()->Fusillade(); 
		upgradeobj->GetScript<UpgradeScript>()->QuickHands(); 
		upgradeobj->GetScript<UpgradeScript>()->ArmedAndReady();
		upgradeobj->GetScript<UpgradeScript>()->FreshClip();
		upgradeobj->GetScript<UpgradeScript>()->KillClip();
		upgradeobj->GetScript<UpgradeScript>()->ElectroMage(); 
		upgradeobj->GetScript<UpgradeScript>()->ElectroBug(); 
		upgradeobj->GetScript<UpgradeScript>()->Energized(); 
		upgradeobj->GetScript<UpgradeScript>()->ElectroMastery();
		upgradeobj->GetScript<UpgradeScript>()->FrostMage();
		upgradeobj->GetScript<UpgradeScript>()->Frostbite(); 
		upgradeobj->GetScript<UpgradeScript>()->IceShard(); 
		upgradeobj->GetScript<UpgradeScript>()->Shatter(); 
		upgradeobj->GetScript<UpgradeScript>()->PyroMage(); 
		upgradeobj->GetScript<UpgradeScript>()->FireStarter();
		upgradeobj->GetScript<UpgradeScript>()->IntenseBurn(); 
		upgradeobj->GetScript<UpgradeScript>()->SoothingWarmth();
		upgradeobj->GetScript<UpgradeScript>()->DarkArts();
		upgradeobj->GetScript<UpgradeScript>()->Doom(); 
		upgradeobj->GetScript<UpgradeScript>()->Wither(); 
		upgradeobj->GetScript<UpgradeScript>()->Ritual(); 
		upgradeobj->GetScript<UpgradeScript>()->HolyAttack(); 
		upgradeobj->GetScript<UpgradeScript>()->HolyMight();
		upgradeobj->GetScript<UpgradeScript>()->Justice(); 
		upgradeobj->GetScript<UpgradeScript>()->Angelic(); 
		upgradeobj->GetScript<UpgradeScript>()->AeroMagic(); 
		upgradeobj->GetScript<UpgradeScript>()->WindBorne();
		upgradeobj->GetScript<UpgradeScript>()->EyeoftheStorm();
		upgradeobj->GetScript<UpgradeScript>()->AeroMastery();
		upgradeobj->GetScript<UpgradeScript>()->Vitality(); 
		upgradeobj->GetScript<UpgradeScript>()->AngerPoint(); 
		upgradeobj->GetScript<UpgradeScript>()->Giant(); 
		upgradeobj->GetScript<UpgradeScript>()->Regeneration();
		upgradeobj->GetScript<UpgradeScript>()->HolyShield(); 
		upgradeobj->GetScript<UpgradeScript>()->DivineBlessing();
		upgradeobj->GetScript<UpgradeScript>()->DivineWrath(); 
		upgradeobj->GetScript<UpgradeScript>()->StalwartShield();
		upgradeobj->GetScript<UpgradeScript>()->Haste(); 
		upgradeobj->GetScript<UpgradeScript>()->BlazingSpeed();
		upgradeobj->GetScript<UpgradeScript>()->RunGun(); 
		upgradeobj->GetScript<UpgradeScript>()->IntheWind();
		upgradeobj->GetScript<UpgradeScript>()->Glare(); 
		upgradeobj->GetScript<UpgradeScript>()->IntenseGlare();
		upgradeobj->GetScript<UpgradeScript>()->SightMagic(); 
		upgradeobj->GetScript<UpgradeScript>()->Saccade(); 
		upgradeobj->GetScript<UpgradeScript>()->Evasive(); 
		upgradeobj->GetScript<UpgradeScript>()->Nimble(); 
		upgradeobj->GetScript<UpgradeScript>()->Tiny(); 
		upgradeobj->GetScript<UpgradeScript>()->Reflex(); 
		upgradeobj->GetScript<UpgradeScript>()->DragonEgg(); 
		upgradeobj->GetScript<UpgradeScript>()->AgedDragon(); 
		upgradeobj->GetScript<UpgradeScript>()->TrainedDragon();
		upgradeobj->GetScript<UpgradeScript>()->DragonBond(); 
		upgradeobj->GetScript<UpgradeScript>()->GhostFriend(); 
		upgradeobj->GetScript<UpgradeScript>()->EnergeticFriends();
		upgradeobj->GetScript<UpgradeScript>()->InSync(); 
		upgradeobj->GetScript<UpgradeScript>()->VengefulGhost();
		upgradeobj->GetScript<UpgradeScript>()->MagicLens();
		upgradeobj->GetScript<UpgradeScript>()->IgnitingLens();
		upgradeobj->GetScript<UpgradeScript>()->Refraction(); 
		upgradeobj->GetScript<UpgradeScript>()->FocalPoint(); 
		upgradeobj->GetScript<UpgradeScript>()->MagicSpear(); 
		upgradeobj->GetScript<UpgradeScript>()->HolySpear(); 
		upgradeobj->GetScript<UpgradeScript>()->SoulDrain(); 
		upgradeobj->GetScript<UpgradeScript>()->SoulKnight(); 
		upgradeobj->GetScript<UpgradeScript>()->MagicScythe(); 
		upgradeobj->GetScript<UpgradeScript>()->Shadowblade(); 
		upgradeobj->GetScript<UpgradeScript>()->Windcutter(); 
		upgradeobj->GetScript<UpgradeScript>()->ScytheMastery();
	}

	glm::vec2 PlayScene::ScreenToCamera(const glm::vec2& screenCoord, const glm::mat4& viewProjectionMatrix, int screenWidth, int screenHeight)
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

	void PlayScene::LevelUPUI()
	{
		//levelUPEffectObj->Life();
		//levelUPEffectObj->GetComponent<Animator>()->Play(L"LevelUPAni", false);

		int random[6];
		int i, j;

		srand((unsigned)time(NULL));

		for (i = 0; i < 5; i++)
		{
			random[i] = (rand() % 23) + 1;

			for (j = 0; j < i; j++)
			{
				if (random[i] == random[j]) i--;
			}
		}

		for (size_t i = 0; i < 5; i++)
		{
			GetIcon()[random[i] * 4]->GetComponent<Transform>()->SetPosition(Vector3(-0.3f + (i * 0.15f), 0.26f, 1.0f));
			GetIcon()[random[i] * 4]->Life();
		}


		SetStop();


		for (size_t i = 0; i < uiObjects.size(); i++)
		{
			uiObjects[i]->Life();
		}







		uiOn = true;
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
}
