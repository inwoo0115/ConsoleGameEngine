#include "Game/Game.h"
#include "Level/TestLevel.h"
#include <Windows.h>
#include <iostream>

int main()
{
	Game game;
	game.LoadLevel(new TestLevel());
	game.Run();
}