#pragma once
#include<iostream>
#include<Windows.h>
#include"Resource.h"
#include"WinMain.h"
#include"DirectX.h"

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
    About = 5
};
namespace Global {
    namespace Window {
        const string GameTitle = "Our Game";
        const int ScreenWidth = 1024;
        const int ScreenHeight = 960;
        //���ڵ�����
        extern int x, y;
        extern bool EnableBackgroundRunning;
        extern bool isActity;
        //���������
        const float CursorSensitivity = 1.0f;
        const bool FullScreen =  false;
        //ָ���߼�ˢ���ٶ�
        const float targetFps = 480.0f;
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

}
