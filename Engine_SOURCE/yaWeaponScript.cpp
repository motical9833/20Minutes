#include "yaWeaponScript.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaBulletScript.h"

namespace ya
{
	WeaponScript::WeaponScript()
		: bReload(false)
		, bReloading(false)
		, time(0.0f)
		, reloadTime(1.0f)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, maxBullet(6)
		, currentBullet(6)
		, mTrans(nullptr)
		, mMousePos{}
		, mPos{}
		, mRot{}
		, circleR(1)
		, deg(0)
		, objSpeed(1)
		, pPos{}
		, bullets{}
		, fireBulletCnt(1)
		, fireDelayTime(0.3f)
	{

	}
	WeaponScript::~WeaponScript()
	{

	}
	void WeaponScript::Initalize()
		{
		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->Stop();

		mTrans = GetOwner()->GetComponent<Transform>();
	}
	void WeaponScript::Update()
	{
		time += Time::DeltaTime();

		if (mTransform->GetParent()->GetOwner()->IsDead() == true)
		{
			GetOwner()->Death();
		}

		WeaponRotate();
		

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
		if (Input::GetKeyState(eKeyCode::NUM_4) == eKeyState::DOWN)
		{
			BulletScaleUp(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_5) == eKeyState::DOWN)
		{
			BulletScaleDown(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_7) == eKeyState::DOWN)
		{
			BulletSpeedUP(10.0f);
		}
		if (Input::GetKeyState(eKeyCode::NUM_8) == eKeyState::DOWN)
		{
			BulletSpeedDown(10.0f);
		}

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
			BulletScript* scripts = i->GetOwner()->GetComponent<BulletScript>();

			float speed = scripts->Getspeed();
			speed += (1 + percentage / 100);

			scripts->SetSpeed(speed);
		}
	}
	void WeaponScript::BulletSpeedDown(float percentage)
	{
		for (auto i : bullets)
		{
			BulletScript* scripts = i->GetOwner()->GetComponent<BulletScript>();

			float speed = scripts->Getspeed();
			speed += (1 - percentage / 100);

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

	void WeaponScript::Fire()
	{
		if (time >= fireDelayTime)
		{
			int a = 0;
			for (size_t i = 0; i < 100; i++)
			{
				if (bullets[i]->GetOwner()->IsDead() == false)
					continue;

				Vector3 pos = mTransform->GetParent()->GetPosition() + Vector3(0.5f, 0.05f, 0.0f);
				Vector3 dir = Input::GetMousePosition() - pos + Vector3(-50.0f, -50.0f, 0.0f);
				dir.Normalize();


				bullets[i]->SetPosition(pos);
				bullets[i]->GetOwner()->GetScript<BulletScript>()->Setdir(dir);
				bullets[i]->SetParent(nullptr);
				bullets[i]->GetOwner()->Life();
				currentBullet--;
				a++;

				if (a >= fireBulletCnt)
				{
					time = 0;
					break;
				}
			}
		}
	}
	void WeaponScript::WeaponRotate()
	{
		mPos = mTrans->GetPosition();

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

	void WeaponScript::Reload()
	{
		mAnimator->Play(L"Revolver");
		mAnimator->Start();
		bReload = false;
		bReloading = true;
		time = 0;
	}
}