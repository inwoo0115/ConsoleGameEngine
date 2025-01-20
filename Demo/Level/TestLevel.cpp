#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Actor/Player.h"
#include "Game/Game.h"
#include "Timer/Timer.h"

TestLevel::TestLevel(int width, int height)
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
	AddActor(new Player(Vector2(2, 2), Vector2(0, 1), grid, width));
	renderer = new Renderer(grid, Vector2(2, 2), Vector2(0, 1), width, height);
	timer = new Timer(0.3);
	totalTime = width;
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



	//글자 크기 처리
	Game::Get().SetConsoleFontSize(2, 3);
	Game::Get().SetConsoleScreenSize(420, 200);


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

	// ESC 키로 메뉴 화면.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}

	// 시간 지났을 시 종료 (추후 화면 전환으로 변경)
	if (totalTime < 2)
	{
		system("cls");
		Engine::Get().SetConsoleTextColor(7);
		Engine::Get().QuitGame();
	}

	// 출구에 왔을 시 종료 (추후 화면 전환으로 변경)
	if (grid[player->Position().y][player->Position().x] == 2)
	{
		system("cls");
		Engine::Get().SetConsoleTextColor(7);
		Engine::Get().QuitGame();
	}
}