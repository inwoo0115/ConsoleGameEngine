#include "Game.h"

Game::Game()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	// 커서 안보이게 설정.
	SetCursorType(CursorType::NoCursor);
}

Game::~Game()
{
}