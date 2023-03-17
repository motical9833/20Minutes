#pragma once
#include "yaComponent.h"

namespace ya
{
	class Light : public Component
	{
	public:
		Light();
		~Light();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:

	};
}