#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();

	//�̱��� ���� �Լ�
	static Game& Get() { return *instance; }

private:
	bool showMenu = false;

	//�� ����
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	// �̱��� ���� ��ü
	static Game* instance;
};