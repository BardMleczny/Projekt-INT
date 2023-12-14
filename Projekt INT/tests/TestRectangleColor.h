#pragma once

#include "Test.h"

namespace test
{

	class TestRectangleColor : public Test
	{
	public:
		TestRectangleColor();
		~TestRectangleColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

	private:
		float m_RecColor[4];
	};
}