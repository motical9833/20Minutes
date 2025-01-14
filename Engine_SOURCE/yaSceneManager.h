#pragma once
#include "yaScene.h"

namespace ya
{
	class PlayScene;
	class TitleScene;
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetPlaySCene() { return mScenes[(UINT)eSceneType::Play]; }
		static PlayScene* GetPlayScene();
		static TitleScene* GetTitleScene();
		static Scene* GetScene(eLayerType type) { return mScenes[(UINT)type]; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}
