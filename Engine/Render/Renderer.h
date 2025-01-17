#pragma once

#include "Core.h"
#include "Math/Vector2.h"

class ENGINE_API Renderer
{
public:
	Renderer(std::vector<std::vector<int>> grid, Vector2 position, \
		Vector2 direction, double width, double height);
	~Renderer() {};


	void Raycasting();
	void CheckDistance(double rx, double ry);
	void DrawLine(int i);
	void DrawColor();
	void DrawInfo();

	//setter
	void SetPosition(const Vector2& newPosition);
	void SetDirection(const Vector2& newDirection);
	void SetGrid(std::vector<std::vector<int>> grid) { this->grid = grid; };
	void SetStamina(int stamina) { this->stamina = stamina; };
	void SetTime(int time) { this->time = time; };

	void ClearBuffer(char buffer[1000][1000]);

private:
	std::vector<std::vector<int>> grid;
	Vector2 position;
	Vector2 direction;
	double width;
	double distance;
	double height;

	int side = 0;
	int stamina;
	int time;

	char buffer[1000][1000] = {};
};

