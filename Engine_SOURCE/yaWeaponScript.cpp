#include "yaWeaponScript.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

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
	{

	}
	WeaponScript::~WeaponScript()
	{

	}
	void WeaponScript::Initalize()
	{
		mTransform = this->GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->Stop();

	}
	void WeaponScript::Update()
	{


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