#pragma once

#include "Level/Level.h"

class Renderer;
class Timer;

class TestLevel : public Level
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(TestLevel, Level)

public:
	TestLevel(int width, int height);
	~TestLevel();

	virtual void Update(float deltaTime) override;

private:
	std::vector<std::vector<int>> grid;

	Renderer* renderer;

	Timer* timer;

	int totalTime;
};