#include "yaPlayerMoveScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	PlayerMoveScript::PlayerMoveScript()
		:pSpeed(1.0f)
		,dir(Vector3{0.0f,0.0f,0.0f})
	{

	}
	PlayerMoveScript::~PlayerMoveScript()
	{

	}
	void PlayerMoveScript::Initalize()
	{

	}
	void PlayerMoveScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos += pSpeed * tr->Right() * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos += pSpeed * -tr->Right() *  Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos += pSpeed * tr->Up() *  Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos += pSpeed * -tr->Up() *  Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos += pSpeed * tr->Forward() *  Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos += pSpeed * -tr->Forward() *  Time::DeltaTime();
		}


		tr->SetPosition(pos);


	}
	void PlayerMoveScript::Render()
	{

	}
}