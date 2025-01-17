#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Actor/Player.h"
#include "Game/Game.h"

TestLevel::TestLevel()
{
	grid = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 3, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 3, 0, 0, 0, 2, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
	};

	//초기 설정
	AddActor(new Player(Vector2(2, 2), Vector2(0, 1), grid));
	Log("[Maze runner]\n");
	Log("Move player with arrow keys\n");
	Log("Enter to Yellow Gate to escape\n");
	Log("and Press button to Start!");
	renderer = new Renderer(grid, Vector2(2, 2), Vector2(0, 1), 400, 150);
}

TestLevel::~TestLevel()
{
	if (renderer != nullptr)
		delete renderer;
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	Game::Get().SetConsoleFontSize(12, 12);
	// totalTime += 1.0 * deltaTime;
	// 상태 변화가 있을 시 render
	if (Engine::Get().IsKey())
	{
		renderer->SetPosition(actors[0]->Position());
		renderer->SetDirection(actors[0]->Direction());
		renderer->Raycasting();
	}
	// ESC 키로 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}
}