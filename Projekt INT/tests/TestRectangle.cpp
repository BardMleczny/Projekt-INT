#include "TestRectangleColor.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestRectangleColor::TestRectangleColor()
		: m_RecColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	TestRectangleColor::~TestRectangleColor()
	{
	}

	void TestRectangleColor::OnUpdate(float deltaTime)
	{
	}

	void TestRectangleColor::OnRender()
	{
		
	}

	void TestRectangleColor::OnImguiRender()
	{
		ImGui::ColorEdit4("Change Color", m_RecColor);
	}
}
