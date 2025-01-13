#include "Game.h"

Game::Game()
{
	// 콘솔 출력 빨라지게 설정
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	// 커서 안보이게 설정.
	SetCursorType(CursorType::NoCursor);
	SetConsoleEnableVTmode();
}

Game::~Game()
{
}