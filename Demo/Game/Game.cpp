#include "Game.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	// 콘솔 출력 빨라지게 설정
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);


	// 커서 안보이게 설정.
	SetCursorType(CursorType::NoCursor);
	//색상 문자열 사용가능
	SetConsoleEnableVTmode();
	//싱글톤 객체 설정
	instance = this;
	//메뉴레벨 생성
	menuLevel = new MenuLevel();
}

Game::~Game()
{
	// 씬 삭제 처리
	if (showMenu)
	{
		// Engine의 메인 레벨이 menu
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// 메인레벨이 testlevel
		delete mainLevel;
		mainLevel = nullptr;
	}
	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	//화면 지우기
	system("cls");
	SetConsoleScreenSizeInit();
	// 값 뒤집기
	showMenu = !showMenu;

	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}
}
