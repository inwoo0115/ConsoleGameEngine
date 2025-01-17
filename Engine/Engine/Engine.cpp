#include "PreCompiledHeader.h"

#include "Engine.h"
#include <Windows.h>
#include <iostream>
#include <time.h>

#include "Level/Level.h"

// 스태틱 변수 초기화.
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr)
{
	//랜덤 시드 설정
	srand((unsigned int)time(nullptr));

	// 싱글톤 객체 설정.
	instance = this;

	// 기본 타겟 프레임 속도 설정.
	SetTargetFrameRate(60.0f);
}

Engine::~Engine()
{
	// 메인 레벨 메모리 해제.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
}

void Engine::Run()
{
	// 시작 타임 스탬프 저장.
	// timeGetTime 함수는 밀리세컨드(1/1000초) 단위.
	//unsigned long currentTime = timeGetTime();
	//unsigned long previousTime = 0;

	// CPU 시계 사용.
	// 시스템 시계 -> 고해상도 카운터. (10000000).
	// 메인보드에 시계가 있음.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//std::cout << "Frequency: " << frequency.QuadPart << "\n";

	// 시작 시간 및 이전 시간을 위한 변수.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = currentTime;

	// 프레임 제한.
	//float targetFrameRate = 90.0f;

	// 한 프레임 시간 계산.
	//float targetOneFrameTime = 1.0f / targetFrameRate;

	// Game-Loop.
	while (true)
	{
		// 종료 조건.
		if (quit)
		{
			break;
		}

		// 현재 프레임 시간 저장.
		//time = timeGetTime();
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;
		// 프레임 시간 계산.
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);
		// 프레임 확인.
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인).
			ProcessInput();
			if (shouldUpdate) 
			{
				Update(deltaTime);
				Draw();
			}
			// 키 상태 저장.
			SavePreviouseKeyStates();

			// 이전 프레임 시간 저장.
			previousTime = currentTime;
			if (mainLevel)
			{
				mainLevel->ProcessAddedAndDestroyedActor();
			}
			shouldUpdate = true;
		}
		//Sleep(1);
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
	// 메인 레벨 설정.
	mainLevel = newLevel;
}

void Engine::SetCursorType(CursorType cursorType)
{
	// 1. 커서 속성 구조체 설정.
	CONSOLE_CURSOR_INFO info = { };

	// 타입 별로 구조체 값 설정.
	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;

	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;

	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;

	}

	// 2. 설정.
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.x, position.y);
}

void Engine::SetCursorPosition(double x, double y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetConsoleTextColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Engine::SetConsoleEnableVTmode()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) return;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}

//TODO: 왠지 모르겠는데 작동을 안함
void Engine::SetConsoleFontSize(int fontSizeX, int fontSizeY) {
	// 콘솔 핸들 가져오기
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE) {
		//std::cerr << "Error: Unable to get console handle" << std::endl;
		return;
	}

	// 콘솔 글꼴 정보 구조체 초기화
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	// 현재 콘솔 글꼴 정보 가져오기
	if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
		//std::cerr << "Error: Unable to get console font info" << std::endl;
		return;
	}

	// 글꼴 크기 설정
	cfi.dwFontSize.X = fontSizeX; // 글자 너비
	cfi.dwFontSize.Y = fontSizeY; // 글자 높이
	wcscpy_s(cfi.FaceName, L"Cascadia Mono"); // 글꼴 이름 설정 (예: Consolas)

	// 글꼴 정보 설정
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Engine::SetConsoleScreenSize(int width, int height)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 콘솔 화면 버퍼 크기 설정
	COORD bufferSize;
	bufferSize.X = width;  // 콘솔 버퍼의 너비
	bufferSize.Y = height; // 콘솔 버퍼의 높이

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		std::cerr << "Error: Unable to get console screen buffer info." << std::endl;
		return;
	}

	// 최대 크기 확인
	int maxWidth = csbi.dwMaximumWindowSize.X;
	int maxHeight = csbi.dwMaximumWindowSize.Y;
	if (width > maxWidth || height > maxHeight) {
		std::cerr << "Error: Window size exceeds maximum screen resolution." << maxWidth << " " << maxHeight << std::endl;
	}

	if (!SetConsoleScreenBufferSize(hConsole, bufferSize)) {
		std::cerr << "Error: Unable to set console screen buffer size." << std::endl;
		return;
	}

	// 콘솔 창 크기 설정
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;

	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
		std::cerr << "Error: Unable to set console window size." << std::endl;
		return;
	}
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

bool Engine::IsKey()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		if (keyState[ix].isKeyDown)
			return true;
	}
	return false;
}

void Engine::QuitGame()
{
	// 종료 플래그 설정.
	quit = true;
}

Engine& Engine::Get()
{
	// 싱글톤 객체 반환.
	return *instance;
}

void Engine::ProcessInput()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].isKeyDown = (GetAsyncKeyState(ix) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// 레벨 업데이트.
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}
}

void Engine::Draw()
{
	// 레벨 그리기.
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}
}

void Engine::SavePreviouseKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyState[ix].wasKeyDown = keyState[ix].isKeyDown;
	}
}