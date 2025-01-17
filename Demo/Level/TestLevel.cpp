#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Actor/Player.h"
#include "Game/Game.h"
#include "Timer/Timer.h"

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
	timer = new Timer(0.3);
}

TestLevel::~TestLevel()
{
	if (renderer != nullptr)
		delete renderer;
	if (timer != nullptr)
		delete timer;
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	timer->Update(deltaTime);

	//Game::Get().SetConsoleFontSize(3, 3);
	//Game::Get().SetConsoleScreenSize(120, 30);

	//player rednering
	Player* player = dynamic_cast<Player*>(actors[0]);
	renderer->SetPosition(player->Position());
	renderer->SetDirection(player->Direction());
	renderer->SetStamina(player->GetStamina());
	renderer->SetTime(totalTime);
	renderer->Raycasting();

	//1초 타이머
	if (timer->IsTimeOut())
	{
		--totalTime;
		timer->Reset();
	}

	// ESC 키로 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}

	// 시간 지났을 시 종료
	if (totalTime < 2)
	{
		Engine::Get().QuitGame();
	}
}