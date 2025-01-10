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

private:
	std::vector<std::vector<int>> grid;
	Vector2 position;
	Vector2 direction;
	double width;
	double distance;
	double height;

	char buffer[1000][1000] = {};
};

