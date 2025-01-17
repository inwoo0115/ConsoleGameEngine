#include "Player.h"
#include "Engine/Engine.h"

Player::Player(Vector2 position, Vector2 direction, std::vector<std::vector<int>> grid)
{
	SetPosition(position);
	SetDirection(direction);
	this->grid = grid;
	stamina = 400;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	double x = 0.0, y = 0.0, speed = 0.03;

	//방향전환
	if (Engine::Get().GetKey(VK_RIGHT))
	{
		SetDirection(direction.VectorRotation(0.1));
	}
	else if (Engine::Get().GetKey(VK_LEFT))
	{
		SetDirection(direction.VectorRotation(-0.1));
	}


	//달리기
	if (Engine::Get().GetKey(VK_SPACE))
	{
		if (stamina > 10)
		{
			speed = 0.1;
			stamina -= 2;
		}
	}
	else
	{
		if (stamina < 400)
			stamina += 2;
	}


	//이동
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
					if (grid[i+1][j] == 0)
					{
						SetPosition(Vector2(j, i + 1));
						SetDirection(Vector2(-1, 0));
					}
					else if (grid[i][j + 1] == 0)
					{
						SetPosition(Vector2(j + 1, i));
						SetDirection(Vector2(0, -1));
					}
					else if (grid[i - 1][j] == 0)
					{
						SetPosition(Vector2(j, i - 1));
						SetDirection(Vector2(1, 0));
					}
					else if (grid[i][j - 1] == 0)
					{
						SetPosition(Vector2(j - 1, i));
						SetDirection(Vector2(0, 1));
					}
				}
			}
		}
	}
}
