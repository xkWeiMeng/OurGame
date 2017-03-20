#pragma once
#include<iostream>
#include"DirectX.h";
using namespace std;
//所有资源的路径
namespace Resource {
    namespace Home {
        char* const Backgroud = "Resources\\Home\\1.bmp";
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
}
