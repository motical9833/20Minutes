#include "yaWeaponScript.h"
#include "yaBulletScript.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaSkillManager.h"
#include "yaColliderCheckScript.h"
#include "yaPlayerScript.h"
#include "yaReloadBarScript.h"
#include "yaAudioSource.h"
#include <ctime>


namespace ya
{
	WeaponScript::WeaponScript()
		: bReload(false)
		, bReloading(false)
		, bBounceTrigger(false)
		, bSiege(false)
		, bFanFire(false)
		, bFanFireTrigger(false)
		, bBackFire(false)
		, bThunder(false)
		, bFreezeTrigger(false)
		, bIceShard(false)
		, bCurseTrigger(false)
		, bGaleTrigger(false)
		, bHolyAttack(false)
		, time(0.0f)
		, reloadTime(1.0f)
		, fanFireTime(0.0f)
		, maxBullet(6)
		, currentBullet(6)
		, allFireBulletCnt(0)
		, fanFireCnt(1)
		, killClip(0.0f)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mTrans(nullptr)
		, mMousePos{}
		, mPos{}
		, mRot{}
		, circleR(1)
		, deg(0)
		, objSpeed(1)
		, pPos{}
		, bullets{}
		, oneShotFire(1)
		, fireDelayTime(0.3f)
		, bulletPos{}
		, bulletRot{}
		, firePosObject{}
		, fireRotmul(1.0f)
		, reloadTimeMul(1.0f)
		, fireDelayTimeMul(1.0f)
		, ritualStack(0)
	{

	}
	WeaponScript::~WeaponScript()
	{

	}
	void WeaponScript::Initalize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mTrans = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->Stop();

		pScene = dynamic_cast<PlayScene*>(SceneManager::GetPlaySCene());

	}
	void WeaponScript::Update()
	{
		if (pScene->GetUIOn())
			return;

		Cheat();
		rateFireTime += Time::DeltaTime();

		if (mTransform->GetParent()->GetOwner()->IsDead() == true)
		{
			GetOwner()->Death();
		}
		if (bReload && pScene->GetPlayer()->GetScript<PlayerScript>()->GetShooting() == false)
		{
			Reload();
		}

		WeaponRotate();
		
		if (bReloading)
		{
			time += Time::DeltaTime();

			if (time >= (reloadTime * (reloadTimeMul - killClip)))
			{
				mAnimator->Stop();
				bReloading = false;
				currentBullet = maxBullet;
				time = 0.0f;
				killClip = 0.0f;
			}
		}
		if (currentBullet > 0)
		{
			if (Input::GetKeyPress(eKeyCode::LBTN))
			{
				SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ReloadBarScript>()->UIOff();
				mAnimator->Stop();
				Fire();
				BackFire();
				if (currentBullet <= 0)
				{
					ReloadSkill();
					if (bIceShard)
					{
						IceShardFire();
					}


					if (bFanFireTrigger)
						bFanFire = true;
				}

				time = 0.0f;
				bReload = true;
				bReloading = false;
			}
		}


		FanFire();
	}
	void WeaponScript::Render()
	{

	}
	void WeaponScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void WeaponScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void WeaponScript::OnCollisionExit(Collider2D* collider)
	{

	}

	void WeaponScript::FirePosRot()
	{
		switch (oneShotFire)
		{
		case 1:
			for (size_t i = 0; i < 1; i++)
			{
				firePosObject[i]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			}
			break;
		case 2:
			for (size_t i = 0; i < 2; i++)
			{
				firePosObject[i]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, (- 0.05f + (i * 0.1f)) * fireRotmul));
			}
			break;
		case 3:
			firePosObject[0]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			for (size_t i = 0; i < 3; i++)
			{
				firePosObject[i]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, ( - 0.05f + (i * 0.05f)) * fireRotmul));
			}
			break;
		}
	}

	void WeaponScript::ReloadSkill()
	{
		Gale();
		Smite();
		pScene->GetSkillManager()->GetScript<SkillManager>()->Spear();
	}

	void WeaponScript::FanFire()
	{
		if (bFanFire)
		{
			fanFireTime += Time::DeltaTime();

			if (fanFireTime >= 0.05f)
			{
				for (size_t i = 0; i < bullets.size(); i++)
				{
					if (bullets[i]->GetOwner()->IsDead() == false)
						continue;

					Vector3 pos = mTransform->GetParent()->GetPosition();
					Vector3 rot = Vector3(0.0f, 0.0f, 0.6f * fanFireCnt);
					bullets[i]->GetOwner()->GetScript<BulletScript>()->Reset();
					bullets[i]->SetPosition(pos);
					bullets[i]->GetOwner()->GetScript<BulletScript>()->Setdir(rot);
					bullets[i]->SetParent(nullptr);
					bullets[i]->GetOwner()->GetComponent<Animator>()->Stop();

					bullets[i]->GetOwner()->Life();

					fanFireCnt++;
					break;
				}
				fanFireTime = 0.0f;
			}
			if (fanFireCnt >= 11)
			{
				fanFireCnt = 0;
				fanFireTime = 0.0f;
				bFanFire = false;
			}
		}
	}

	void WeaponScript::BackFire()
	{
		if (bBackFire)
		{

			for (size_t i = 0; i < bullets.size(); i++)
			{
				if (bullets[i]->GetOwner()->IsDead() == false)
					continue;

				Vector3 pos = mTransform->GetParent()->GetPosition();
				Vector3 rot = firePosObject[4]->GetComponent<Transform>()->GetRotation() + mTransform->GetRotation();

				bullets[i]->GetOwner()->GetScript<BulletScript>()->Reset();
				bullets[i]->SetPosition(pos);
				bullets[i]->GetOwner()->GetScript<BulletScript>()->Setdir(rot);
				bullets[i]->SetParent(nullptr);
				bullets[i]->GetOwner()->Life();
				bullets[i]->GetOwner()->GetComponent<Animator>()->Stop();
				break;
			}
		}
	}

	void WeaponScript::IceShardFire()
	{
		if (bIceShard)
		{
			Vector3 pos = mTransform->GetParent()->GetPosition() + mTransform->GetPosition();

			for (size_t i = 0; i < 3; i++)
			{
				Vector3 rot = mTransform->GetRotation() + Vector3(0.0f, 0.0f, (-0.1f + (i * 0.1f)));
				pScene->GetSkillManager()->GetScript<SkillManager>()->IceShard(pos, rot);
			}
		}
	}

	void WeaponScript::SetRitualStack()
	{ 
		ritualStack++;

		if (ritualStack % 10 == 0)
		{
			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i]->GetOwner()->GetScript<BulletScript>()->SetDamageInc(0.01f);
			}
		}
	}

	void WeaponScript::BulletSupply(int count)
	{
		currentBullet += count;

		if (currentBullet > maxBullet)
		{
			currentBullet = maxBullet;
		}
	}

	void WeaponScript::Gale()
	{
		if (bGaleTrigger)
		{
			Vector3 pos = mTransform->GetParent()->GetPosition();
			Vector3 dir = Input::GetMousePosition() - pos;

			dir.Normalize();

			pScene->GetSkillManager()->GetScript<SkillManager>()->GaleFire(pos, dir);
		}
	}

	void WeaponScript::Smite()
	{
		if (bHolyAttack)
		{
			pScene->GetColliderChack()->GetScript<ColliderCheckScript>()->DeathChack();

			int arrayLength = pScene->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsters().size();

			list<Monster*> monsters = pScene->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsters();

			list<Monster*>::iterator iter = pScene->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsters().begin();


			for (iter = monsters.begin(); iter != monsters.end(); iter++)
			{
				Vector3 pos = (*iter)->GetComponent<Transform>()->GetPosition();

				pScene->GetSkillManager()->GetScript<SkillManager>()->SmiteFire(pos + Vector3(0.0f, 0.5f, 0.0f));
			}
		}
	}

	void WeaponScript::Fire()
	{
		if (rateFireTime >= fireDelayTime * fireDelayTimeMul)
		{
			int a = 0;
			for (size_t i = 0; i < bullets.size(); i++)
			{
				if (bullets[i]->GetOwner()->IsDead() == false)
					continue;

				Vector3 pos = mTransform->GetParent()->GetPosition() + mTransform->GetPosition();
				Vector3 rot = firePosObject[a]->GetComponent<Transform>()->GetRotation() + mTransform->GetRotation();

				bullets[i]->GetOwner()->GetScript<BulletScript>()->Reset();
				bullets[i]->SetPosition(pos);
				bullets[i]->GetOwner()->GetScript<BulletScript>()->Setdir(rot);
				bullets[i]->SetParent(nullptr);
				bullets[i]->GetOwner()->Life();
				bullets[i]->GetOwner()->GetComponent<Animator>()->Stop();


				if (pScene->GetPlayer()->GetScript<PlayerScript>()->GetPlayerHit())
				{
					bullets[i]->GetOwner()->GetScript<BulletScript>()->SetDamageInc(0.5f);
					bullets[i]->GetOwner()->GetScript<BulletScript>()->SetSpeedMul(0.5f);
				}

				if (bBounceTrigger)
					bullets[i]->GetOwner()->GetScript<BulletScript>()->SetBounceTrigger();
				if (bFreezeTrigger)
					bullets[i]->GetOwner()->GetScript<BulletScript>()->SetFreezeBullet();
				if (bCurseTrigger)
					bullets[i]->GetOwner()->GetScript<BulletScript>()->SetCurse();


				allFireBulletCnt++;
				a++;

				if (allFireBulletCnt % (oneShotFire * 2) == 0 && bThunder)
				{
					bullets[i]->GetOwner()->GetScript<BulletScript>()->ThunderEnchantOn();
				}

				if (a >= oneShotFire)
				{
					pScene->GetPlayer()->GetScript<PlayerScript>()->FireSlow();
					pScene->GetMuzzleFlash()->Life();
					pScene->GetMuzzleFlash()->GetComponent<AudioSource>()->Play();
					rateFireTime = 0;
					break;
				}
			}
			if (bSiege  && pScene->GetPlayer()->GetScript<PlayerScript>()->GetIdle() == true)
			{
				srand((unsigned int)std::time(NULL));

				int random = rand() & 100 + 1;

				if (random <= 33)
				{
					return;
				}
			}
			currentBullet--;
		}
	}
	void WeaponScript::WeaponRotate()
	{
		mPos = mTrans->GetPosition() + mTrans->GetParent()->GetPosition();
		
	//	Vector3 rot = mTransform->GetRotation();

		mMousePos = Input::GetMousePosition();
		mRot = mTrans->GetRotation();
		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);
		mTrans->SetRotation(mRot);

		Vector3 dir = Input::GetMousePosition() - mPos;

		dir.Normalize();

		GetOwner()->GetComponent<Transform>()->SetPosition(dir/2.0f);

	}
	void WeaponScript::Start()
	{

	}
	void WeaponScript::Action()
	{

	}
	void WeaponScript::End()
	{

	}

	void WeaponScript::Reset()
	{
		float speed = 10.0f;
		oneShotFire = 1;
		fireDelayTime = 0.3f;
		maxBullet = 6;
		currentBullet = 6;
		reloadTime = 1.0f;
		bReload = false;
		bReloading = false;
		time = 0.0f;
		rateFireTime = 0.0f;
		mAnimator->Stop();
	}

	void WeaponScript::GameReset()
	{
		fireRotmul = 1.0f;
		fireDelayTimeMul = 1.0f;
		bReload = false;
		bReloading = false;
		bBounceTrigger = false;
		bSiege = false;
		bBackFire = false;
		bFanFireTrigger = false;
		bFanFire = false;
		bThunder = false;
		bFreezeTrigger = false;
		bCurseTrigger = false;
		bHolyAttack = false;
		bGaleTrigger = false;

		time = 0.0f;
		rateFireTime = 0.0f;
		reloadTime = 1.0f;
		fanFireTime = 0.0f;
		killClip = 0.0f;

		maxBullet = 6;
		currentBullet = 6;
		oneShotFire = 1;
		allFireBulletCnt = 0;
		fanFireCnt = 0;
		ritualStack = 0;
	}

	void WeaponScript::Cheat()
	{
	}

	void WeaponScript::Reload()
	{
		SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ReloadBarScript>()->UIOn();
		SceneManager::GetPlayScene()->GetSoundObjects(1)->GetComponent<AudioSource>()->Play();
		mAnimator->Play(L"Revolver");
		mAnimator->Start();
		bReload = false;
		bReloading = true;
		time = 0;
	}
}