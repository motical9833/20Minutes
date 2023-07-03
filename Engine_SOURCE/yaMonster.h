#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

		void Initalize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Stop() { bStop = true; }
		void Start() { bStop = false; }

	private:
		bool bStop;

	};
}