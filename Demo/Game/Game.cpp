#include "Game.h"
#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	// �ܼ� ��� �������� ����
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);


	// Ŀ�� �Ⱥ��̰� ����.
	SetCursorType(CursorType::NoCursor);
	//���� ���ڿ� ��밡��
	SetConsoleEnableVTmode();
	//�̱��� ��ü ����
	instance = this;
	//�޴����� ����
	menuLevel = new MenuLevel();
}

Game::~Game()
{
	// �� ���� ó��
	if (showMenu)
	{
		// Engine�� ���� ������ menu
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// ���η����� testlevel
		delete mainLevel;
		mainLevel = nullptr;
	}
	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	//ȭ�� �����
	system("cls");
	SetConsoleScreenSizeInit();
	// �� ������
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
