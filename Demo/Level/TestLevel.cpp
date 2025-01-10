﻿#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Actor/Player.h"

TestLevel::TestLevel()
{
	grid = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
	};

	AddActor(new Player(Vector2(5, 3), Vector2(0, 1)));
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	// 상태 변화가 있을 시
	Renderer renderer = Renderer(grid, actors[0]->Position(), actors[0]->Direction(), 300, 100);
	renderer.Raycasting();

	// ESC 키로 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}