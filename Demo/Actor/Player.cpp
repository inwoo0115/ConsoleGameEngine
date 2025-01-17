#include "Player.h"
#include "Engine/Engine.h"

Player::Player(Vector2 position, Vector2 direction, std::vector<std::vector<int>> grid)
{
	SetPosition(position);
	SetDirection(direction);
	this->grid = grid;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		SetDirection(direction.VectorRotation(0.1));
	}
	else if (Engine::Get().GetKey(VK_LEFT))
	{
		SetDirection(direction.VectorRotation(-0.1));
	}

	double x = 0.0, y = 0.0, speed = 0.05;
	if (Engine::Get().GetKey(VK_SPACE))
		speed = 0.1;
	if (Engine::Get().GetKey(VK_UP))
	{
		x = position.x + direction.x * speed;
		y = position.y + direction.y * speed;
		if (grid[static_cast<int>(y)][static_cast<int>(x)] != 1)
			SetPosition(Vector2(x, y));
	}
	else if (Engine::Get().GetKey(VK_DOWN))
	{
		x = position.x - direction.x * speed;
		y = position.y - direction.y * speed;
		if (grid[static_cast<int>(y)][static_cast<int>(x)] != 1)
			SetPosition(Vector2(x, y));
	}
	//출구에 왔을 경우 종료
	int currentPosition = grid[static_cast<int>(position.y)][static_cast<int>(position.x)];
	if (currentPosition == 2)
	{
		Engine::Get().QuitGame();
	}
	else if (currentPosition > 2)
	{
		UsePortal(currentPosition);
	}
}

void Player::UsePortal(int portal)
{
	for (double i = 0.0; i < grid.size(); ++i) {
		for (double j = 0.0; j < grid[i].size(); ++j) {
			if (grid[i][j] == portal) {
				if (i != static_cast<int>(position.y) && j != static_cast<int>(position.x))
				{
					SetPosition(Vector2(j, i));
				}
			}
		}
	}
}
