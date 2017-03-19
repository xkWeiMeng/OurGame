#pragma once
#include<iostream>
#include<Windows.h>
#include"Resource.h"
#include"WinMain.h"
#include"DirectX.h"

using namespace std;
enum GAME_STATE
{
    //无任何场景（初始状态）
    None = 0,
    //欢迎场景
    Home = 1,
    //游戏场景
    Playing = 2
};
namespace Global {
    namespace Window {
        const string GameTitle = "Our Game";
        const int ScreenWidth = 1024;
        const int ScreenHeight = 768;
        const bool FULLSCREEN = false;
        //指定逻辑刷新速度
        const float targetFps = 60.0f;
    }
    namespace Debug {
        const bool ShowDebugInfo = true;
        //当前总帧率
        extern int currentFPS;
    }
}
