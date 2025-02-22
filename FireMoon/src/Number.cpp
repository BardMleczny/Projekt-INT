#include "Number.h"
#include <iostream>

NumberText::NumberText(int number, int size, Color color)
	: value(number),
	basicRectangle(0.0f, 0.0f, size, size, "res/shaders/basicRectangle_vertex.shader", "res/shaders/basicRectangle_fragment.shader"),
	color(color)
{
	numberTextures = new Texture*[10];
	for (int i = 0; i < 10; i++)
	{
		Texture* tempTexture = new Texture("res/textures/numbers/set2/" + std::to_string(i) + ".png");
		numberTextures[i] = tempTexture;
	}
}

NumberText::~NumberText()
{
	for (int i = 0; i < 10; i++)
	{
		delete numberTextures[i];
	}
	delete numberTextures;
}

void NumberText::Draw(float x, float y)
{
	int length = 0, divisor = 10;
	while ((value != 0 && (value % divisor == 0)) || ((value % int(pow(10, length + 1))) / int(pow(10, length))))
	{
		length++;
		if (value % divisor == 0)
			divisor *= 10;
	}

	basicRectangle.m_transform.y = y;
	for (int i = 0; i < length; i++)
	{
		int index = (value % int(pow(10, i + 1)) - value % int(pow(10, i))) / int(pow(10, i));
		numberTextures[index]->Bind();
		basicRectangle.m_transform.x = x - basicRectangle.GetWidth() * (i + 1);
		
		Renderer::DrawRectangle(basicRectangle, color, glm::mat4(1.0f), basicRectangle.m_shader);
		numberTextures[index]->Unbind();
	}
}
