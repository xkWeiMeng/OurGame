#pragma once
#include<iostream>
#include"DirectX.h";
using namespace std;
//������Դ��·��
namespace Resource {
    namespace Home {
        char* const Backgroud = "Resources\\Home\\UI.bmp";
        //char* const BGM = "Resources\\Home\\3.wav";
        const D3DCOLOR SelectedColor = D3DCOLOR_XRGB(255, 128, 128);
        const D3DCOLOR UnselectedColor = D3DCOLOR_XRGB(64, 64, 64);

        char* const OptionsStr[] = { "������Ϸ","������Ϸ","��������" };
    }
    namespace Cursor {
        char* const Normal = "Resources\\Cursor\\Normal.png";
    }
    namespace About {
        char* const Backgroud = "Resources\\About\\Background.jpg";

    }
	namespace Sound_Rescource {
		char* const Start = "Resources\\Sound\\��ʼ1.wav";
		char*const Moving = "Resources\\Sound\\̹���ƶ�.wav";
		char*const Stop = "Resources\\Sound\\̹��ֹͣ�ƶ�.wav";
		char*const GameOver = "Resources\\Sound\\��Ϸ����.aif";

	}
	namespace Texture {
		char*const Flag = "Resources\\Texture\\����.bmp";
		char*const Something = "Resources\\Texture\\����.bmp";
		char*const Tile = "Resources\\Texture\\ש.bmp";
		char*const Player_1 = "Resources\\Texture\\���һ.bmp";
		char*const Player_2 = "Resources\\Texture\\��Ҷ�.bmp";
		char*const Bullet = "Resources\\Texture\\�ӵ�.bmp";
		char*const Boom1 = "Resources\\Texture\\��ըһ.bmp";
		char*const Boom2 = "Resources\\Texture\\��ը��.bmp";
		char*const Enemy = "Resources\\Texture\\����.bmp";
		char*const Award = "Resources\\Texture\\����.bmp";
		char*const GameOver = "Resources\\Texture\\��Ϸ����.bmp";
		char*const Shield = "Resources\\Texture\\����.bmp";

	}
}
