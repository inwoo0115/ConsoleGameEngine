#include "Game.h"

Game::Game()
{
	// �ܼ� ��� �������� ����
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	// Ŀ�� �Ⱥ��̰� ����.
	SetCursorType(CursorType::NoCursor);
	SetConsoleEnableVTmode();
}

Game::~Game()
{
}