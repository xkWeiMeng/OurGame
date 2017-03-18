#pragma once
#include<Windows.h>
bool Game_Init();
void Game_Update(HWND window);
void Game_End(HWND window, HDC device);
void Game_Render(HWND window, HDC device);