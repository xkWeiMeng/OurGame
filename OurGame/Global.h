#pragma once
#include<iostream>
using namespace std;
namespace Global {
    namespace Window {
        const string GameTitle = "Our Game";
        const int ScreenWidth = 1024;
        const int ScreenHeight = 768;
    }
    extern bool Gameover;

}

//macro to detect key presses
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)