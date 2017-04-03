#pragma once
#include<iostream>
#include"DirectX.h";
using namespace std;
//所有资源的路径
namespace Resource {
    namespace Home {
        char* const Backgroud = "Resources\\Home\\UI.bmp";
        //char* const BGM = "Resources\\Home\\3.wav";
        const D3DCOLOR SelectedColor = D3DCOLOR_XRGB(255, 128, 128);
        const D3DCOLOR UnselectedColor = D3DCOLOR_XRGB(64, 64, 64);

        char* const OptionsStr[] = { "单人游戏","多人游戏","关于我们" };
    }
    namespace Cursor {
        char* const Normal = "Resources\\Cursor\\Normal.png";
    }
    namespace About {
        char* const Backgroud = "Resources\\About\\Background.jpg";

    }
	namespace Sound_Rescource {
		char* const Start = "Resources\\Sound\\开始1.wav";
		char*const Moving = "Resources\\Sound\\坦克移动.wav";
		char*const Stop = "Resources\\Sound\\坦克停止移动.wav";
		char*const GameOver = "Resources\\Sound\\游戏结束.aif";

	}
	namespace Texture {
		char*const Flag = "Resources\\Texture\\旗子.bmp";
		char*const Something = "Resources\\Texture\\杂项.bmp";
		char*const Tile = "Resources\\Texture\\砖.bmp";
		char*const Player_1 = "Resources\\Texture\\玩家一.bmp";
		char*const Bullet = "Resources\\Texture\\子弹.bmp";

	}
}
