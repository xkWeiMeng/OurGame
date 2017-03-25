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
    Playing = 2,
    //���ڳ���
    About = 3
};
namespace Global {
    namespace Window {
        const string GameTitle = "Our Game";
        const int ScreenWidth = 1024;
        const int ScreenHeight = 768;
        //���ڵ�����
        extern int x, y;
        extern bool EnableBackgroundRunning;
        extern bool isActity;
        //���������
        const float CursorSensitivity = 1.0f;
        const bool FullScreen = false;
        //ָ���߼�ˢ���ٶ�
        const float targetFps = 120.0f;
    }
    namespace Home {
        //���յ�ѡ�0��������Ϸ��1��������Ϸ��2����������
        extern int selectedType;
    }
    namespace Debug {
        //�Ƿ���ʾ������Ϣ
        const bool ShowDebugInfo = true;
        //��ǰ��֡��
        extern int currentFPS;
    }

}
