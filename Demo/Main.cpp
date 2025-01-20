#include "Game/Game.h"
#include "Level/TestLevel.h"
#include <Windows.h>
#include <iostream>

int main()
{
	//Memory leak check
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.LoadLevel(new TestLevel(400, 150));
	game.Get().ToggleMenu();
	game.Run();
}