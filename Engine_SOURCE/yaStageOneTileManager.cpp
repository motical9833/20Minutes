#include "yaStageOneTileManager.h"


namespace ya
{
	StageOneTileManager::StageOneTileManager()
		:left(0)
		,right(0)
		,up(0)
		,down(0)
		, currentPos(Vector3::Zero)
		, savedPos(Vector3(1.0f,1.0f,0.0f))
	{

	}
	StageOneTileManager::~StageOneTileManager()
	{

	}
	void StageOneTileManager::Initalize()
	{

	}
	void StageOneTileManager::Update()
	{
		MovePosX();
		if (currentPos.y < 0 && savedPos.y < 0)
		{
			
			if (currentPos.y - savedPos.y > 40)
			{
				savedPos.y = currentPos.y;
				SetUP();
			}
			else if (currentPos.y - savedPos.y < -40)
			{
				savedPos.y = currentPos.y;
				SetDown();
			}
		}
		else if (currentPos.y < 0 && savedPos.y > 0)
		{
			if (currentPos.y + savedPos.y < -40)
			{
				savedPos.y = currentPos.y;
				SetDown();
			}
		}
		else if (currentPos.y > 0 && savedPos.y < 0)
		{
			// 1.1f              // -0.1f
			if (currentPos.y + savedPos.y > 40)
			{
				savedPos.y = currentPos.y;
				SetUP();
			}
		}
		else if (currentPos.y > 0 && savedPos.y > 0)
		{
			//      2              1
			if (currentPos.y - savedPos.y > 40)
			{
				savedPos.y = currentPos.y;
				SetUP();
			}
			else if (currentPos.y - savedPos.y < -40)
			{
				savedPos.y = currentPos.y;
				SetDown();
			}
		}

	}
	void StageOneTileManager::FixedUpdate()
	{

	}
	void StageOneTileManager::Render()
	{

	}
	void StageOneTileManager::SetLeft()
	{
		left++;
		for (size_t i = 0; i < tiles.size(); i++)
		{
			if ((i + 1) % 3 == 0)
			{
				Vector3 pos = tiles[i]->GetComponent<Transform>()->GetPosition();
				pos.x = pos.x - 120;
				tiles[i]->GetComponent<Transform>()->SetPosition(pos);
			}
		}
		for (size_t i = 0; i < tiles.size(); i++)
		{
			if ((i + 1) % 3 == 0)
			{
				SwapArrayTile(tiles, i, i - 1, i - 2);
			}
		}
	}
	void StageOneTileManager::SetRight()
	{
		right++;

		for (size_t i = 0; i < tiles.size(); i++)
		{
			if (i % 3 == 0)
			{
				Vector3 pos = tiles[i]->GetComponent<Transform>()->GetPosition();
				pos.x = pos.x + 120;
				tiles[i]->GetComponent<Transform>()->SetPosition(pos);
			}
		}
		for (size_t i = 0; i < tiles.size(); i++)
		{
			if (i % 3 == 0)
			{
				SwapArrayTile(tiles, i, i + 1, i + 2);
			}
		}
	}
	void StageOneTileManager::SetUP()
	{
		up++;

		for (size_t i = 6; i < tiles.size(); i++)
		{
			Vector3 pos = tiles[i]->GetComponent<Transform>()->GetPosition();
			pos.y = pos.y + 120;
			tiles[i]->GetComponent<Transform>()->SetPosition(pos);
		}
		for (int i = 0; i < 3; i++)
		{
			int firstIdx = i;     
			int secondIdx = i + 3;
			int thirdIdx = i + 6; 

			SwapArrayTile(tiles, thirdIdx, secondIdx, firstIdx);
		}
	}
	void StageOneTileManager::SetDown()
	{
		down++;

		for (size_t i = 0; i < 3; i++)
		{
			Vector3 pos = tiles[i]->GetComponent<Transform>()->GetPosition();
			pos.y = pos.y - 120;
			tiles[i]->GetComponent<Transform>()->SetPosition(pos);
		}
		for (int i = 0; i < 3; i++)
		{
			int firstIdx = i;     
			int secondIdx = i + 3;
			int thirdIdx = i + 6; 

			SwapArrayTile(tiles, firstIdx, secondIdx, thirdIdx);
		}
	}
	void StageOneTileManager::SwapArrayTile(std::vector<GameObject*>& array, int idx1, int idx2)
	{
		GameObject* obj = array[idx1];
		array[idx1] = array[idx2];
		array[idx2] = obj;
	}
	void StageOneTileManager::SwapArrayTile(std::vector<GameObject*>& array, int idx1, int idx2, int idx3)
	{          
		GameObject* obj = array[idx1];
		array[idx1] = array[idx2];  
		array[idx2] = obj;
		obj = array[idx3];
		array[idx3] = array[idx2];
		array[idx2] = obj;
	}
	void StageOneTileManager::MovePosX()
	{
		if (currentPos.x < 0 && savedPos.x < 0)
		{
			// 10                  11
			if (currentPos.x - savedPos.x < -40)
			{
				savedPos.x = currentPos.x;
				SetLeft();
			}
			else if (currentPos.x - savedPos.x > 40)
			{
				savedPos.x = currentPos.x;
				SetRight();
			}
		}
		else if (currentPos.x < 0 && savedPos.x > 0)
		{
			//   -1.1f                  0.1f
			if (currentPos.x + savedPos.x < -40)
			{
				savedPos.x = currentPos.x;
				SetLeft();
			}
		}
		else if (currentPos.x > 0 && savedPos.x < 0)
		{
			// 1.1f              // -0.1f
			if (currentPos.x + savedPos.x < -40)
			{
				savedPos.x = currentPos.x;
				SetLeft();
			}
			else if (currentPos.x + savedPos.x > 40)
			{
				savedPos.x = currentPos.x;
				SetRight();
			}
		}
		else if (currentPos.x > 0 && savedPos.x > 0)
		{
			if (currentPos.x - savedPos.x < -40)
			{
				savedPos.x = currentPos.x;
				SetLeft();
			}
			else if (currentPos.x - savedPos.x > 40)
			{
				savedPos.x = currentPos.x;
				SetRight();
			}
		}
	}
}