#include "PreCompiledHeader.h"
#include "Renderer.h"
#include <cmath>
#include <Engine/Engine.h>

Renderer::Renderer(std::vector<std::vector<int>> grid, \
	Vector2 position, Vector2 direction, double width, double height) : \
	grid(grid), position(position), direction(direction), width(width), height(height), distance(0)
{
	stamina = static_cast<int>(width);
	time = static_cast<int>(width);
}

void Renderer::Raycasting()
{
	double i = 0, ratio = 0;
	Vector2 raydirection = Vector2(0.0, 0.0);
	Vector2 plane = direction.VectorRotation(1.57);
	//색상 초기화
	Engine::Get().SetConsoleTextColor(1);
	ClearBuffer(buffer);

	while (i < width)
	{
		ratio = 2 * i / width - 1;
		raydirection.x = direction.x + plane.x * ratio;
		raydirection.y = direction.y + plane.y * ratio;
		CheckDistance(raydirection.x, raydirection.y);
		DrawLine(static_cast<int>(i));
		++i;
	}
	DrawColor();

	//buffer에 담긴 이미지 출력
	for (int ix = 0; ix < height; ++ix)
		Log(buffer[ix]);
	//time, stamina 출력
	DrawInfo();
	//시작 좌표 0으로 초기화
	Engine::Get().SetCursorPosition(0, 0);
}


//1이상 숫자에 충돌할떄까지 거리 측정
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
				side = 0;
				break;
			}
			else if (grid[y][x] == 2)
			{
				distance = (x - position.x + (1 - signX) / 2) / rx;
				side = 1;
				break;
			}
			else if (grid[y][x] > 2)
			{
				distance = (x - position.x + (1 - signX) / 2) / rx;
				side = 2;
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
				side = 0;
				break;
			}
			else if (grid[y][x] == 2)
			{
				distance = (y - position.y + (1 - signY) / 2) / ry;
				side = 1;
				break;
			}
			else if (grid[y][x] > 2)
			{
				distance = (y - position.y + (1 - signY) / 2) / ry;
				side = 2;
				break;
			}
		}
	}
}

//y축을 기준으로 한줄씩 거리에 비례하여 줄 그리기
void Renderer::DrawLine(int x)
{
	int heightInt = static_cast<int>(height);
	int lineHeight = static_cast<int>(heightInt / distance);

	int start = (-1) * lineHeight + heightInt / 2;
	if (start < 0)
		start = 0;
	int end = lineHeight / 2 + heightInt / 2;
	if (end >= heightInt)
		end = heightInt - 1;

	for (int y = 0; y < heightInt; ++y)
	{
		if (y < start || y > end)
			buffer[y][x] = ' ';
		else
		{
			if (side == 0)
				buffer[y][x] = '0';
			else if (side == 1)
				buffer[y][x] = '8';
			else if (side == 2)
				buffer[y][x] = '1';
		}
	}
}

//'8'로 표시된 부분 색상 문자열 삽입
void Renderer::DrawColor()
{
	const char* color = "\033[33m";
	const char* white = "\033[34m";
	const char* portal = "\033[35m";
	int colorLength = strlen(color);
	int portalLength = strlen(portal);
	int whiteLength = strlen(white);
	char prevText = '0';

	for (int y = 0;y < height;++y) {
		for (int x = 0;x < width;++x) {
			if (buffer[y][x] == '8' && prevText != '8')
			{
				memmove(buffer[y] + x + colorLength, buffer[y] + x, width - x + 10);
				memcpy(buffer[y] + x, color, colorLength);
				//flag = 1;
				x += colorLength;
				prevText = '8';
			}
			else if (buffer[y][x] == '1' && prevText != '1')
			{
				memmove(buffer[y] + x + portalLength, buffer[y] + x, width - x + 10);
				memcpy(buffer[y] + x, portal, portalLength);
				//flag = 1;
				x += colorLength;
				prevText = '1';
			}
			else if ((buffer[y][x] == ' ' || buffer[y][x] == '0') && prevText != '0')
			{
				memmove(buffer[y] + x + whiteLength, buffer[y] + x, width - x + 10);
				memcpy(buffer[y] + x, white, whiteLength);
				//flag = 0;
				x += whiteLength + 1;
				prevText = '0';
			}
		}
	}
}

void Renderer::DrawInfo()
{
	int heightInt = static_cast<int>(height);
	int widthInt = static_cast<int>(width);

	Engine::Get().SetConsoleTextColor(2);
	for (int i = 0; i < 5; ++i)
	{
		memset(buffer[i + heightInt], '0', stamina);
		memset(buffer[i + heightInt] + stamina, ' ', widthInt - stamina + 1);
		Log(buffer[i + heightInt]);
	}
	Engine::Get().SetConsoleTextColor(4);
	for (int i = 5; i < 10; ++i)
	{
		memset(buffer[i + heightInt], '0', time);
		memset(buffer[i + heightInt] + time, ' ', widthInt - time + 1);
		Log(buffer[i + heightInt]);
	}
	for (int i = 10; i < 12; ++i)
	{
		memset(buffer[i + heightInt], ' ', time);
		Log(buffer[i + heightInt]);
	}
}

void Renderer::SetPosition(const Vector2& newPosition)
{
	this->position = newPosition;
}

void Renderer::SetDirection(const Vector2& newDirection)
{
	this->direction = newDirection;
}

void Renderer::ClearBuffer(char buffer[1000][1000])
{
	// 배열의 각 요소를 \0으로 초기화
	for (int i = 0; i < 1000; ++i) {
		memset(buffer[i], '\0', 1000);
	}
}
