#include "Player.h"
#include "Engine/Engine.h"

Player::Player(Vector2 position, Vector2 direction)
{
	SetPosition(position);
	SetDirection(direction);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	//Ű �Է½� ������ ����
	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		SetDirection(direction.VectorRotation(-0.1));
	}	
	else if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		SetDirection(direction.VectorRotation(0.1));
	}
}
