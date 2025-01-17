#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();

	//½Ì±ÛÅæ Á¢±Ù ÇÔ¼ö
	static Game& Get() { return *instance; }

private:
	bool showMenu = false;

	//¾À º¯¼ö
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	// ½Ì±ÛÅæ ±¸Çö °´Ã¼
	static Game* instance;
};