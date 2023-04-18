#include "yaWeaponScript.h"
#include "yaBulletScript.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaSkillManager.h"

namespace ya
{
	WeaponScript::WeaponScript()
		: bReload(false)
		, bReloading(false)
		, time(0.0f)
		, reloadTime(1.0f)
		, maxBullet(6)
		, currentBullet(6)
		, allFireBulletCnt(0)
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
	{

	}
	WeaponScript::~WeaponScript()
	{

	}
	void WeaponScript::Initalize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTrans = GetOwner()->GetComponent<Transform>();
		mAnimator->Stop();

		pScene = dynamic_cast<PlayScene*>(SceneManager::GetPlaySCene());
	}
	void WeaponScript::Update()
	{
		Cheat();
		time += Time::DeltaTime();

		if (mTransform->GetParent()->GetOwner()->IsDead() == true)
		{
			GetOwner()->Death();
		}

		WeaponRotate();

		if (bReload)
			Reload();
		
		if (bReloading)
		{
			time += Time::DeltaTime();
			
			if (time >= reloadTime)
			{
				mAnimator->Stop();
				bReloading = false;
				currentBullet = maxBullet;
				time = 0;
			}
		}

		if (bReloading == false && bReload == false)
		{
			if (Input::GetKeyDown(eKeyCode::LBTN))
			{
				Fire();
 				if (currentBullet <= 0)
					bReload = true;
			}
		}

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
	void WeaponScript::BulletSpeedUP(float percentage)
	{
		for (auto i : bullets)
		{
			BulletScript* scripts = i->GetOwner()->GetScript<BulletScript>();

			float speed = scripts->Getspeed();
			speed *= (1 + percentage / 100);

			scripts->SetSpeed(speed);
		}
	}
	void WeaponScript::BulletSpeedDown(float percentage)
	{
		for (auto i : bullets)
		{
			BulletScript* scripts = i->GetOwner()->GetScript<BulletScript>();

			float speed = scripts->Getspeed();
			speed *= (1 - percentage / 100);

			scripts->SetSpeed(speed);
		}
	}
	void WeaponScript::BulletScaleUp(float percentage)
	{
		for (auto i : bullets)
		{
			Vector3 scale = i->GetScale();

			scale.x *= (1 + percentage / 100);
			scale.y *= (1 + percentage / 100);
			scale.z *= (1 + percentage / 100);

			i->SetScale(scale);
		}
	}
	void WeaponScript::BulletScaleDown(float percentage)
	{
		for (auto i : bullets)
		{
			Vector3 scale = i->GetScale();

			scale.x *= (1 - percentage / 100);
			scale.y *= (1 - percentage / 100);
			scale.z *= (1 - percentage / 100);

			i->SetScale(scale);
		}
	}
	void WeaponScript::AttackSpeedUP(float percentage)
	{
		fireDelayTime *= (1 - percentage / 100);
	}
	void WeaponScript::AttackSpeedDown(float percentage)
	{
		fireDelayTime *= (1 + percentage / 100);
	}

	void WeaponScript::ReloadTimeUP(float percentage)
	{
		reloadTime *= (1 + percentage / 100);
	}

	void WeaponScript::ReloadTimeDown(float percentage)
	{
		reloadTime *= (1 - percentage / 100);
	}

	void WeaponScript::BulletCntUP()
	{
		if (oneShotFire == 3)
			return;
		oneShotFire++;
		FirePosRot();
	}

	void WeaponScript::BulletCntDown()
	{
		if (oneShotFire == 1)
			return;
		oneShotFire--;
		FirePosRot();
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
				firePosObject[i]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, -0.05f + (i * 0.1f)));
			}
			break;
		case 3:
			firePosObject[0]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			for (size_t i = 0; i < 3; i++)
			{
				firePosObject[i]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, -0.05f + (i * 0.05f)));
			}
			break;
		     //case 4:
			//for (size_t i = 0; i < 2; i++)
			//{
			//	firePosObject[i]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, -0.5f + (i * 20)));
			//}
			//for (size_t j = 2; j < 4; j++)
			//{
			//	firePosObject[j]->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, 0.5f - (j * 20)));
			//}
			//break;
		}
	}

	void WeaponScript::Fire()
	{

		// 이동 변환 행렬
		Vector3 pos = Input::GetMousePosition();
		Matrix position;
		position.Translation(pos);

		Matrix mWorld = position;

		Vector3 vla = Vector3::Transform(Vector3::Zero,mWorld);

		if (time >= fireDelayTime)
		{
			int a = 0;
			for (size_t i = 0; i < 100; i++)
			{
				if (bullets[i]->GetOwner()->IsDead() == false)
					continue;

				Vector3 pos = firePosObject[a]->GetComponent<Transform>()->GetPosition() + mTransform->GetParent()->GetPosition();
				Vector3 rot = firePosObject[a]->GetComponent<Transform>()->GetRotation() + mTransform->GetRotation();

				bullets[i]->SetPosition(pos);
				bullets[i]->GetOwner()->GetScript<BulletScript>()->Setdir(rot);
				bullets[i]->SetParent(nullptr);
				bullets[i]->GetOwner()->Life();
				bullets[i]->GetOwner()->GetComponent<Animator>()->Stop();
				allFireBulletCnt++;
				a++;

				if (allFireBulletCnt % 2 == 0)
				{
					bullets[i]->GetOwner()->GetScript<BulletScript>()->ThunderEnchantOn();
				}

				if (a >= oneShotFire)
				{
					time = 0;
					break;
				}
			}
			currentBullet--;


			//for (auto i : bullets)
			//{
			//	BulletScript* scripts = i->GetOwner()->GetScript<BulletScript>();

			//	float speed = scripts->Getspeed();
			//	speed *= (1 + percentage / 100);

			//	scripts->SetSpeed(speed);
			//}

			//if (clickCnt%2 == 0)
			//{
			//	for (auto i : pScene->GetThunders())
			//	{
			//		if (i->IsDead() == false)
			//			continue;

			//		Vector3 pos = Input::GetMousePosition();

			//		i->GetComponent<Transform>()->SetPosition(pos);
			//		i->Life();
			//	}
			//}
		}
	}
	void WeaponScript::WeaponRotate()
	{
		mPos = mTrans->GetPosition() + mTrans->GetParent()->GetPosition();

		Vector3 rot = mTransform->GetRotation();

		mMousePos = Input::GetMousePosition();
		mRot = mTrans->GetRotation();
		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);
		mTrans->SetRotation(mRot);


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
		mAnimator->Stop();
	}

	void WeaponScript::Cheat()
	{
		if (Input::GetKeyState(eKeyCode::NUM_0) == eKeyState::DOWN)
		{
			BulletCntUP();
		}
		if (Input::GetKeyState(eKeyCode::NUM_1) == eKeyState::DOWN)
		{
			AttackSpeedUP(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_2) == eKeyState::DOWN)
		{
			AttackSpeedDown(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_3) == eKeyState::DOWN)
		{
			BulletScaleUp(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_4) == eKeyState::DOWN)
		{
			BulletScaleDown(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_5) == eKeyState::DOWN)
		{
			BulletSpeedUP(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_6) == eKeyState::DOWN)
		{
			BulletSpeedDown(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_7) == eKeyState::DOWN)
		{
			ReloadTimeDown(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_8) == eKeyState::DOWN)
		{
			ReloadTimeUP(10.0f);
		}
	}

	void WeaponScript::Reload()
	{
		mAnimator->Play(L"Revolver");
		mAnimator->Start();
		bReload = false;
		bReloading = true;
		time = 0;
	}
}