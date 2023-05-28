#include "yalogoScript.h"
#include "yaGameObject.h"

namespace ya
{
	logoScript::logoScript()
	{

	}
	logoScript::~logoScript()
	{

	}
	void logoScript::Initalize()
	{

	}
	void logoScript::Update()
	{

	}
	void logoScript::FixedUpdate()
	{

	}
	void logoScript::Render()
	{

	}
	void logoScript::Next()
	{
		GetOwner()->Death();
	}
	void logoScript::Reset()
	{
		GetOwner()->Life();
	}
}