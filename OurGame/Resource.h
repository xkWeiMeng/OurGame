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

        char* const OptionsStr[] = { "������Ϸ","˫����Ϸ","��Ƶ�ͼ","��Ϸ�趨","��������" };
    }
    namespace Cursor {
        char* const Normal = "Resources\\Cursor\\���.png";
    }
    namespace About {
        char* const Backgroud = "Resources\\About\\Background.jpg";
		char* const BKG = "Resources\\About\\ɽ��.bmp";
		char* const Cloud1 = "Resources\\About\\��1.png";
		char* const Cloud2 = "Resources\\About\\��2.png";
		char* const Cloud3 = "Resources\\About\\��3.png";
		char* const Feiting = "Resources\\About\\��ͧ.tga";

    }
	namespace Sound_Rescource {
		char* const Start = "Resources\\Sound\\��ʼ1.wav";
		char*const Moving = "Resources\\Sound\\̹���ƶ�.wav";
		char*const Stop = "Resources\\Sound\\̹��ֹͣ�ƶ�.wav";
		char*const GameOver = "Resources\\Sound\\��Ϸ����.aif";
		char*const BGM = "Resources\\Sound\\bgm.wav";
		char*const PlayerBoom = "Resources\\Sound\\��ը.wav";
	}
	namespace Texture {
		char*const Flag = "Resources\\Texture\\����.bmp";
		char*const Something = "Resources\\Texture\\����.bmp";
		char*const Tile = "Resources\\Texture\\ש.bmp";
		char*const Player_1 = "Resources\\Texture\\wxz.png";
		char*const Player_1_L = "Resources\\Texture\\wxzL.png";

		char*const Player_2 = "Resources\\Texture\\��Ҷ�.bmp";
		char*const Bullet = "Resources\\Texture\\���.png";
		char*const Boom1 = "Resources\\Texture\\��ըһ.bmp";
		char*const Boom2 = "Resources\\Texture\\��ը��.bmp";
		char*const Enemy = "Resources\\Texture\\����.bmp";
		char*const Award = "Resources\\Texture\\����.bmp";
		char*const GameOver = "Resources\\Texture\\��Ϸ����.bmp";
		char*const Shield = "Resources\\Texture\\����.bmp";
		char*const Hole = "Resources\\Texture\\��.bmp";
		char*const Number = "Resources\\Texture\\����.bmp";
		char*const GameSetting = "Resources\\Texture\\GameSetting.png";
	}
}
