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
#include "yaMuzzleFlashScript.h"
#include "yaReloadBarScript.h"
#include "yaStageOneTileManager.h"
#include "yaMonsterFactoryScript.h"
#include "yaCursorUIScript.h"
#include "yaAudioListener.h"
#include "yaAudioSource.h"
#include "yaHubNigguratScript.h"
#include "yaBommerSoundEffectScript.h"
#include "yaSoundObjectScript.h"
#include "yaTreePosScript.h"
#include "yaMonsterEyeLightScript.h"
#include "yaFireLightScript.h"

#include <random>

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
		, randomValue{}
		, abliltyNumber(0)
		, click{}
		, bReroll(false)
		, uiOns{}
	{
	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initalize()
	{
		Resources::Load<AudioClip>(L"LightningSound", L"..\\Resources\\Sound\\Lightning Spelll.wav");
		Resources::Load<AudioClip>(L"MonsterHit", L"..\\Resources\\Sound\\MonsterHit.wav");
		Resources::Load<AudioClip>(L"Footsteps_Casual_Grass_01", L"..\\Resources\\Sound\\Footsteps_Casual_Grass_01.wav");
		Resources::Load<AudioClip>(L"PlayerHit", L"..\\Resources\\Sound\\PlayerHit.wav");

		//paint Shader
		//std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//paintShader->SetTarget(Resources::Find<Texture>(L"PaintTexture"));
		//paintShader->OnExcute();

		//post process object


		GameObject* cursorObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		SpriteRenderer* cursorRender = cursorObject->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> cursorMat = Resources::Find<Material>(L"CursorMaterial");
		cursorRender->SetMaterial(cursorMat);
		std::shared_ptr<Mesh> cursorMesh = Resources::Find<Mesh>(L"RectMesh");
		cursorRender->SetMesh(cursorMesh);
		cursorObject->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cursorObject->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.0f));
		cursorObject->AddComponent<CursorUIScript>();

		{
			playerPointLight = object::Instantiate<GameObject>(eLayerType::UI,this);
			playerPointLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			Light* lightComp = playerPointLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(3.0f);
			lightComp->SetDiffuse(Vector4(0.25f, 0.25f, 0.25f, 1.0f));

			playerSubPointLight = object::Instantiate<GameObject>(eLayerType::UI, this);
			playerSubPointLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			Light* sublightComp = playerSubPointLight->AddComponent<Light>();
			sublightComp->SetType(eLightType::Point);
			sublightComp->SetRadius(6.0f);
			sublightComp->SetDiffuse(Vector4(0.25f, 0.25f, 0.25f, 1.0f));



			directionalLight = object::Instantiate<GameObject>(eLayerType::UI, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			Light* directLightComp = directionalLight->AddComponent<Light>();
			//directLightComp->SetAmbient(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			directLightComp->SetType(eLightType::Directional);
			directLightComp->SetRadius(1.0f);
			//directLightComp->SetDiffuse(Vector4(0.047f, 0.015f, 0.168f, -0.5f));
			directLightComp->SetDiffuse(Vector4(-0.65f, -0.65f, -0.65f, 1.0f));
		}


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

		Resources::Load<AudioClip>(L"StageBGM", L"..\\Resources\\Sound\\WastelandCombatLoop.wav");


		// Main Camera Game Object
		pSceneCamera = object::Instantiate<GameObject>(eLayerType::Camera,this);
		pSceneCamera->SetName(L"PSMCamera");
		Camera* cameraComp = pSceneCamera->AddComponent<Camera>();
		pSceneCamera->AddComponent<AudioListener>();
		pSceneCamera->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"StageBGM"));
		pSceneCamera->GetComponent<AudioSource>()->SetLoop(true);
		Transform* mainCameraTr = pSceneCamera->GetComponent<Transform>();
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
			pCollider->SetSize(Vector2(0.15f, 0.15f));
			SpriteRenderer* pMr = playerObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			pMr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> pMesh = Resources::Find<Mesh>(L"RectMesh");
			pMr->SetMesh(pMesh);
			playerObj->AddComponent<Animator>();
			playerObj->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"PlayerHit"));

			switch (i)
			{
			case 0:
				playerObj->AddComponent<PlayerScript>(i, 4);
				break;
			case 1:
				playerObj->AddComponent<PlayerScript>(i, 4);
				break;
			case 2:
				playerObj->AddComponent<PlayerScript>(i, 4);
				break;
			case 3:
				playerObj->AddComponent<PlayerScript>(i, 4);
				break;
			case 4:
				playerObj->AddComponent<PlayerScript>(i, 4);
				break;
			}
			playerObj->GetScript<PlayerScript>()->Reset();
			playerObj->Death();
			players.push_back(playerObj);
		}

		Transform* playerTr;
		playerTr = players[0]->GetComponent<Transform>();

		//post process object
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::PostProcess);
			obj->SetName(L"PostProcessGameObject");
			playerTr = obj->GetComponent<Transform>();
			playerTr->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
			playerTr->SetScale(Vector3(4.0f, 4.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetSize(Vector2(1.0f, 0.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PostProcessMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}


		CreateWeapon();
		CreateFirePos();

		// Monster
		{
			CreateBrainMonster();
			CreateEyeMonster();
			CreateBommerMonster();
			CreateBossMonster();

			CreateTreeMonster(Vector3(-13.0f,8.0f,0.0f));
			CreateTreeMonster(Vector3(15.0f, 7.8f, 0.0f));
			CreateTreeMonster(Vector3(-11.0f, 0.2f, 0.0f));
			CreateTreeMonster(Vector3(12.0f, -0.7f, 0.0f));
			CreateTreeMonster(Vector3(-10.0f, -8.7f, 0.0f));
			CreateTreeMonster(Vector3(9.0f, -9.5f, 0.0f));
		}

		Resources::Load<AudioClip>(L"MonsterHit", L"..\\Resources\\Sound\\MonsterHit.wav");

		for (size_t i = 0; i < 1000; i++)
		{
			//총알 오브젝트 생성
			Bullet* bulletobj = object::Instantiate<Bullet>(eLayerType::Bullet, this);
			bullets.push_back(bulletobj);
			bullets[i]->SetLayerType(eLayerType::Bullet);
			bullets[i]->SetName(L"Bullet" + i);
			bullets[i]->GetComponent<Transform>()->SetParent(pWeapon->GetComponent<Transform>());
			bullets[i]->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			bullets[i]->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			bullets[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));

			//콜라이더 생성
			Collider2D* bulletColloder = bullets[i]->AddComponent<Collider2D>();
			bulletColloder->SetType(eColliderType::Rect);
			bulletColloder->SetSize(Vector2(0.1f, 0.1f));

			//스프라이트 생성
			SpriteRenderer* render = bullets[i]->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bulletMaterial = Resources::Find<Material>(L"BulletMaterial");
			render->SetMaterial(bulletMaterial);
			std::shared_ptr<Mesh> bulletMesh = Resources::Find<Mesh>(L"RectMesh");
			render->SetMesh(bulletMesh);

			//충돌시 재생되는 애니메이션 생성
			Animator* bulletAnimator = bullets[i]->AddComponent<Animator>();
			std::shared_ptr<Texture> bulletTexture = Resources::Find<Texture>(L"BulletTexture");
			bulletAnimator->Create(L"BulletAni", bulletTexture, Vector2(0.0f, 0.0f),
				Vector2(16.0f, 14.0f), Vector2::Zero, 2, 0.0f);
			bulletAnimator->Play(L"BulletAni", true);
			bulletAnimator->ResetStop();
			bullets[i]->AddComponent<BulletScript>();

			//MonsterHit 오디오
			bullets[i]->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"MonsterHit"));
			pWeapon->GetScript<WeaponScript>()->SetBullets(bullets[i]->GetComponent<Transform>());
		}


		// SKill
		CreateThunder();

		pulseObject = object::Instantiate<GameObject>(eLayerType::Skill, this);
		pulseObject->SetLayerType(eLayerType::Skill);

		CreateGale();
		CreateHolyShiled();


		CreateLevelUpEffect();
		CreateFreezes();
		FreezeAddToMonster();
		CreateCurses();
		CurseAddToMonster();
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
		CreateHpUIobj();
		CreateSkillUI(cameraUIObj);
		CreateAbilityIcon(/*cameraUIObj*/);
		CreateAmmoIcon(cameraUIObj);
		CreateExpBar(cameraUIObj);
		CreateGameManagers();
		CreateExitUI();
		CreateEndUI();

		stageOneMapManager = object::Instantiate<GameObject>(eLayerType::None, this);
		stageOneMapManager->AddComponent<StageOneTileManager>();

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				CreateStageOneTile(Vector3(-40.0f + 40.0f * j, 40.0f - 40.0f * i, 1.0f));
			}
		}

		monsterFactoryManager = object::Instantiate<GameObject>(eLayerType::None, this);
		monsterFactoryManager->AddComponent<MonsterFactoryScript>();

		//Tile_0Material
		//Particle
		//GameObject* particle = object::Instantiate<Player>(eLayerType::Particle, this);
		//particle->SetName(L"Particle");
		//Transform* particleTr = particle->GetComponent<Transform>();
		//particleTr->SetPosition(Vector3::Zero);
		//particle->AddComponent<ParticleSystem>();
		//particleTr->SetParent(player->GetComponent<Transform>());


		for (size_t i = 0; i < 100; i++)
		{
			const std::wstring name = L"Icon_Ability_" + std::to_wstring(i) + L"Material";
			CreateSkillIcon(name, Vector3(0.0f, 0.0f, 9.0f), Vector3(0.54f, 0.54f, 1.0f));
		}

		for (size_t c = 0; c < 2; c++)
		{
			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					const std::wstring name = L"Time_" + std::to_wstring(j) + L"Material";
					CreatetimerObject(name, Vector3(9.1f +(((c*2)+i) * -0.5f) + (c * -0.1f), 4.9f, 9.0f), Vector3(0.4f, 0.4f, 1.0f));
				}
			}
		}
		CreatetimerObject(L"Time_spotMaterial", Vector3(8.3f , 4.9f, 9.0f), Vector3(0.4f, 0.4f, 1.0f));

		timerObj[0]->Life();
		timerObj[10]->Life();
		timerObj[20]->Life();
		timerObj[30]->Life();
		timerObj[40]->Life();



		CreateLevelUI(L"LevelTextMaterial", Vector3(0.0f, 5.42f, 9.0f), Vector3(0.8f, 0.3f, 1.0f));
		

		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				const std::wstring name = L"Time_" + std::to_wstring(j) + L"Material";
				CreateLevelText(name, Vector3(1.2f + (- 0.28f * i), 5.40f, 9.0f), Vector3(0.28f, 0.3f, 1.0f));
			}
		}
		levelTexts[1]->Life();

		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				const std::wstring name = L"BulletText_" + std::to_wstring(j) + L"Material";
				CreateBulletText(name, Vector3(-6.0f + (-0.35f * i), 3.8f, 9.0f), Vector3(0.3f, 0.3f, 1.0f));
			}
		}
		bulletTexts[6]->Life();
		bulletTexts[10]->Life();

		GameObject* uiSlash = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiSlash->SetLayerType(eLayerType::UI);
		uiSlash->GetComponent<Transform>()->SetPosition(Vector3(-5.5f, 3.8f, 9.0f));
		uiSlash->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		SpriteRenderer* uiSlashRender = uiSlash->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> uiSlashtMat = Resources::Find<Material>(L"BulletUISlashMaterial");
		uiSlashRender->SetMaterial(uiSlashtMat);
		std::shared_ptr<Mesh> uiSlashMesh = Resources::Find<Mesh>(L"RectMesh");
		uiSlashRender->SetMesh(uiSlashMesh);

		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				const std::wstring name = L"BulletText_" + std::to_wstring(j) + L"Material";
				CreateBulletText(name, Vector3(-4.5f + (-0.35f * i), 3.8f, 9.0f), Vector3(0.3f, 0.3f, 1.0f));
			}
		}
		bulletTexts[26]->Life();
		bulletTexts[30]->Life();



		Resources::Load<AudioClip>(L"GetExpSound", L"..\\Resources\\Sound\\GetExpSound.wav");
		Resources::Load<AudioClip>(L"ReloadSound", L"..\\Resources\\Sound\\Weapon_Shotgun_Reload.wav");
		Resources::Load<AudioClip>(L"ButMousePos", L"..\\Resources\\Sound\\ButMousePos.wav");
		Resources::Load<AudioClip>(L"UIClick", L"..\\Resources\\Sound\\UIClick.wav");
		Resources::Load<AudioClip>(L"LevelUPSound", L"..\\Resources\\Sound\\LevelUPSound.wav");
		Resources::Load<AudioClip>(L"LevelUPUIOpen", L"..\\Resources\\Sound\\LevelUPUIOpen.wav");
		Resources::Load<AudioClip>(L"Shield_Magic", L"..\\Resources\\Sound\\Shield_Magic.wav");
		Resources::Load<AudioClip>(L"YouWin", L"..\\Resources\\Sound\\YouWin.wav");
		Resources::Load<AudioClip>(L"YouLose", L"..\\Resources\\Sound\\YouLose.wav");
		Resources::Load<AudioClip>(L"Big_Weapon_Whoosh", L"..\\Resources\\Sound\\Big_Weapon_Whoosh.wav");
		Resources::Load<AudioClip>(L"BossCharge", L"..\\Resources\\Sound\\BossCharge.wav");

		CreateSoundobject(L"GetExpSound");
		CreateSoundobject(L"ReloadSound");
		CreateSoundobject(L"ButMousePos");
		CreateSoundobject(L"UIClick");
		CreateSoundobject(L"LevelUPSound");
		CreateSoundobject(L"LevelUPUIOpen");
		CreateSoundobject(L"Footsteps_Casual_Grass_01");
		CreateSoundobject(L"Shield_Magic");
		CreateSoundobject(L"YouWin");
		CreateSoundobject(L"YouLose");
		CreateSoundobject(L"Big_Weapon_Whoosh");
		CreateSoundobject(L"BossCharge");
		CreateBrainEyeEffect();
		CreateBommerEyeEffect();
		CreateEyeMonsterEffect();
		CreateBossEffect();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterBoomer, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Tree, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Explosion, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::ExpMarble, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Explosion, true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterBoomer, eLayerType::MonsterBoomer, true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterBoomer, eLayerType::Explosion, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Boss, eLayerType::Explosion, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::MonsterBoomer, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Boss, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill, eLayerType::MonsterBoomer, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill, eLayerType::Boss, true);
		CollisionManager::CollisionLayerCheck(eLayerType::ColliderChack, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::ColliderChack, eLayerType::MonsterBoomer, true);
		CollisionManager::CollisionLayerCheck(eLayerType::ColliderChack, eLayerType::Boss, true);
		CollisionManager::CollisionLayerCheck(eLayerType::ColliderChack, eLayerType::ExpMarble, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill_Smite, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill_Smite, eLayerType::MonsterBoomer, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill_Smite, eLayerType::Boss, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill, eLayerType::Bullet, true);
		Scene::Initalize();
	}


	void PlayScene::Update()
	{
		stageOneMapManager->GetScript<StageOneTileManager>()->SetCurrentPos(player->GetComponent<Transform>()->GetPosition());

		playerPointLight->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
		playerSubPointLight->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());

		for (size_t i = 0; i < soundObj.size(); i++)
		{
			soundObj[i]->GetComponent<Transform>()->SetPosition(pSceneCamera->GetComponent<Transform>()->GetPosition());
		}

		if (uiOns[0])
		{
			Vector3 mousePos = UiMousePos();
			UiButton(mousePos);
		}
		else if (uiOns[1])
		{
			Vector3 mousePos = UiMousePos();
			EscUIButton(mousePos);
		}
		else if (uiOns[2])
		{
			Vector3 mousePos = UiMousePos();
			EndUIButton(mousePos);
		}

		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			EscUIOn();
		}

		if (Input::GetKeyDown(eKeyCode::R))
		{
			SurvivalEndUIOn();
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			DeadEndUIOn();
		}


		//Transform* tr = pSceneCamera->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();

		Scene::Update();

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
		pSceneCamera->GetComponent<AudioSource>()->Play();
	}

	void PlayScene::OnExit()
	{
		pSceneCamera->GetComponent<AudioSource>()->Stop();
	}

	void PlayScene::ChoosePlayers(int num)
	{
		players[num]->Life();
		player = players[num];

		pSceneCamera->GetScript<CameraScript>()->SetTarget(player);
		playerPointLight->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

		Transform* weaponTr = pWeapon->GetComponent<Transform>();
		weaponTr->SetParent(player->GetComponent<Transform>());
		weaponTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		weaponTr->SetPosition(Vector3(0.3f, 0.02f, 0.0f));

		levelUPEffectObj->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());
		levelUPEffectObj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.7f, 0.0f));
		levelUPEffectObj->GetComponent<Transform>()->SetScale(Vector3(2.0f, 5.0f, 1.0f));

		holyShield->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());
		muzzleFlash->GetScript<MuzzleFlashScript>()->GetPlayer();
		muzzleFlash->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

		bulletFireLight->GetScript<FireLightScript>()->GetPlayer();
		bulletFireLight->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

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
		for (size_t i = 0; i < mBigBoomerMonsters.size(); i++)
		{
			mBigBoomerMonsters[i]->GetScript<MonsterScript>()->SetPlayer(players[num]);
		}
		for (size_t i = 0; i < mBossMonsters.size(); i++)
		{
			mBossMonsters[i]->GetScript<MonsterScript>()->SetPlayer(players[num]);
		}
	}

	void PlayScene::CreatePlayer()
	{

	}

	void PlayScene::CreateWeapon()
	{
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
		weaponAni->Create(L"RevolverLeft", revolverTexture, Vector2(0.0f, 15.0f), Vector2(16.0f, 15.0f), Vector2::Zero, 5, 0.0f);
		weaponAni->Play(L"Revolver", true);
		pWeapon->AddComponent<WeaponScript>();


		Resources::Load<AudioClip>(L"FireSound", L"..\\Resources\\Sound\\single_shot.wav");

		muzzleFlash = object::Instantiate<Weapon>(eLayerType::Particle, this);
		muzzleFlash->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		muzzleFlash->SetLayerType(eLayerType::Particle);
		SpriteRenderer* muzzleRender = muzzleFlash->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> muzzleMaterial = Resources::Find<Material>(L"MuzzleFlashMaterial");
		muzzleRender->SetMaterial(muzzleMaterial);
		std::shared_ptr<Mesh>  muzzleMesh = Resources::Find<Mesh>(L"RectMesh");
		muzzleRender->SetMesh(muzzleMesh);
		muzzleFlash->Death();
		muzzleFlash->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"FireSound"));
		muzzleFlash->AddComponent<MuzzleFlashScript>();


		bulletFireLight = object::Instantiate<GameObject>(eLayerType::UI, this);
		bulletFireLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		Light* fireLightComp = bulletFireLight->AddComponent<Light>();
		fireLightComp->SetType(eLightType::Point);
		fireLightComp->SetRadius(8.0f);
		fireLightComp->SetDiffuse(Vector4(0.25f, 0.25f, 0.25f, 1.0f));
		bulletFireLight->AddComponent<FireLightScript>();
		bulletFireLight->Death();
	}

	void PlayScene::CreateFirePos()
	{
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
	}

	void PlayScene::CreateBrainMonster()
	{
		for (size_t i = 0; i < 100; i++)
		{
			Monster* m_Brain = object::Instantiate<Monster>(eLayerType::Monster, this);
			m_Brain->SetLayerType(eLayerType::Monster);
			m_Brain->SetName(L"brain");
			M_DefaultTr(m_Brain, Vector3(-2.0f, 0.0f, 0.0f), Vector3(3.0f, 3.0f, 1.0f));
			CreateCollider(m_Brain, eColliderType::Rect, Vector2(0.5f, 0.5f));
			CreateSpriteRenderer(m_Brain, L"BrainMonsterMaterial");

			Animator* mAnimator = m_Brain->AddComponent<Animator>();
			std::shared_ptr<Texture> mTexture = Resources::Find<Texture>(L"BrainMonster");
			std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
			mAnimator->Create(L"m_Right", mTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
			mAnimator->Create(L"m_Left", mTexture, Vector2(0.0f, 64.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
		    mAnimator->Create(L"m_RightHit", mTexture, Vector2(0.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"m_LeftHit", mTexture, Vector2(0.0f, 192.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
			mAnimator->Play(L"m_Left", true);

			m_Brain->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"MonsterHit"));
			m_Brain->AddComponent<MonsterScript>(40,eLayerType::Monster);
			m_Brain->Death();
			mBrainMonsters.push_back(m_Brain);
		}


		//Monster* m_Brain = object::Instantiate<Monster>(eLayerType::Monster, this);
		//m_Brain->SetLayerType(eLayerType::Monster);
		//m_Brain->SetName(L"brain");
		//M_DefaultTr(m_Brain, Vector3(-2.0f, 0.0f, 0.0f), Vector3(3.0f, 3.0f, 1.0f));
		//CreateCollider(m_Brain, eColliderType::Rect, Vector2(0.5f, 0.5f));
		//CreateSpriteRenderer(m_Brain, L"BrainMonsterMaterial");

		//Animator* mAnimator = m_Brain->AddComponent<Animator>();
		//std::shared_ptr<Texture> mTexture = Resources::Find<Texture>(L"BrainMonster");
		//std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		//mAnimator->Create(L"m_Right", mTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
		//mAnimator->Create(L"m_Left", mTexture, Vector2(0.0f, 64.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.1f);
		//mAnimator->Create(L"m_RightHit", mTexture, Vector2(0.0f, 128.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		//mAnimator->Create(L"m_LeftHit", mTexture, Vector2(0.0f, 192.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
		//mAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		//mAnimator->Play(L"m_Left", true);

		//m_Brain->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"MonsterHit"));
		//m_Brain->AddComponent<MonsterScript>(10000000, eLayerType::Monster);
		//m_Brain->GetScript<MonsterScript>()->SetSpeed(0.0f);
		//mBrainMonsters.push_back(m_Brain);
	}

	void PlayScene::CreateBrainEyeEffect()
	{
		for (size_t i = 0; i < mBrainMonsters.size(); i++)
		{
			GameObject* eye = object::Instantiate<Monster>(eLayerType::None, this);
			eye->SetLayerType(eLayerType::None);
			eye->SetName(L"brainEye");
			eye->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			eye->GetComponent<Transform>()->SetParent(mBrainMonsters[i]->GetComponent<Transform>());
			eye->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			CreateSpriteRenderer(eye, L"BrainMonsterEyeMaterial");
			Animator* eyeAni = eye->AddComponent<Animator>();
			std::shared_ptr<Texture> m_EyeTexture = Resources::Find<Texture>(L"BrainMonsterEye");
			eyeAni->Create(L"m_Right", m_EyeTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 3, 0.1f);
			eyeAni->Create(L"m_Left", m_EyeTexture, Vector2(0.0f, 64.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 3, 0.1f);
			eyeAni->Play(L"m_Right", true);
			eye->AddComponent<MonsterEyeLightScript>(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			eye->Death();
			mBrainMonsterEyes.push_back(eye);
		}
	}

	void PlayScene::CreateTreeMonster(Vector3 pos)
	{
		Monster* m_tree = object::Instantiate<Monster>(eLayerType::Tree, this);
		m_tree->SetLayerType(eLayerType::Tree);
		m_tree->SetName(L"tree");
		M_DefaultTr(m_tree, pos, Vector3(3.0f, 3.0f, 1.0f));
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
		m_tree->AddComponent<TreePosScript>();
		mTreeMonsters.push_back(m_tree);
	}

	void PlayScene::CreateEyeMonster()
	{
		for (size_t i = 0; i < 100; i++)
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
			m_EyeAnimator->Create(L"m_RightHit", m_EyeTexture, Vector2(0.0f, 80.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 1, 0.1f);
			m_EyeAnimator->Create(L"m_LeftHit", m_EyeTexture, Vector2(0.0f, 120.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 1, 0.1f);
			m_EyeAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
			m_EyeAnimator->Play(L"m_Right", true);
			eyeMonster->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"MonsterHit"));
			eyeMonster->AddComponent<MonsterScript>(60,eLayerType::Monster);
			eyeMonster->Death();
			mEyeMonsters.push_back(eyeMonster);
		}
	}

	void PlayScene::CreateEyeMonsterEffect()
	{

		for (size_t i = 0; i < mEyeMonsters.size(); i++)
		{
			GameObject* eye = object::Instantiate<Monster>(eLayerType::None, this);
			eye->SetLayerType(eLayerType::None);
			eye->SetName(L"EyeMonsterEye");
			eye->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			eye->GetComponent<Transform>()->SetParent(mEyeMonsters[i]->GetComponent<Transform>());
			eye->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			CreateSpriteRenderer(eye, L"EyeMonsterEyeMaterial");
			Animator* eyeAni = eye->AddComponent<Animator>();
			std::shared_ptr<Texture> EyeMonsterEyeTex = Resources::Find<Texture>(L"EyeMonsterEye");
			eyeAni->Create(L"m_Right", EyeMonsterEyeTex, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 3, 0.1f);
			eyeAni->Create(L"m_Left", EyeMonsterEyeTex, Vector2(0.0f, 40.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 3, 0.1f);
			eyeAni->Play(L"m_Right", true);
			eye->AddComponent<MonsterEyeLightScript>(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			eye->Death();
			mEyeMonsterEyes.push_back(eye);
		}
	}

	void PlayScene::CreateBommerMonster()
	{
		Resources::Load<AudioClip>(L"BommerDeath", L"..\\Resources\\Sound\\Spell_Explosion_Magic_02.wav");

		for (size_t i = 0; i < 30; i++)
		{
			Monster* mBoomer = object::Instantiate<Monster>(eLayerType::MonsterBoomer, this);
			mBoomer->SetLayerType(eLayerType::MonsterBoomer);
			M_DefaultTr(mBoomer, Vector3(4.0f, 0.0f, 0.0f), Vector3(3.0f, 3.0f, 1.0f));
			CreateCollider(mBoomer, eColliderType::Rect, Vector2(0.5f, 0.5f));
			CreateSpriteRenderer(mBoomer, L"BoomerMaterial");
			Animator* boomerAnimator = mBoomer->AddComponent<Animator>();
			std::shared_ptr<Texture> boomerTexture = Resources::Find<Texture>(L"BoomerMonster");
			std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"BoomerExplosion");
			boomerAnimator->Create(L"m_Right", boomerTexture, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.2f);
			boomerAnimator->Create(L"m_Left", boomerTexture, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.2f);
			boomerAnimator->Create(L"m_RightHit", boomerTexture, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			boomerAnimator->Create(L"m_LeftHit", boomerTexture, Vector2(0.0f, 96.5f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			boomerAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 6, 0.1f);
			boomerAnimator->Play(L"m_Right", true);
			mBoomer->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"MonsterHit"));
			mBoomer->AddComponent<MonsterScript>(10,eLayerType::MonsterBoomer);
			mBoomer->Death();
			mBoomerMonsters.push_back(mBoomer);
		}

		//bigBoomer
		for (size_t i = 0; i < 10; i++)
		{
			Monster* mBigBoomer = object::Instantiate<Monster>(eLayerType::MonsterBoomer, this);
			mBigBoomer->SetLayerType(eLayerType::MonsterBoomer);
			mBigBoomer->SetName(L"BigBoomer");
			M_DefaultTr(mBigBoomer, Vector3(1.0f, 0.0f, 0.0f), Vector3(4.0f, 4.0f, 1.0f));
			CreateCollider(mBigBoomer, eColliderType::Rect, Vector2(0.5f, 0.5f));
			CreateSpriteRenderer(mBigBoomer, L"BoomerMonsterMaterial");
			Animator* boomerAnimator = mBigBoomer->AddComponent<Animator>();
			std::shared_ptr<Texture> BigboomerTexture = Resources::Find<Texture>(L"BoomerMonsterSprite");
			std::shared_ptr<Texture> BigboomerdeathTexture = Resources::Find<Texture>(L"M_DeathFX");
			boomerAnimator->Create(L"m_Right", BigboomerTexture, Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.2f);
			boomerAnimator->Create(L"m_Left", BigboomerTexture, Vector2(0.0f, 58.5f), Vector2(64.0f, 64.0f), Vector2::Zero, 4, 0.2f);
			boomerAnimator->Create(L"m_RightHit", BigboomerTexture, Vector2(0.0f, 117.0f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
			boomerAnimator->Create(L"m_LeftHit", BigboomerTexture, Vector2(0.0f, 175.5f), Vector2(64.0f, 64.0f), Vector2::Zero, 1, 0.1f);
			boomerAnimator->Create(L"DeathAnimation", BigboomerdeathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
			boomerAnimator->Play(L"m_Right", true);
			mBigBoomer->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"MonsterHit"));
			mBigBoomer->AddComponent<MonsterScript>(100, eLayerType::MonsterBoomer);
			mBigBoomer->Death();
			mBigBoomerMonsters.push_back(mBigBoomer);
		}
		//mBigBoomerMonsters[0]->Life();

		for (size_t i = 0; i < 30; i++)
		{
			GameObject* explosion = object::Instantiate<GameObject>(eLayerType::Explosion, this);
			CreateCollider(explosion, eColliderType::Rect, Vector2(3.0f, 3.0f));
			explosion->SetLayerType(eLayerType::Explosion);
			explosion->GetComponent<Transform>()->SetPosition(Vector3::Zero);
			explosion->AddComponent<BommerSoundEffectScript>();
			explosion->Death();
			boomersExplosions.push_back(explosion);
		}

		for (size_t i = 0; i < 30; i++)
		{
			GameObject* sound = object::Instantiate<GameObject>(eLayerType::None, this);
			sound->SetLayerType(eLayerType::Explosion);
			sound->GetComponent<Transform>()->SetPosition(Vector3::Zero);
			sound->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"BommerDeath"));
			sound->AddComponent<SoundObjectScript>();
			sound->Death();
			boomersSounds.push_back(sound);
		}
	}

	void PlayScene::CreateBommerEyeEffect()
	{
		for (size_t i = 0; i < mBoomerMonsters.size(); i++)
		{
			GameObject* eye = object::Instantiate<Monster>(eLayerType::None, this);
			eye->SetLayerType(eLayerType::None);
			eye->SetName(L"boomerEye");
			eye->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			eye->GetComponent<Transform>()->SetParent(mBoomerMonsters[i]->GetComponent<Transform>());
			eye->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			CreateSpriteRenderer(eye, L"BoomerEyeMaterial");
			Animator* eyeAni = eye->AddComponent<Animator>();
			std::shared_ptr<Texture> bmmoerEyeTex = Resources::Find<Texture>(L"BoomerMonsterEye");
			eyeAni->Create(L"m_Right", bmmoerEyeTex, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.2f);
			eyeAni->Create(L"m_Left", bmmoerEyeTex, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.2f);
			eyeAni->Play(L"m_Right", true);
			eye->AddComponent<MonsterEyeLightScript>(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			eye->Death();
			mBoomerMonsterEyes.push_back(eye);
		}
	}

	void PlayScene::CreateBossMonster()
	{
		Resources::Load<AudioClip>(L"BossCharge", L"..\\Resources\\Sound\\BossCharge.wav");

		Monster* hubNiggurat = object::Instantiate<Monster>(eLayerType::Boss, this);
		hubNiggurat->SetLayerType(eLayerType::Boss);
		hubNiggurat->SetName(L"hubNiggurat");
		Transform* bossTr = hubNiggurat->GetComponent<Transform>();
		bossTr->SetPosition(Vector3(10.0f, 0.0f, 0.0f));
		bossTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		CreateCollider(hubNiggurat, eColliderType::Rect, Vector2(0.6f, 0.4f));
		CreateSpriteRenderer(hubNiggurat, L"ShubNigguratMaterial");
		Animator* hubAnimator = hubNiggurat->AddComponent<Animator>();
		std::shared_ptr<Texture> hubNigguratTexture = Resources::Find<Texture>(L"Boss_ShubNiggurat");
		std::shared_ptr<Texture> deathTexture = Resources::Find<Texture>(L"M_DeathFX");
		hubAnimator->Create(L"Boss_RightMove", hubNigguratTexture, Vector2(0.0f, 0.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		hubAnimator->Create(L"Boss_RightCharge", hubNigguratTexture, Vector2(0.0f, 88.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 5, 0.2f);
		hubAnimator->Create(L"Boss_RightAttack", hubNigguratTexture, Vector2(0.0f, 184.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		hubAnimator->Create(L"Boss_LeftMove", hubNigguratTexture, Vector2(0.0f, 280.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		hubAnimator->Create(L"Boss_LeftCharge", hubNigguratTexture, Vector2(0.0f, 376.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 5, 0.2f);
		hubAnimator->Create(L"Boss_LeftAttack", hubNigguratTexture, Vector2(0.0f, 472.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		hubAnimator->Create(L"m_RightHit", hubNigguratTexture, Vector2(0.0f, 568.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 1, 0.1f);
		hubAnimator->Create(L"m_LeftHit", hubNigguratTexture, Vector2(0.0f, 664.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 1, 0.1f);
		hubAnimator->Create(L"DeathAnimation", deathTexture, Vector2(0.0f, 0.0f), Vector2(40.0f, 40.0f), Vector2::Zero, 4, 0.1f);
		hubAnimator->Play(L"Boss_RightMove", true);
		hubNiggurat->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"BossCharge"));
		hubNiggurat->AddComponent<HubNigguratScript>(2000);
		hubNiggurat->Death();
		mBossMonsters.push_back(hubNiggurat);
	}

	void PlayScene::CreateBossEffect()
	{
		GameObject* effect = object::Instantiate<Monster>(eLayerType::None, this);
		effect->SetLayerType(eLayerType::None);
		effect->SetName(L"bossEffect");
		effect->GetComponent<Transform>()->SetParent(mBossMonsters[0]->GetComponent<Transform>());
		effect->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		effect->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		CreateSpriteRenderer(effect, L"ShubNigguratEyeMaterial");
		Animator* effectAni = effect->AddComponent<Animator>();
		std::shared_ptr<Texture> bossEffectTex = Resources::Find<Texture>(L"Boss_ShubNigguratEye");
		effectAni->Create(L"m_Right", bossEffectTex, Vector2(0.0f, 0.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		effectAni->Create(L"m_RightCharge", bossEffectTex, Vector2(0.0f, 88.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 5, 0.2f);
		effectAni->Create(L"m_RightAttack", bossEffectTex, Vector2(0.0f, 184.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		effectAni->Create(L"m_Left", bossEffectTex, Vector2(0.0f, 280.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		effectAni->Create(L"m_LeftCharge", bossEffectTex, Vector2(0.0f, 376.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 5, 0.2f);
		effectAni->Create(L"m_LeftAttack", bossEffectTex, Vector2(0.0f, 472.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.2f);
		effectAni->Create(L"m_RightHit", bossEffectTex, Vector2(0.0f, 568.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 1, 0.1f);
		effectAni->Create(L"m_LeftHit", bossEffectTex, Vector2(0.0f, 664.0f), Vector2(96.0f, 96.0f), Vector2::Zero, 1, 0.1f);
		effectAni->Play(L"m_Right", true);
		effect->AddComponent<MonsterEyeLightScript>(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
		effect->Death();
		mBossMonsterEffects.push_back(effect);

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
			bulletAnimator->ResetStop();
			bullet->AddComponent<DragonFireScript>();
			bullet->Death();
			dragonFires.push_back(bullet);
		}
	}

	void PlayScene::CreateGhostPet()
	{
		Resources::Load<AudioClip>(L"Spell_Water_02", L"..\\Resources\\Sound\\Spell_Water_02.wav");

		ghostPet = CreateSkillObject(eLayerType::Skill, L"DragonMaterial");
		ghostPet->SetLayerType(eLayerType::Skill);
		ghostPet->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		Animator* ghostPetAnimator = ghostPet->AddComponent<Animator>();
		std::shared_ptr<Texture> ghostPetTexture = Resources::Find<Texture>(L"S_GhostPet");
		ghostPetAnimator->Create(L"ghostPetIdle", ghostPetTexture, Vector2::Zero, Vector2(16.0f, 16.0f), Vector2::Zero, 6, 0.1f);
		ghostPetAnimator->Create(L"ghostPetAttack", ghostPetTexture, Vector2(0, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 4, 0.1f);
		ghostPetAnimator->Play(L"ghostPetIdle", true);
		ghostPet->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"Spell_Water_02"));
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
			bulletAnimator->ResetStop();
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
			thunderObject->GetComponent<Transform>()->SetScale(Vector3(2.0f, 10.0f, 1.0f));
			thunderObject->GetComponent<Transform>()->SetPosition(Vector3::Zero);
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
			thunderObject->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"LightningSound"));
			thunderObject->Death();
			thunders.push_back(thunderObject);
		}
	}

	void PlayScene::CreateGale()
	{
		Resources::Load<AudioClip>(L"Spell_WindSound", L"..\\Resources\\Sound\\Spell_Wind_02.wav");
		for (size_t i = 0; i < 20; i++)
		{
			gales.push_back(CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"GaleMaterial"));
			Animator* galesAnimator = gales[i]->AddComponent<Animator>();
			gales[i]->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			std::shared_ptr<Texture> galesTexture = Resources::Find<Texture>(L"S_Gale");
			galesAnimator->Create(L"galeAni", galesTexture, Vector2::Zero, Vector2(96.0f, 96.0f), Vector2::Zero, 3, 0.01f);
			galesAnimator->Play(L"galeAni", true);
			gales[i]->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"Spell_WindSound"));
			gales[i]->Death();
			gales[i]->AddComponent<GaleScript>();
		}

	}

	void PlayScene::CreateScythe()
	{
		scythe = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"ScytheMaterial");
		scythe->SetLayerType(eLayerType::Skill);
		scythe->Death();
		scythe->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"MonsterHit"));
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
		Resources::Load<AudioClip>(L"Spell_IceSpear", L"..\\Resources\\Sound\\Spell_IceSpear_03.wav");

		for (size_t i = 0; i < 20; i++)
		{
			GameObject* icicle = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"IcicleMaterial");
			icicle->SetLayerType(eLayerType::Skill);
			icicle->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.3f, 1.0f));
			Collider2D* icicleCollider = icicle->GetComponent<Collider2D>();
			icicle->AddComponent<IcicleScript>();
			icicle->Death();
			icicles.push_back(icicle);
		}

		for (size_t i = 0; i < 20; i++)
		{
			GameObject* icicleSound = object::Instantiate<GameObject>(eLayerType::None, this);
			icicleSound->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"Spell_IceSpear"));
			icicleSound->AddComponent<SoundObjectScript>();
			icicleSounds.push_back(icicleSound);
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

	void PlayScene::CreateFreezes()
	{
		Resources::Load<AudioClip>(L"Spell_Freeze", L"..\\Resources\\Sound\\Spell_Freeze.wav");

		for (size_t i = 0; i < 1000; i++)
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
			freeze->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(L"Spell_Freeze"));
			freeze->Death();
			freezes.push_back(freeze);
		}
	}

	void PlayScene::CreateCurses()
	{
		for (size_t i = 0; i < 1000; i++)
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
	}

	void PlayScene::CreateHpUIobj()
	{
		for (size_t i = 0; i < 10; i++)
		{
			GameObject* hpObject = object::Instantiate<GameObject>(eLayerType::UI, this);
			hpObject->SetLayerType(eLayerType::UI);
			hpObject->GetComponent<Transform>()->SetPosition(Vector3(-7.0f + ((float)i * 0.8f), 4.7f, 9.0f));
			hpObject->GetComponent<Transform>()->SetScale(Vector3(2.5f, 2.5f, 1.0f));
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

	void PlayScene::CreateAbilityIcon(/*GameObject* parent*/)
	{
		for (size_t i = 0; i < 100; i++)
		{
			const std::wstring name = L"Icon_Ability_" + std::to_wstring(i) + L"Material";
			CreateSkillIcon(name, Vector3(0.0f, 0.0f, 9.0f), Vector3(0.54f, 0.54f, 1.0f));
		}

		for (size_t i = 0; i < 100; i++)
		{
			const std::wstring name = L"Icon_Ability_" + std::to_wstring(i) + L"Material";
			CreateSkillIcon(name, Vector3(0.0f, 0.0f, 9.0f), Vector3(0.54f, 0.54f, 1.0f));
		}

		for (size_t i = 0; i < 100; i++)
		{
			const std::wstring name = L"Ability_Text_" + std::to_wstring(i) + L"Material";
			CreateIconText(name, Vector3(-0.7f, 1.0f, 9.0f), Vector3(6.5f, 3.0f, 1.0f));
		}

		//CreateIconText
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

	void PlayScene::CreateUIPanal(Vector3 pos ,Vector3 scale)
	{
		GameObject* uiPanal = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiPanal->SetLayerType(eLayerType::UI);
		uiPanal->GetComponent<Transform>()->SetPosition(pos);
		uiPanal->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* panalRender = uiPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> panalMaterial = Resources::Find<Material>(L"PanalMaterial");
		panalRender->SetMaterial(panalMaterial);
		std::shared_ptr<Mesh> panalMesh = Resources::Find<Mesh>(L"RectMesh");
		panalRender->SetMesh(panalMesh);

		uiObjects.push_back(uiPanal);
	}

	void PlayScene::CreateUIObject(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* uiLeader = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiLeader->SetLayerType(eLayerType::UI);
		uiLeader->GetComponent<Transform>()->SetPosition(pos);
		uiLeader->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* leaderRender = uiLeader->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> leaderMaterial = Resources::Find<Material>(key);
		leaderRender->SetMaterial(leaderMaterial);
		std::shared_ptr<Mesh> leaderMesh = Resources::Find<Mesh>(L"RectMesh");
		leaderRender->SetMesh(leaderMesh);

		uiObjects.push_back(uiLeader);
	}

	void PlayScene::CreateUIObject(const std::wstring& key, std::vector<GameObject*>& array, Vector3 pos, Vector3 scale)
	{
		GameObject* uiLeader = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiLeader->SetLayerType(eLayerType::UI);
		uiLeader->GetComponent<Transform>()->SetPosition(pos);
		uiLeader->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* leaderRender = uiLeader->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> leaderMaterial = Resources::Find<Material>(key);
		leaderRender->SetMaterial(leaderMaterial);
		std::shared_ptr<Mesh> leaderMesh = Resources::Find<Mesh>(L"RectMesh");
		leaderRender->SetMesh(leaderMesh);

		array.push_back(uiLeader);
	}

	void PlayScene::CreatePowerUpFrame(Vector3 pos, Vector3 scale)
	{
		GameObject* frame = object::Instantiate<GameObject>(eLayerType::UI, this);
		frame->SetLayerType(eLayerType::UI);
		//frame->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		frame->GetComponent<Transform>()->SetPosition(pos);
		frame->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* render = frame->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"PowerupFrameMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		uiFrames.push_back(frame);

		GameObject* frameBG = object::Instantiate<GameObject>(eLayerType::UI, this);
		frameBG->SetLayerType(eLayerType::UI);
		//frameBG->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		frameBG->GetComponent<Transform>()->SetPosition(pos - Vector3(0.0f,0.0f,-0.01f));
		frameBG->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* bgRender = frameBG->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bgMaterial = Resources::Find<Material>(L"PowerupIconBGMaterial");
		bgRender->SetMaterial(bgMaterial);
		std::shared_ptr<Mesh> bgMesh = Resources::Find<Mesh>(L"RectMesh");
		bgRender->SetMesh(bgMesh);

		uiObjects.push_back(frameBG);
	}

	void PlayScene::CreateSkillUI(GameObject* parent)
	{
		CreateUIPanal(Vector3(1.0f, 1.0f, 9.0f), Vector3(10.0f, 3.2f, 1.0f));
		CreateUIObject(L"SelectPanalRedMaterial", Vector3(1.0f, -1.4f, 9.0f), Vector3(6.5f, 0.7f, 1.0f));
		CreateUIObject(L"SelectPanalWhiteMaterial", Vector3(1.0f, -1.4f, 9.0f), Vector3(6.5f, 0.7f, 1.0f));
		CreateUIObject(L"RefreshRedMaterial", Vector3(1.0f, -2.4f, 9.0f), Vector3(6.5f, 0.7f, 1.0f));
		CreateUIObject(L"RefreshWhiteMaterial", Vector3(1.0f, -2.4f, 9.0f), Vector3(6.5f, 0.7f, 1.0f));

		CreateUIObject(L"LeftDownLeaderMaterial", Vector3(3.4f, 1.6f, 9.0f), Vector3(0.45f, 0.45f, 1.0f));
		CreateUIObject(L"RightDownLeaderMaterial", Vector3(5.0f, 1.6f, 9.0f), Vector3(0.45f, 0.45f, 1.0f));
		CreateUIObject(L"DownRightLeaderMaterial", Vector3(3.4f, 0.0f, 9.0f), Vector3(0.45f, 0.45f, 1.0f));
		CreateUIObject(L"DownLeftLeaderMaterial", Vector3(5.0f, 0.0f, 9.0f), Vector3(0.45f, 0.45f, 1.0f));
		CreatePowerUpFrame(Vector3(4.2f, 1.7f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(3.22f, 0.82f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(5.10f, 0.82f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(4.2f, 0.10f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(-1.3f, 3.3f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(-0.1f, 3.3f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(1.1f, 3.3f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(2.3f, 3.3f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));
		CreatePowerUpFrame(Vector3(3.5f, 3.3f, 9.0f), Vector3(0.72f, 0.72f, 1.0f));


		for (size_t i = 0; i < uiObjects.size(); i++)
		{
			uiObjects[i]->Death();
		}
		for (size_t i = 0; i < uiFrames.size(); i++)
		{
			uiFrames[i]->Death();
		}
		for (size_t i = 0; i < iconObjects.size(); i++)
		{
			iconObjects[i]->Death();
			icons[i]->Death();
		}
		for (size_t i = 0; i < iconTexts.size(); i++)
		{
			iconTexts[i]->Death();
		}
		uiOn = false;
		uiOns[0] = false;
	}

	void PlayScene::CreateSkillIcon(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* iconObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		iconObj->SetLayerType(eLayerType::UI);
		//iconObj->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		iconObj->GetComponent<Transform>()->SetPosition(pos);
		iconObj->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* iconRender = iconObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> iconMaterial = Resources::Find<Material>(key);
		iconRender->SetMaterial(iconMaterial);
		std::shared_ptr<Mesh> iconMesh = Resources::Find<Mesh>(L"RectMesh");
		iconRender->SetMesh(iconMesh);

		iconObj->Death();
		iconObjects.push_back(iconObj);

		GameObject* icon = object::Instantiate<GameObject>(eLayerType::UI, this);
		icon->SetLayerType(eLayerType::UI);
		//icon->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		icon->GetComponent<Transform>()->SetPosition(pos);
		icon->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* render = icon->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(key);
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);

		icon->Death();
		icons.push_back(icon);
	}

	void PlayScene::CreatetimerObject(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* timer = object::Instantiate<GameObject>(eLayerType::UI, this);
		timer->SetLayerType(eLayerType::UI);
		timer->GetComponent<Transform>()->SetPosition(pos);
		timer->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* timerRender = timer->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> timerMat = Resources::Find<Material>(key);
		timerRender->SetMaterial(timerMat);
		std::shared_ptr<Mesh> timerMesh = Resources::Find<Mesh>(L"RectMesh");
		timerRender->SetMesh(timerMesh);

		timer->Death();
		timerObj.push_back(timer);
	}

	void PlayScene::CreateLevelUI(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* levelUI = object::Instantiate<GameObject>(eLayerType::UI, this);
		levelUI->SetLayerType(eLayerType::UI);
		levelUI->GetComponent<Transform>()->SetPosition(pos);
		levelUI->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* levelUIRender = levelUI->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> levelUIMat = Resources::Find<Material>(key);
		levelUIRender->SetMaterial(levelUIMat);
		std::shared_ptr<Mesh> levelUIMesh = Resources::Find<Mesh>(L"RectMesh");
		levelUIRender->SetMesh(levelUIMesh);

		//levelTexts.push_back(levelUI);
	}

	void PlayScene::CreateLevelText(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* levelText = object::Instantiate<GameObject>(eLayerType::UI, this);
		levelText->SetLayerType(eLayerType::UI);
		levelText->GetComponent<Transform>()->SetPosition(pos);
		levelText->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* levelTextRender = levelText->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> levelTextMat = Resources::Find<Material>(key);
		levelTextRender->SetMaterial(levelTextMat);
		std::shared_ptr<Mesh> levelTextMesh = Resources::Find<Mesh>(L"RectMesh");
		levelTextRender->SetMesh(levelTextMesh);

		levelText->Death();
		levelTexts.push_back(levelText);
	}

	void PlayScene::CreateBulletText(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* bulletText = object::Instantiate<GameObject>(eLayerType::UI, this);
		bulletText->SetLayerType(eLayerType::UI);
		bulletText->GetComponent<Transform>()->SetPosition(pos);
		bulletText->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* bulletTextRender = bulletText->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bulletTextMat = Resources::Find<Material>(key);
		bulletTextRender->SetMaterial(bulletTextMat);
		std::shared_ptr<Mesh> bulletTextMesh = Resources::Find<Mesh>(L"RectMesh");
		bulletTextRender->SetMesh(bulletTextMesh);

		bulletText->Death();
		bulletTexts.push_back(bulletText);
	}

	void PlayScene::CreateIconText(const std::wstring& key, Vector3 pos, Vector3 scale)
	{
		GameObject* text = object::Instantiate<GameObject>(eLayerType::UI, this);
		text->SetLayerType(eLayerType::UI);
		//iconObj->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		text->GetComponent<Transform>()->SetPosition(pos);
		text->GetComponent<Transform>()->SetScale(scale);
		SpriteRenderer* textRender = text->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> textMat = Resources::Find<Material>(key);
		textRender->SetMaterial(textMat);
		std::shared_ptr<Mesh> textMesh = Resources::Find<Mesh>(L"RectMesh");
		textRender->SetMesh(textMesh);

		text->Death();
		iconTexts.push_back(text);
	}

	void PlayScene::CreateExpBar(GameObject* parent)
	{
		GameObject* expBar = object::Instantiate<GameObject>(eLayerType::UI, this);
		expBar->SetLayerType(eLayerType::UI);
		expBar->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		expBar->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 5.0f, 9.0f));
		expBar->GetComponent<Transform>()->SetScale(Vector3(19.0f, 0.5f, 1.0f));
		SpriteRenderer* expBarRender = expBar->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> expBarMat = Resources::Find<Material>(L"LevelGaugeZeroMaterial");
		expBarRender->SetMaterial(expBarMat);
		std::shared_ptr<Mesh> expBarMesh = Resources::Find<Mesh>(L"RectMesh");
		expBarRender->SetMesh(expBarMesh);

		expGauge = object::Instantiate<GameObject>(eLayerType::UI, this);
		expGauge->SetLayerType(eLayerType::UI);
		expGauge->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		expGauge->GetComponent<Transform>()->SetPosition(Vector3(-10.0f, 5.0f, 9.0f));
		expGauge->GetComponent<Transform>()->SetScale(Vector3(0.0f, 0.5f, 1.0f));
		SpriteRenderer* gaugeRender = expGauge->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> gaugeMat = Resources::Find<Material>(L"LevelGaugeMaterial");
		gaugeRender->SetMaterial(gaugeMat);
		std::shared_ptr<Mesh> gaugeMesh = Resources::Find<Mesh>(L"RectMesh");
		gaugeRender->SetMesh(gaugeMesh);


		GameObject* reloadBarObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		reloadBarObject->SetLayerType(eLayerType::UI);
		reloadBarObject->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		reloadBarObject->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.6f, 9.0f));
		reloadBarObject->GetComponent<Transform>()->SetScale(Vector3(2.1f,0.5f,1.0f));
		SpriteRenderer* render = reloadBarObject->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ReloadBarMaterial");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		render->SetMesh(mesh);
		reloadBarObject->Death();
		reloadUI.push_back(reloadBarObject);

		GameObject* reloadButObject = object::Instantiate<GameObject>(eLayerType::UI, this);
		reloadButObject->SetLayerType(eLayerType::UI);
		reloadButObject->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		reloadButObject->GetComponent<Transform>()->SetPosition(Vector3(-1.0f, 0.6f, 9.0f));
		reloadButObject->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.5f, 1.0f));
		SpriteRenderer* butRender = reloadButObject->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> ButMaterial = Resources::Find<Material>(L"ReloadButMaterial");
		butRender->SetMaterial(ButMaterial);
		std::shared_ptr<Mesh> ButMesh = Resources::Find<Mesh>(L"RectMesh");
		butRender->SetMesh(ButMesh);
		reloadButObject->AddComponent<ReloadBarScript>();
		reloadButObject->Death();
		reloadUI.push_back(reloadButObject);

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

	void PlayScene::CreateExitUI()
	{
		GameObject* uiPanal = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiPanal->SetLayerType(eLayerType::UI);
		uiPanal->GetComponent<Transform>()->SetPosition(Vector3(5.0f, 1.0f, 9.0f));
		uiPanal->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		SpriteRenderer* panalRender = uiPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> panalMaterial = Resources::Find<Material>(L"PanalMaterial");
		panalRender->SetMaterial(panalMaterial);
		std::shared_ptr<Mesh> panalMesh = Resources::Find<Mesh>(L"RectMesh");
		panalRender->SetMesh(panalMesh);
		exitUIs.push_back(uiPanal);
		CreateUIObject(L"FollowingRedMaterial", exitUIs, Vector3(5.0f, 1.5f, 9.0f), Vector3(1.0f, 0.5f, 1.0f));
		CreateUIObject(L"FollowingWhiteMaterial", exitUIs, Vector3(5.0f, 1.5f, 9.0f), Vector3(1.0f, 0.5f, 1.0f));
		//exitUIs[2]->Death();
		CreateUIObject(L"GiveUPRedMaterial", exitUIs, Vector3(5.0f, 0.5f, 9.0f), Vector3(0.7f, 0.45f, 1.0f));
		CreateUIObject(L"GiveUpWhiteMaterial", exitUIs, Vector3(5.0f, 0.5f, 9.0f), Vector3(0.7f, 0.45f, 1.0f));
		//exitUIs[4]->Death();

		for (size_t i = 0; i < exitUIs.size(); i++)
		{
			exitUIs[i]->Death();
		}
	}

	void PlayScene::CreateEndUI()
	{
		GameObject* uiPanal = object::Instantiate<GameObject>(eLayerType::UI, this);
		uiPanal->SetLayerType(eLayerType::UI);
		uiPanal->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 1.0f, 9.0f));
		uiPanal->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		SpriteRenderer* panalRender = uiPanal->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> panalMaterial = Resources::Find<Material>(L"PanalMaterial");
		panalRender->SetMaterial(panalMaterial);
		std::shared_ptr<Mesh> panalMesh = Resources::Find<Mesh>(L"RectMesh");
		panalRender->SetMesh(panalMesh);
		endUIs.push_back(uiPanal);
		CreateUIObject(L"SurvivalMaterial", endUIs, Vector3(1.0f, 2.0f, 9.0f), Vector3(0.8f, 0.676f, 1.0f));
		CreateUIObject(L"DeadRedMaterial", endUIs, Vector3(1.0f, 2.0f, 9.0f), Vector3(0.8f, 0.676f, 1.0f));
		CreateUIObject(L"ReStartRedMaterial", endUIs, Vector3(1.0f, 0.8f, 9.0f), Vector3(1.0f, 0.5f, 1.0f));
		CreateUIObject(L"ReStartWhiteMaterial", endUIs, Vector3(1.0f, 0.8f, 9.0f), Vector3(1.0f, 0.5f, 1.0f));
		CreateUIObject(L"MainMenuRedMaterial", endUIs, Vector3(1.0f, 0.1f, 9.0f), Vector3(1.0f, 0.5f, 1.0f));
		CreateUIObject(L"MainMenuWhiteMaterial", endUIs, Vector3(1.0f, 0.1f, 9.0f), Vector3(1.0f, 0.5f, 1.0f));

		for (size_t i = 0; i < endUIs.size(); i++)
		{
			endUIs[i]->Death();
		}
	}

	void PlayScene::M_DefaultTr(auto* object,Vector3 pos,Vector3 scale)
	{
		Transform* mboomerTr = object->GetComponent<Transform>();
		mboomerTr->SetPosition(pos);
		mboomerTr->SetScale(scale);
	}

	void PlayScene::FreezeAddToMonster()
	{
		int a = mBrainMonsters.size();
		int b = mBoomerMonsters.size();
		int c = mEyeMonsters.size();
		int d = mBossMonsters.size();
		int e = mBigBoomerMonsters.size();

		for (size_t i = 0; i < mBrainMonsters.size(); i++)
		{
			freezes[i]->GetComponent<Transform>()->SetParent(mBrainMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mBoomerMonsters.size(); i++)
		{
			freezes[a + i]->GetComponent<Transform>()->SetParent(mBoomerMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mEyeMonsters.size(); i++)
		{
			freezes[a + b + i]->GetComponent<Transform>()->SetParent(mEyeMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mBossMonsters.size(); i++)
		{
			freezes[a + b + c + i]->GetComponent<Transform>()->SetParent(mBossMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mBigBoomerMonsters.size(); i++)
		{
			freezes[a + b + c + d + i]->GetComponent<Transform>()->SetParent(mBigBoomerMonsters[i]->GetComponent<Transform>());
		}
	}

	void PlayScene::CurseAddToMonster()
	{
		int a = mBrainMonsters.size();
		int b = mBoomerMonsters.size();
		int c = mEyeMonsters.size();
		int d = mBossMonsters.size();
		int e = mBigBoomerMonsters.size();

		for (size_t i = 0; i < mBrainMonsters.size(); i++)
		{
			curses[i]->GetComponent<Transform>()->SetParent(mBrainMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mBoomerMonsters.size(); i++)
		{
			curses[a + i]->GetComponent<Transform>()->SetParent(mBoomerMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mEyeMonsters.size(); i++)
		{
			curses[a + b + i]->GetComponent<Transform>()->SetParent(mEyeMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mBossMonsters.size(); i++)
		{
			curses[a + b + c + i]->GetComponent<Transform>()->SetParent(mBossMonsters[i]->GetComponent<Transform>());
		}
		for (size_t i = 0; i < mBigBoomerMonsters.size(); i++)
		{
			curses[a + b + c + d + i]->GetComponent<Transform>()->SetParent(mBigBoomerMonsters[i]->GetComponent<Transform>());
		}
	}

	void PlayScene::ALLSKILL()
	{
		upgradeobj->GetScript<UpgradeScript>()->TakeAim();
		upgradeobj->GetScript<UpgradeScript>()->Penetration();
		upgradeobj->GetScript<UpgradeScript>()->Sniper();
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
		for (size_t i = 0; i < uiFrames.size(); i++)
		{
			uiFrames[i]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
		}
		for (size_t i = 0; i < iconObjects.size(); i++)
		{
			iconObjects[i]->GetComponent<Transform>()->SetScale(Vector3(0.54f, 0.54f, 1.0f));
			icons[i]->GetComponent<Transform>()->SetScale(Vector3(0.54f, 0.54f, 1.0f));
		}

		srand((unsigned)time(NULL));

		for (size_t i = 0; i < 5; i++)
		{
			randomValue[i] = (rand() % 23) + 1;

			for (size_t j = 0; j < i; j++)
			{
				if (randomValue[i] == randomValue[j]) i--;
			}
		}

		for (size_t i = 0; i < 5; i++)
		{
			click[i][0] = randomValue[i];
			int a;
			for (a = 0; a < 4; a++)
			{
				if (upgradeobj->GetScript<UpgradeScript>()->GetUpgradeBool()[randomValue[i]][a])
				{
					continue;
				}
				else
				{
					iconObjects[(randomValue[i] * 4) + a]->GetComponent<Transform>()->SetPosition(Vector3(-1.3f + (i * 1.2f), 3.3f, 9.0f));
					iconObjects[(randomValue[i] * 4) + a]->Life();
					break;
				}
			}
			iconTexts[(randomValue[0] * 4) + a]->Life();
			click[i][1] = a;
		}

		iconObjects[randomValue[0]]->GetComponent<Transform>()->SetScale(Vector3(1.08f, 1.08f, 1.0f));
		uiFrames[4]->GetComponent<Transform>()->SetScale(Vector3(1.08f, 1.08f, 1.0f));
		iconObjects[(randomValue[0] * 4)]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));


		//AbilityTree
		for (size_t i = 0; i < 5; i++)
		{
			icons[(randomValue[i] * 4) + 0]->GetComponent<Transform>()->SetPosition(Vector3(4.2f, 1.7f, 9.0f));
			icons[(randomValue[i] * 4) + 1]->GetComponent<Transform>()->SetPosition(Vector3(3.22f, 0.82f, 9.0f));
			icons[(randomValue[i] * 4) + 2]->GetComponent<Transform>()->SetPosition(Vector3(5.10f, 0.82f, 9.0f));
			icons[(randomValue[i] * 4) + 3]->GetComponent<Transform>()->SetPosition(Vector3(4.2f, 0.1f, 9.0f));
		}

		for (size_t i = 0; i < 4; i++)
		{
			icons[(randomValue[0] * 4) + i]->Life();
		}

		//SetStop();
		for (size_t i = 0; i < mBrainMonsters.size(); i++)
		{
			mBrainMonsters[i]->Stop();
		}
		for (size_t i = 0; i < mEyeMonsters.size(); i++)
		{
			mEyeMonsters[i]->Stop();
		}
		for (size_t i = 0; i < mBoomerMonsters.size(); i++)
		{
			mBoomerMonsters[i]->Stop();
		}
		for (size_t i = 0; i < mTreeMonsters.size(); i++)
		{
			mTreeMonsters[i]->Stop();
		}
		for (size_t i = 0; i < mBossMonsters.size(); i++)
		{
			mBossMonsters[i]->Stop();
		}
		player->Stop();
		pWeapon->Stop();


		for (size_t i = 0; i < uiObjects.size(); i++)
		{
			uiObjects[i]->Life();
		}
		for (size_t i = 0; i < uiFrames.size(); i++)
		{
			uiFrames[i]->Life();
		}

		uiObjects[2]->Death();
		
		if (bReroll == false)
		{
			uiObjects[3]->Death();
			uiObjects[4]->Death();
		}
		else
		uiObjects[4]->Death();

		uiOn = true;
		uiOns[0] = true;
	}

	void PlayScene::UiButton(Vector3 pos)
	{
		if (Input::GetKeyDown(eKeyCode::LBTN) && -0.321f <= pos.x && pos.x <= -0.25f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIClick(0);
		}
		else if (uiFrames[0 + 4]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && -0.321f <= pos.x && pos.x <= -0.25f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIMousePoint(0);
		}
		else if (Input::GetKeyDown(eKeyCode::LBTN) && -0.178f <= pos.x && pos.x <= -0.106f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIClick(1);
		}
		else if (uiFrames[1 + 4]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f)  && -0.178f <= pos.x && pos.x <= -0.106f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIMousePoint(1);
		}
		else if (Input::GetKeyDown(eKeyCode::LBTN) && -0.03f <= pos.x && pos.x <= 0.069f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIClick(2);
		}
		else if (uiFrames[2 + 4]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && -0.03f <= pos.x && pos.x <= 0.069f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIMousePoint(2);
		}
		else if (Input::GetKeyDown(eKeyCode::LBTN) && 0.10f <= pos.x && pos.x <= 0.172f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIClick(3);
		}
		else if (uiFrames[3 + 4]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && 0.10f <= pos.x && pos.x <= 0.172f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIMousePoint(3);
		}
		else if (Input::GetKeyDown(eKeyCode::LBTN) && 0.25f <= pos.x && pos.x <= 0.322f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIClick(4);
		}
		else if (uiFrames[4 + 4]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && 0.25f <= pos.x && pos.x <= 0.322f && 0.386f <= pos.y && pos.y <= 0.522f)
		{
			AbilityUIMousePoint(4);
		}
		else if (uiFrames[0]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && 0.345f <= pos.x && pos.x <= 0.414f && 0.08f <= pos.y && pos.y <= 0.217f)
		{
			AbilityTreeClick(abliltyNumber,0);
		}
		else if (uiFrames[1]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && 0.231f <= pos.x && pos.x <= 0.302f && -0.075f <= pos.y && pos.y <= 0.053f)
		{
			AbilityTreeClick(abliltyNumber, 1);
		}
		else if (uiFrames[2]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && 0.460f <= pos.x && pos.x <= 0.531f && -0.075f <= pos.y && pos.y <= 0.053f)
		{
			AbilityTreeClick(abliltyNumber, 2);
		}
		else if (uiFrames[3]->GetComponent<Transform>()->GetScale() != Vector3(1.08f, 1.08f, 1.0f) && 0.345f <= pos.x && pos.x <= 0.414f && -0.242f <= pos.y && pos.y <= -0.111f)
		{
			AbilityTreeClick(abliltyNumber, 3);
		}
		else if (Input::GetKeyDown(eKeyCode::LBTN) && -0.380f <= pos.x && pos.x <= 0.380f && -0.555f <= pos.y && pos.y <= -0.393f)
		{
			SelectAbility();
		}
		else if (uiObjects[2]->GetState() == GameObject::Dead && -0.380f <= pos.x && pos.x <= 0.380f && -0.555f <= pos.y && pos.y <= -0.393f)
		{
			uiObjects[4]->Death();

			soundObj[2]->GetComponent<AudioSource>()->Play();
			uiObjects[2]->Life();
		}
		else if (bReroll == true && Input::GetKeyDown(eKeyCode::LBTN) && -0.380f <= pos.x && pos.x <= 0.380f && -0.753f <= pos.y && pos.y <= -0.591f)
		{
			bReroll = false;
			soundObj[3]->GetComponent<AudioSource>()->Play();

			for (size_t i = 0; i < uiObjects.size(); i++)
			{
				uiObjects[i]->Death();
			}
			for (size_t i = 0; i < uiFrames.size(); i++)
			{
				uiFrames[i]->Death();
			}
			for (size_t i = 0; i < iconObjects.size(); i++)
			{
				iconObjects[i]->Death();
				icons[i]->Death();
			}
			for (size_t i = 0; i < iconTexts.size(); i++)
			{
				iconTexts[i]->Death();
			}
			LevelUPUI();
		}
		else if (bReroll == true && uiObjects[4]->GetState() == GameObject::Dead && -0.380f <= pos.x && pos.x <= 0.380f && -0.753f <= pos.y && pos.y <= -0.591f)
		{
			uiObjects[2]->Death();

			soundObj[2]->GetComponent<AudioSource>()->Play();
			uiObjects[4]->Life();
		}
	}

	void PlayScene::EscUIButton(Vector3 pos)
	{
		if (Input::GetKeyDown(eKeyCode::LBTN) && 0.419f <= pos.x && pos.x <= 0.535f && 0.086f <= pos.y && pos.y <= 0.157f)
		{
			EscUIClick(0);
		}
		else if (Input::GetKeyDown(eKeyCode::LBTN) && 0.419f <= pos.x && pos.x <= 0.535f && -0.108f <= pos.y && pos.y <= -0.05f)
		{
			EscUIClick(1);
		}
		else if (exitUIs[2]->GetState() == GameObject::Dead && 0.419f <= pos.x && pos.x <= 0.535f && 0.086f <= pos.y && pos.y <= 0.157f)
		{
			EscUIMousePoint(2);
		}
		else if (exitUIs[4]->GetState() == GameObject::Dead && 0.419f <= pos.x && pos.x <= 0.535f && -0.108f <= pos.y && pos.y <= -0.05f)
		{
			EscUIMousePoint(4);
		}
	}

	void PlayScene::EscUIOn()
	{
		for (size_t i = 0; i < exitUIs.size(); i++)
		{
			if (i % 2 == 0 && i != 0)
				continue;

			exitUIs[i]->Life();
		}
		uiOns[1] = true;
		uiOn = true;
	}

	void PlayScene::EscUIClick(int number)
	{
		soundObj[3]->GetComponent<AudioSource>()->Play();

		if (number == 0)
		{
			for (size_t i = 0; i < exitUIs.size(); i++)
			{
				exitUIs[i]->Death();
			}
			uiOns[1] = false;
			uiOn = false;
		}
		else if (number == 1)
		{
			ReturnTitleScene();
		}
	}

	void PlayScene::EscUIMousePoint(int number)
	{
		for (size_t i = 0; i < exitUIs.size(); i++)
		{
			if (i % 2 == 0 && i != 0)
			{
				exitUIs[i]->Death();
				continue;
			}

			exitUIs[i]->Life();
		}

		soundObj[2]->GetComponent<AudioSource>()->Play();
		exitUIs[number]->Life();
		exitUIs[number - 1]->Death();
	}

	void PlayScene::AbilityUIClick(int number)
	{
		uiObjects[2]->Death();
		uiObjects[4]->Death();
		int a = click[number][1];
		soundObj[3]->GetComponent<AudioSource>()->Play();

		for (size_t i = 0; i < uiFrames.size(); i++)
		{
			uiFrames[i]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
		}
		for (size_t i = 0; i < iconObjects.size(); i++)
		{
			iconObjects[i]->GetComponent<Transform>()->SetScale(Vector3(0.54f, 0.54f, 1.0f));
		}

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				icons[(randomValue[j] * 4) + i]->Death();
			}
		}
		for (size_t i = 0; i < iconTexts.size(); i++)
		{
			iconTexts[i]->Death();
		}


		for (size_t i = 0; i < 4; i++)
		{
			icons[(randomValue[number] * 4) + i]->Life();
		}

		uiFrames[number + 4]->GetComponent<Transform>()->SetScale(Vector3(1.08f, 1.08f, 1.0f));
		iconObjects[(randomValue[number] * 4) + a]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
		iconTexts[(randomValue[number] * 4) + a]->Life();
		AbilityTreeClickReset();

		abliltyNumber = number;
	}

	void PlayScene::AbilityUIMousePoint(int number)
	{
		uiObjects[2]->Death();
		uiObjects[4]->Death();
		soundObj[2]->GetComponent<AudioSource>()->Play();

		int a = click[number][1];

		for (size_t i = 0; i < uiFrames.size(); i++)
		{
			uiFrames[i]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
		}
		for (size_t i = 0; i < iconObjects.size(); i++)
		{
			iconObjects[i]->GetComponent<Transform>()->SetScale(Vector3(0.54f, 0.54f, 1.0f));
		}
		for (size_t i = 0; i < icons.size(); i++)
		{
			icons[i]->GetComponent<Transform>()->SetScale(Vector3(0.54f, 0.54f, 1.0f));
		}


		uiFrames[number + 4]->GetComponent<Transform>()->SetScale(Vector3(1.08f, 1.08f, 1.0f));
		iconObjects[(randomValue[number] * 4) + a]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
	}

	void PlayScene::AbilityTreeClick(int ablityNum, int treeNum)
	{
		soundObj[2]->GetComponent<AudioSource>()->Play();
		uiObjects[2]->Death();
		uiObjects[4]->Death();

		for (size_t i = 0; i < 4; i++)
		{
			icons[(randomValue[ablityNum] * 4) + i]->GetComponent<Transform>()->SetScale(Vector3(0.54f, 0.54f, 1.0f));
			uiFrames[i]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
		}

		for (size_t i = 0; i < iconTexts.size(); i++)
		{
			iconTexts[i]->Death();
		}

		icons[(randomValue[ablityNum] * 4) + treeNum]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
		iconTexts[(randomValue[ablityNum] * 4) + treeNum]->Life();
		uiFrames[treeNum]->GetComponent<Transform>()->SetScale(Vector3(1.08f, 1.08f, 1.0f));
	}

	void PlayScene::AbilityTreeClickReset()
	{
		for (size_t i = 0; i < 4; i++)
		{
			uiFrames[i]->GetComponent<Transform>()->SetScale(Vector3(0.72f, 0.72f, 1.0f));
			for (size_t j = 0; j < 5; j++)
			{
				icons[(randomValue[j] * 4) + i]->GetComponent<Transform>()->SetScale(Vector3(0.54f, 0.54f, 1.0f));
			}
		}
	}

	void PlayScene::EndUIButton(Vector3 pos)
	{
		if (Input::GetKeyDown(eKeyCode::LBTN) && -0.05f <= pos.x && pos.x <= 0.05f && -0.05f <= pos.y && pos.y <= 0.01f)
		{
			EndUIClick(0);
		}
		else if (Input::GetKeyDown(eKeyCode::LBTN) && -0.05f <= pos.x && pos.x <= 0.05f && -0.2f <= pos.y && pos.y <= -0.13f)
		{
			EndUIClick(1);
		}
		else if (endUIs[4]->GetState() == GameObject::Dead && -0.05f <= pos.x && pos.x <= 0.05f && -0.05f <= pos.y && pos.y <= 0.01f)
		{
			EndUIMousePoint(4);
		}
		else if (endUIs[6]->GetState() == GameObject::Dead && -0.05f <= pos.x && pos.x <= 0.05f && -0.2f <= pos.y && pos.y <= -0.13f)
		{
			EndUIMousePoint(6);
		}
	}

	void PlayScene::EndUIClick(int number)
	{
		soundObj[3]->GetComponent<AudioSource>()->Play();
		ReturnTitleScene();
	}

	void PlayScene::EndUIMousePoint(int number)
	{
		for (size_t i = 3; i < endUIs.size(); i++)
		{
			if (i % 2 == 0)
			{
				endUIs[i]->Death();
				continue;
			}

			endUIs[i]->Life();
		}

		soundObj[2]->GetComponent<AudioSource>()->Play();
		endUIs[number]->Life();
		endUIs[number - 1]->Death();
	}

	void PlayScene::SurvivalEndUIOn()
	{
		pSceneCamera->GetComponent<AudioSource>()->Stop();
		soundObj[8]->GetComponent<AudioSource>()->Play();

		for (size_t i = 0; i < endUIs.size(); i++)
		{
			if (i % 2 == 0 && i != 0)
				continue;

			endUIs[i]->Life();
		}

		uiOns[2] = true;
		uiOn = true;
	}

	void PlayScene::DeadEndUIOn()
	{
		pSceneCamera->GetComponent<AudioSource>()->Stop();
		soundObj[9]->GetComponent<AudioSource>()->Play();

		endUIs[0]->Life();
		endUIs[2]->Life();
		endUIs[3]->Life();
		endUIs[5]->Life();

		uiOns[2] = true;
		uiOn = true;
	}

	void PlayScene::SelectAbility()
	{
		soundObj[3]->GetComponent<AudioSource>()->Play();
		upgradeobj->GetScript<UpgradeScript>()->UpgradeSkill(click[abliltyNumber][0], click[abliltyNumber][1]);

		for (size_t i = 0; i < uiObjects.size(); i++)
		{
			uiObjects[i]->Death();
		}
		for (size_t i = 0; i < uiFrames.size(); i++)
		{
			uiFrames[i]->Death();
		}
		for (size_t i = 0; i < iconObjects.size(); i++)
		{
			iconObjects[i]->Death();
			icons[i]->Death();
		}
		for (size_t i = 0; i < iconTexts.size(); i++)
		{
			iconTexts[i]->Death();
		}
		uiOn = false;
		uiOns[0] = false;

		for (size_t i = 0; i < mBrainMonsters.size(); i++)
		{
			mBrainMonsters[i]->Start();
		}
		for (size_t i = 0; i < mEyeMonsters.size(); i++)
		{
			mEyeMonsters[i]->Start();
		}
		for (size_t i = 0; i < mBoomerMonsters.size(); i++)
		{
			mBoomerMonsters[i]->Start();
		}
		for (size_t i = 0; i < mTreeMonsters.size(); i++)
		{
			mTreeMonsters[i]->Start();
		}
		for (size_t i = 0; i < mBossMonsters.size(); i++)
		{
			mBossMonsters[i]->Start();
		}
		player->Start();
		pWeapon->Start();

		SetStart();
	}

	Vector3 PlayScene::UiMousePos()
	{
		Vector3 pos = Input::GetMousePosition();

		glm::vec2 screenCoord(pos.x, pos.y);
		glm::mat4 viewProjectionMatrix(1.0f);

		int screenWidth = 1600;
		int screenHeight = 900;

		glm::vec2 cameraCoorcd = ScreenToCamera(screenCoord, viewProjectionMatrix, screenWidth, screenHeight);

		Vector3 mousePos = Vector3(cameraCoorcd.x, cameraCoorcd.y, 0.0f);

		int a = 0;

		return mousePos;
	}

	void PlayScene::CreateStageOneTile(Vector3 pos)
	{
		GameObject* tile = object::Instantiate<GameObject>(eLayerType::Tile, this);
		tile->SetLayerType(eLayerType::Tile);
		tile->GetComponent<Transform>()->SetScale(Vector3(40.0f, 40.0f, 1.0f));
		tile->GetComponent<Transform>()->SetPosition(pos);
		SpriteRenderer* render = tile->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"Tile_0Material");
		render->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		stageOneMapManager->GetScript<StageOneTileManager>()->SetTile(tile);
		render->SetMesh(mesh);
	}

	void PlayScene::ReturnTitleScene()
	{
		pSceneCamera->GetComponent<AudioSource>()->Play();
		SceneManager::LoadScene(eSceneType::Tilte);
		//player->Life();

		for (size_t i = 0; i < players.size(); i++)
		{
			players[i]->GetComponent<Transform>()->SetPosition(Vector3::Zero);
			players[i]->GetScript<PlayerScript>()->GameReset();
		}
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
		monsterFactoryManager->GetScript<MonsterFactoryScript>()->GameReset();
		magicLens->GetScript<MagicLensScript>()->GameReset();
		upgradeobj->GetScript<UpgradeScript>()->GameReset();
		expGauge->GetComponent<Transform>()->SetScale(Vector3(0.0f, 0.5f, 1.0f));
		scythe->GetScript<ScytheScript>()->GameReset();

		for (size_t i = 0; i < timerObj.size(); i++)
		{
			timerObj[i]->Death();
		}

		timerObj[0]->Life();
		timerObj[10]->Life();
		timerObj[20]->Life();
		timerObj[30]->Life();
		timerObj[40]->Life();

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

		for (size_t i = 0; i < mBrainMonsters.size(); i++)
		{
			mBrainMonsters[i]->Death();
			mBrainMonsterEyes[i]->Death();
		}
		for (size_t i = 0; i < mBoomerMonsters.size(); i++)
		{
			mBoomerMonsters[i]->Death();
			mBoomerMonsterEyes[i]->Death();
		}
		for (size_t i = 0; i < mEyeMonsters.size(); i++)
		{
			mEyeMonsters[i]->Death();
			mEyeMonsterEyes[i]->Death();
		}
		for (size_t i = 0; i < mBossMonsters.size(); i++)
		{
			mBossMonsters[i]->Death();
			mBossMonsterEffects[i]->Death();
		}

		for (size_t i = 0; i < exitUIs.size(); i++)
		{
			exitUIs[i]->Death();
		}

		uiOn = false;

		for (size_t i = 0; i < 3; i++)
		{
			uiOns[i] = false;
		}

		for (size_t i = 0; i < endUIs.size(); i++)
		{
			endUIs[i]->Death();
		}
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

	void PlayScene::CreateAmmoIcon(GameObject* parent)
	{
		GameObject* iconObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		iconObj->SetLayerType(eLayerType::UI);
		iconObj->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
		iconObj->GetComponent<Transform>()->SetPosition(Vector3(-9.0f , 3.2f, 9.0f));
		iconObj->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		SpriteRenderer* iconRender = iconObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> iconMaterial = Resources::Find<Material>(L"AmmoIconMaterial");
		iconRender->SetMaterial(iconMaterial);
		std::shared_ptr<Mesh> iconMesh = Resources::Find<Mesh>(L"RectMesh");
		iconRender->SetMesh(iconMesh);
	}

	void PlayScene::CreateSpriteRenderer(auto* object, const std::wstring& materialKey)
	{
		SpriteRenderer* spriteRender = object->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(materialKey);
		spriteRender->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		spriteRender->SetMesh(mesh);
	}
	void PlayScene::CreateSoundobject(const std::wstring& key)
	{
		GameObject* soundObject = object::Instantiate<GameObject>(eLayerType::None, this);
		soundObject->SetLayerType(eLayerType::None);
		soundObject->AddComponent<AudioSource>()->SetClip(Resources::Find<AudioClip>(key));
		soundObj.push_back(soundObject);
	}
}