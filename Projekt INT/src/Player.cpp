#include "Player.h"

void Player::Draw(Renderer renderer)
{
	renderer.DrawRectangle(rectangle, color);
	Move();
}

void Player::Move()
{

}