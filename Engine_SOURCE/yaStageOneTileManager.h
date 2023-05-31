#pragma once
#include "yaScript.h"
#include "yaGameObject.h"

namespace ya
{
	class StageOneTileManager : public Script
	{
	public:
		StageOneTileManager();
		virtual ~StageOneTileManager();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetLeft();
		void SetRight();
		void SetUP();
		void SetDown();
		void SetTile(GameObject* obj) { tiles.push_back(obj); }
		void SetCurrentPos(Vector3 pos) { currentPos = pos; }
		void SwapArrayTile(std::vector<GameObject*>& array, int objectA, int objectB);
		void SwapArrayTile(std::vector<GameObject*>& array, int idx1, int idx2,int idx3);

		void MovePosX();
	private:
		std::vector<GameObject*> tiles;
		Vector3 currentPos;
		Vector3 savedPos;
		UINT8 left;
		UINT8 right;
		UINT8 up;
		UINT8 down;
	};
}