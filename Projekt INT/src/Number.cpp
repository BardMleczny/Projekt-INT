#include "Number.h"
#include <iostream>
NumberText::NumberText(int number, int size)
	: number(number), basicRectangle(0.0f, 0.0f, size, size, "res/shaders/basicRectangle.shader")
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

void NumberText::Draw(float x, float y, const Renderer& renderer)
{
	int length = 0;
	while ((number % int(pow(10, length + 1))) / int(pow(10, length)))
	{
		length++;
	}

	basicRectangle.m_transform.y = y;
	for (int i = 0; i < length; i++)
	{
		int index = (number % int(pow(10, i + 1)) - number % int(pow(10, i))) / int(pow(10, i));
		numberTextures[index]->Bind();
		basicRectangle.m_transform.x = x + basicRectangle.GetWidth() * i;
		
		renderer.DrawRectangle(basicRectangle, { 1.0f, 1.0f, 1.0f, 1.0f }, basicRectangle.m_shader);
		numberTextures[index]->Unbind();
	}
}
