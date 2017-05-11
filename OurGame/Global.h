#pragma once
#include<iostream>
#include<Windows.h>
#include"Resource.h"
#include"WinMain.h"
#include"DirectX.h"

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }  //�ͷ���Դ
using namespace std;
enum GAME_STATE
{
    //���κγ�������ʼ״̬��
    None = 0,
    //��ӭ����
    Home = 1,
    //��Ϸ����
    SinglePlayer = 2,
	DoublePlayer = 3,
	//��Ƶ�ͼ
	DesignMap=4,
    //���ڳ���
    About = 5,
	//��Ϸ�趨����
	GameSatting=6
};
namespace Global {
    namespace Window {
        const string GameTitle = "Our Game";
		extern int ScreenWidth;
		extern int ScreenHeight ;
        //���ڵ�����
        extern int x, y;
        extern bool EnableBackgroundRunning;
        extern bool isActity;
        //���������
        const float CursorSensitivity = 1.0f;
        const bool FullScreen =  false;
        //ָ���߼�ˢ���ٶ�
        const float targetFps = 480.0f;
		//��ǰ����Ϸ״̬
		extern int Now_GAME_STATE;
    }
    namespace Home {
        //���յ�ѡ�0��������Ϸ��1��˫����Ϸ��2����Ƶ�ͼ��3����������
        extern int selectedType;
    }
    namespace Debug {
        //�Ƿ���ʾ������Ϣ
        const bool ShowDebugInfo = true;
        //��ǰ��֡��
        extern int currentFPS;
    }
	namespace DesignMap {
		//����Ƶ�ͼ������
		extern string NewMapName;
	}
	namespace PlayerControl {
		//���һ�Ŀ��Ʒ�ʽ
		extern  int Player1[5];
		//��Ҷ��Ŀ��Ʒ�ʽ
		extern  int Player2[5];
	}
	namespace Sound {
		//���ֿ���
		extern bool SoundSwicth;
	}

}
