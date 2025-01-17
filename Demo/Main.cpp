#include "Game/Game.h"
#include "Level/TestLevel.h"
#include <Windows.h>
#include <iostream>

void ListSupportedFontSizes() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
    wcscpy_s(cfi.FaceName, L"Cascadia Mono");

    std::wcout << L"Supported font sizes for Cascadia Mono:" << std::endl;
    for (int y = 8; y <= 72; y += 2) { // 테스트 범위: 8~72 픽셀
        cfi.dwFontSize.Y = y;
        cfi.dwFontSize.X = y / 2; // 일반적인 가로:세로 비율 1:2 가정
        if (SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
            std::wcout << L" - " << cfi.dwFontSize.X << L"x" << cfi.dwFontSize.Y << std::endl;
        }
    }
}

int main()
{
	//Memory leak check
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.LoadLevel(new TestLevel(400, 150));
	game.Get().ToggleMenu();
	game.Run();
}