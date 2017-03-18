#pragma once
#include<iostream>
using namespace std;
enum GAME_STATE
{
    //无任何场景（初始状态）
    None = -1,
    //欢迎场景
    Home = 0,
    //游戏场景
    Playing = 1
};
namespace Global {
    namespace Window {
        const string GameTitle = "Our Game";
        const int ScreenWidth = 1024;
        const int ScreenHeight = 768;
        const bool FULLSCREEN = false;
    }
}
