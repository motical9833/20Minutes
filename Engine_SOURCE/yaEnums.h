#pragma once

namespace ya::enums
{
	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Monster,
		Player,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, //��ġ ������ �����ϴ� ������Ʈ
		Camera,
		Mesh,
		Collider,
		MeshRenerer,
		SpriteRenderer,
		UI,
		FadeInOut,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		//Font,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,

		Script,
		End,
	};
}