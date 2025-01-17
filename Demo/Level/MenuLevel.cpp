#include "MenuLevel.h"
#include "Game/Game.h"

MenuLevel::MenuLevel()
{
	items.emplace_back(new MenuItem("Resume Game", []() {Game::Get().ToggleMenu(); }));
	items.emplace_back(new MenuItem("Quit Game", []() {Game::Get().QuitGame(); }));

	//메뉴 개수 저장
	itemCount = (int)items.size();
}

MenuLevel::~MenuLevel()
{
	for (MenuItem* item : items)
	{
		delete item;
	}
	items.clear();
}

void MenuLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Game::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
	}

	if (Game::Get().GetKeyDown(VK_UP))
	{
		currentSelectIndex = (currentSelectIndex - 1 + itemCount) % itemCount;
	}
	
	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		currentSelectIndex = (currentSelectIndex + 1) % itemCount;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		items[currentSelectIndex]->onSelected();
	}
}

void MenuLevel::Draw()
{
	Super::Draw();
	
	//메뉴 제목 출력
	Game::Get().SetConsoleFontSize(36, 36);
	Game::Get().SetCursorPosition(Vector2(0, 0));
	Game::Get().SetConsoleTextColor(unselectedColor);
	std::cout << "Menu title\n\n";
	

	for (int ix = 0; ix < itemCount; ++ix)
	{
		Game::Get().SetConsoleTextColor(ix == currentSelectIndex ? selectedColor : unselectedColor);
		std::cout << items[ix]->text << "\n";
	}

}
