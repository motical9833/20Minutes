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



		// Monster
		{
			CreateBrainMonster();
			CreateEyeMonster();
			CreateTreeMonster();
			CreateBommerMonster();
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
			pTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
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
			weaponTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			weaponTr->SetParent(pTr);
			weaponTr->SetPosition(Vector3(0.3f, 0.02f, 0.0f));
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


			// SKill
			for (size_t i = 0; i < 20; i++)
			{
				GameObject* thunderObject = object::Instantiate<GameObject>(eLayerType::Skill, this);
				thunders.push_back(thunderObject);
				thunders[i]->SetLayerType(eLayerType::Skill);
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

			// 원형 콜라이더 작성 해야됨
			pulseObject = object::Instantiate<GameObject>(eLayerType::Skill, this);
			pulseObject->SetLayerType(eLayerType::Skill);


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

			holyShield = CreateSkillObject(eLayerType::Skill, L"HolyShieldMaterial");
			holyShield->GetComponent<Transform>()->SetParent(pTr);
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

			for (size_t i = 0; i < 20; i++)
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

			for (size_t i = 0; i < 20; i++)
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
				curseAnimator->Play(L"curseAni", false);

				curse->AddComponent<CurseScript>();

				curse->Death();
				curses.push_back(curse);
			}
			curses[0]->GetComponent<Transform>()->SetParent(mBrainMonsters[0]->GetComponent<Transform>());
			curses[1]->GetComponent<Transform>()->SetParent(mBoomerMonsters[0]->GetComponent<Transform>());
			curses[2]->GetComponent<Transform>()->SetParent(mEyeMonsters[0]->GetComponent<Transform>());
			curses[3]->GetComponent<Transform>()->SetParent(mTreeMonsters[0]->GetComponent<Transform>());

			for (size_t i = 0; i < 30; i++)
			{
				GameObject* smite = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"SmiteFXMaterial");
				smite->SetLayerType(eLayerType::Skill);
				smite->GetComponent<Transform>()->SetPosition(Vector3::Zero);
				smite->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
				smite->GetComponent<Collider2D>()->SetSize(Vector2(0.3f, 0.3f));
				smite->GetComponent<Collider2D>()->SetCenter(Vector2(0.0f, -0.6f));
				Animator* smiteAnimator = smite->AddComponent<Animator>();
				std::shared_ptr<Texture> smiteTexture = Resources::Find<Texture>(L"S_SmiteFX");
				smiteAnimator->Create(L"Smite", smiteTexture, Vector2::Zero, Vector2(32.0f, 96.0f), Vector2::Zero, 4, 0.1f);
				smiteAnimator->Play(L"Smite",false);
				smite->AddComponent<SmiteScript>();
				smite->Death();
				smites.push_back(smite);
			}

			magicLens = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"MagicLensMaterial");
			magicLens->SetLayerType(eLayerType::Skill);
			magicLens->GetComponent<Transform>()->SetPosition(Vector3(-4.0f, 0.0f, 0.0f));
			magicLens->GetComponent<Collider2D>()->SetSize(Vector2(0.2f, 1.0f));
			Collider2D* lensCollider = magicLens->GetComponent<Collider2D>();
			lensCollider->SetCenter(Vector2::Zero);
			Animator* lensAnimator = magicLens->AddComponent<Animator>();
			std::shared_ptr<Texture> lensTexture = Resources::Find<Texture>(L"S_MagicLens");
			magicLens->AddComponent<MagicLensScript>();

			dragonPet = CreateSkillObject(eLayerType::Skill, L"DragonMaterial");
			dragonPet->SetLayerType(eLayerType::Skill);
			dragonPet->AddComponent<DragonPetScript>();
			dragonPet->GetComponent<Transform>()->SetParent(pTr);
			dragonPet->GetComponent<Transform>()->SetScale(Vector3(3.0f,3.0f,1.0f));
			Animator* dragonAnimator = dragonPet->AddComponent<Animator>();
			std::shared_ptr<Texture> dragonEggTexture = Resources::Find<Texture>(L"S_DragonEgg");
			std::shared_ptr<Texture> dragonTexture = Resources::Find<Texture>(L"S_Dragon");
			dragonAnimator->Create(L"DragonEgg", dragonEggTexture, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 1, 255);
			dragonAnimator->Create(L"DragonIdle", dragonTexture, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 6, 0.1f);
			dragonAnimator->Create(L"DragonAttack", dragonTexture, Vector2(0, 32.0f) , Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

			dragonAnimator->Play(L"DragonIdle",true);

			ghostPet = CreateSkillObject(eLayerType::Skill, L"DragonMaterial");
			ghostPet->SetLayerType(eLayerType::Skill);
			ghostPet->AddComponent<GhostPetScript>();
			ghostPet->GetComponent<Transform>()->SetParent(pTr);
			ghostPet->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			Animator* ghostPetAnimator = ghostPet->AddComponent<Animator>();
			std::shared_ptr<Texture> ghostPetTexture = Resources::Find<Texture>(L"S_GhostPet");
			ghostPetAnimator->Create(L"ghostPetIdle", ghostPetTexture, Vector2::Zero, Vector2(16.0f, 16.0f), Vector2::Zero, 6, 0.1f);
			ghostPetAnimator->Create(L"ghostPetAttack", ghostPetTexture, Vector2(0, 16.0f), Vector2(16.0f, 16.0f), Vector2::Zero, 4, 0.1f);
			ghostPetAnimator->Play(L"ghostPetIdle", true);

			for (size_t i = 0; i < 20; i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(eLayerType::Bullet, this);
				bullet->SetLayerType(eLayerType::Bullet);
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
			scythe = CreateSkillObject(eColliderType::Rect, eLayerType::Skill, L"ScytheMaterial");
			scythe->SetLayerType(eLayerType::Skill);
			scythe->AddComponent<ScytheScript>();

			colliderCheck = object::Instantiate<GameObject>(eLayerType::Skill, this);
			colliderCheck->SetLayerType(eLayerType::Skill);
			Transform* checkTr = colliderCheck->GetComponent<Transform>();
			checkTr->SetPosition(Vector3::Zero);
			checkTr->SetScale(Vector3::One);
			Collider2D* checkCollider = colliderCheck->AddComponent<Collider2D>();
			checkCollider->SetType(eColliderType::Rect);
			checkCollider->SetType(eColliderType::Rect);
			checkCollider->SetSize(Vector2(5.0f, 5.0f));
			colliderCheck->AddComponent<ColliderCheckScript>();
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

		skillManager = object::Instantiate<GameObject>(eLayerType::None, this);
		skillManager->AddComponent<SkillManager>();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Skill, eLayerType::Monster, true);
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
			pWeapon->Life();
			mBoomerMonsters[0]->GetScript<MonsterScript>()->Reset();
			mBrainMonsters[0]->GetScript<MonsterScript>()->Reset();
			mEyeMonsters[0]->GetScript<MonsterScript>()->Reset();
			

			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i]->GetScript<BulletScript>()->Reset();
				bullets[i]->Death();
			}

			for (size_t i = 0; i < gales.size(); i++)
			{
				gales[i]->GetScript<GaleScript>()->Reset();
				gales[i]->Death();
			}

			for (size_t i = 0; i < thunders.size(); i++)
			{
				thunders[i]->GetScript<ThunderScript>()->Reset();
				thunders[i]->Death();
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
		M_DefaultTr(m_Brain, Vector3(2.0f, 0.0f, 0.0f), Vector3::Zero);
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
