#include "yaWeaponScript.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaBulletScript.h"

namespace ya
{
	WeaponScript::WeaponScript()
		:bReload(false)
		,bReloading(false)
		,time(0.0f)
		,reloadTime(1.0f)
		,mTransform(nullptr)
		,mAnimator(nullptr)
		,maxBullet(6)
		,currentBullet(6)
		,mTrans(nullptr)
		,mMousePos{}
		,mPos{}
		,mRot{}
		,circleR(1)
		,deg(0)
		,objSpeed(1)
		,pPos{}
		,bullets{}
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
		if (mTransform->GetParent()->GetOwner()->IsDead() == true)
		{
			GetOwner()->Death();
		}

		mPos = mTrans->GetPosition();

		Vector3 rot = mTransform->GetRotation();

		mMousePos = Input::GetMousePosition();
		mRot = mTrans->GetRotation();
		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);
		mTrans->SetRotation(mRot);
		
		if (Input::GetKeyState(eKeyCode::LBTN) == eKeyState::PRESSED)
		{
			Vector3 pos = mTransform->GetParent()->GetPosition() + Vector3(0.5f,0.05f,0.0f);
		    Vector3 dir = Input::GetMousePosition() - pos;
		    dir.Normalize();

			bullets[0]->SetPosition(pos);
			bullets[0]->GetOwner()->GetScript<BulletScript>()->Setdir(dir);
			bullets[0]->SetParent(nullptr);
			bullets[0]->GetOwner()->Life();
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
				currentBullet--;
 				if (currentBullet <= 0)
				{
					bReload = true;
				}
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
	}
}