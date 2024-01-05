#pragma once

#include "GameObject.h"

GameObject::GameObject(Rectangle& rectangle, Color color, const std::string& texturePath)
	: m_rectangle(rectangle), m_color(color), m_texture(texturePath)
{

}

GameObject::GameObject(Rectangle& rectangle, Color color, const Texture& texture)
	: m_rectangle(rectangle), m_color(color), m_texture(texture)
{

}

GameObject::GameObject()
	: m_rectangle(0, 0, 0, 0, ""), m_color({0.0f, 0.0f, 0.0f, 0.0f}), m_texture("")
{

}

void GameObject::Draw(const Renderer& renderer) {
	m_texture.Bind();
	renderer.DrawRectangle(m_rectangle, m_color, m_rectangle.m_shader);
	m_texture.Unbind();
}
