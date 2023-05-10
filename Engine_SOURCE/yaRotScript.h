#pragma once
#include "yaScript.h"



namespace ya
{
	class RotScript : public Script
	{
	public:
		RotScript();
		~RotScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Rotate();

	private:


	};
}


