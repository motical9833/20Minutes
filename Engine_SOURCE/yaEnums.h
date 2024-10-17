#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Tilte,
		Play,
		End,
	};

	enum class eMouseState
	{
		IDLE,
		CLICK,
		HOLD,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Tile,
		Tree,
		Monster,
		MonsterBoomer,
		Boss,
		Explosion,
		Player,
		Bullet,
		Skill,
		Skill_Buff,
		Skill_Smite,
		ExpMarble,
		Particle,
		ColliderChack,
		UI,
		PostProcess,
		End = 20,
	};

	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Mesh,
		Collider,
		MeshRenerer,
		SpriteRenderer,
		Animator,
		ParticleSystem,
		Audio,
		AudioListener,
		AudioSource,
		Light,
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
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		AudioClip,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};
	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End, 
	};

	enum class eUIType
	{
		HUD,
		BUTTERN,
		TITLE_MAINMENU,
		TITLE_CHARACTERSELECT,
		TITLE_MAPSELECT,

		HP,
		BULLETCURRENT,
		CURRENTTIME,
		EXPBAR,
		SKILLSELECT,
		OPTION,

		END,
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

}