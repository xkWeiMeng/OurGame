#pragma once
#include<Windows.h>
#include"Global.h"
bool Game_Init(HWND window);
void Game_Update(HWND window);
void Game_End(HWND window, HDC device);
void Game_Render(HWND window, HDC device);
void Game_ChangeScene(GAME_STATE to);