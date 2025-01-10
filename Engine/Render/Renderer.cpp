#include "PreCompiledHeader.h"
#include "Renderer.h"
#include <cmath>
#include <Engine/Engine.h>

Renderer::Renderer(std::vector<std::vector<int>> grid, \
	Vector2 position, Vector2 direction, double width, double height) : \
	grid(grid), position(position), direction(direction), width(width), height(height), distance(0)
{
}

void Renderer::Raycasting()
{
	double i = 0, ratio = 0;
	Vector2 raydirection = Vector2(0.0, 0.0);
	Vector2 plane = direction.VectorRotation(1.57);

	while (i < width)
	{
		ratio = 2 * i / width - 1;
		raydirection.x = direction.x + plane.x * ratio;
		raydirection.y = direction.y + plane.y * ratio;
		CheckDistance(raydirection.x, raydirection.y);
		DrawLine(static_cast<int>(i));
		++i;
	}
	for (int ix = 0; ix < height; ++ix)
		Log(buffer[ix]);
	Engine::Get().SetCursorPosition(0, 0);
}

void Renderer::CheckDistance(double rx, double ry)
{
	int x = static_cast<int>(position.x);
	int y = static_cast<int>(position.y);
	double dx = std::abs(1.0 / rx);
	double dy = std::abs(1.0 / ry);
	int signX = 1, signY = 1;

	double distX = 0.0, distY = 0.0;

	if (rx < 0)
	{
		signX = -1;
		distX = (position.x - x) * dx;
	}
	else
	{
		signX = 1;
		distX = (x - position.x + 1.0) * dx;
	}
	if (ry < 0)
	{
		signY = -1;
		distY = (position.y - y) * dy;
	}
	else
	{
		signY = 1;
		distY = (y - position.y + 1.0) * dy;
	}

	while (1)
	{
		if (distX < distY)
		{
			distX += dx;
			x += signX;
			if (grid[y][x] == 1)
			{
				distance = (x - position.x + (1 - signX) / 2) / rx;
				break;
			}
		}
		else
		{
			distY += dy;
			y += signY;
			if (grid[y][x] == 1)
			{
				distance = (y - position.y + (1 - signY) / 2) / ry;
				break;
			}
		}
	}

}

void Renderer::DrawLine(int x)
{
	//ȭ�� ����
	int heightInt = static_cast<int>(height);
	int lineHeight = static_cast<int>(heightInt / distance);

	int start = (-1) * lineHeight + heightInt / 2;
	if (start < 0)
		start = 0;
	int end = lineHeight / 2 + heightInt / 2;
	if (end >= heightInt)
		end = heightInt - 1;

	//for (int y = 0; y < heightInt; ++y)
	//{
	//	Engine::Get().SetCursorPosition(x, y);
	//	if (y < start || y > end)
	//		Log(" ");
	//	else
	//		Log("*");
	//}
	for (int y = 0; y < heightInt; ++y)
	{
		if (y < start || y > end)
			buffer[y][x] = ' ';
		else
			buffer[y][x] = '0';
	}
}