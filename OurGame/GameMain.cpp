#include"GameMain.h"
#include"Global.h"
#include"Scenes.h"
#include"DebugTools.h"
#include"GUIs.h"
#include"DirectSound.h"
//��ǰ��Ϸ�ĳ���
Scene *scene = NULL;

//��ǰ��Ϸ״̬
GAME_STATE Game_State;

//��ȡ��Ϸ����
bool ReadPlayerSettingInHD();

// Startup and loading code goes here
bool Game_Init(HWND window)
{
    if (!Direct3D_Init(window, Global::Window::ScreenWidth, Global::Window::ScreenHeight, Global::Window::FullScreen))
    {
        ShowMessage("Direct3D��ʼ��ʧ��");
        return false; 
    }
    if (!DirectInput_Init(window))
    {
        ShowMessage("Direct Input ��ʼ��ʧ��");
        return false;
    }
    if (!DirectSound_Init(window)) {
        ShowMessage("Direct Sound ��ʼ��ʧ��");
        return false;
    }
	//��ʼ��������Դ
	Sound::Sound_Init();
	//
    GUI::Cursor::Init();
	//
	ReadPlayerSettingInHD();
	//
	Global::Window::Now_GAME_STATE = 0;
	//��������
	//Global::Sound::SoundSwicth = true;
	//��ʼ����ҿ��Ƽ�  //��������Ҫ��ȡӲ���е���Ϸ����
	{
		//���һ
		Global::PlayerControl::Player1[0] = VK_UP;
		Global::PlayerControl::Player1[1] = VK_DOWN;
		Global::PlayerControl::Player1[2] = VK_LEFT;
		Global::PlayerControl::Player1[3] = VK_RIGHT;
		Global::PlayerControl::Player1[4] = 0x58;
		//��Ҷ�
		Global::PlayerControl::Player2[0] = 0x57;
		Global::PlayerControl::Player2[1] = 0x53;
		Global::PlayerControl::Player2[2] = 0x41;;
		Global::PlayerControl::Player2[3] = 0x44;
		Global::PlayerControl::Player2[4] = 0x4A;
	}
    //�л�����ӭ����
    Game_ChangeScene(GAME_STATE::Home);

    return true;
}

/*
    �߼�������
*/
void Game_Update(HWND window)
{
    //��ȡ���µ�����������
    DirectInput_Update(window);

    GUI::Cursor::Update();

    //ִ�е�ǰ������Update�߼�������
    if (scene != NULL)
        scene->Update();
	//�����������˳������º��˳���Ϸ
	if (Global::Window::Now_GAME_STATE == 0)
	{
		if (Key_Up(DIK_ESCAPE))
			PostMessage(window, WM_DESTROY, 0, 0);
	}
}

/*
    ��Ⱦ������
*/
void Game_Render(HWND window, HDC device)
{
    //ȷ��DX�Ѿ���Ч
    if (!d3dDev) return;

    //����
    d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 65, 105, 225 ), 1.0f, 0);

    //��ʼ��Ⱦ
    if (d3dDev->BeginScene())
    {
        spriteObj->Begin(D3DXSPRITE_ALPHABLEND);

        //���õ�ǰ��������Ⱦ����
        if (scene != NULL)
            scene->Render();

        if (Global::Debug::ShowDebugInfo)
        {
            DebugTools::PrintMouseInfo();
        }


        GUI::Cursor::Render();

        spriteObj->End();
        d3dDev->EndScene();
        //�Ѻ�̨����ˢ��ǰ̨��ʾ
        d3dDev->Present(NULL, NULL, NULL, NULL);
    }
}
//�л���Ϸ����
void Game_ChangeScene(GAME_STATE to)
{
    if (to != Game_State)
    {
        if (scene != NULL)
        {
            //�ͷŵ�ǰ��������Դ
            scene->End();
            delete scene;
        }
        switch (to)
        {
        case GAME_STATE::Home:
			Global::Window::Now_GAME_STATE = 0;
            scene = new HomeScene();
			break;
		case GAME_STATE::DoublePlayer:
        case GAME_STATE::SinglePlayer:
			Global::Window::Now_GAME_STATE = 1;
			scene = new GamingScene();
            break;
		case GAME_STATE::DesignMap:
			Global::Window::Now_GAME_STATE = 1;
			scene = new DesignMapScene();
			break;
        case GAME_STATE::About:
			Global::Window::Now_GAME_STATE = 1;
			scene = new AboutScene();
            break;
		case GAME_STATE::GameSatting:
			Global::Window::Now_GAME_STATE = 1;
			scene = new GameSettingScene();
			break;
        default:
			Global::Window::Now_GAME_STATE = 0;
			scene = NULL;
            break;
        }
        //���ó����ĳ�ʼ������
        if (scene == NULL || !scene->Init())
        {
            //���������ʼ�������������Ϸ
			//����Ӧ��������˵������
            EndApplication();
        }
        Game_State = to;
    }
}

// ֻ��������Ϣ������WinProc�е��ô˺�����Ҫ��ر���Ϸ������WinMain���EndApplication
void Game_Free(HWND window, HDC device)
{
    //���ó����Ĺرպ������ͷų���
    if (scene != NULL)
    {
        scene->End();
        delete scene;
    }
    DirectInput_Shutdown();
    DirectSound_Shutdown();
    Direct3D_Shutdown();
    ReleaseDC(window, device);
}
//��ȡ��Ϸ����
bool ReadPlayerSettingInHD()
{
	char buf;
	ifstream in("GameSet.set", ios::in | ios::binary);
	if (!in.is_open())
	{
		ShowMessage("�޷�����Ϸ�������ļ�");
		return false;
	}
	for (int i = 0; i < 5; i++)
	{
		in.read(&buf, 1);
		Global::PlayerControl::Player1[i]=buf;
	}
	for (int i = 0; i < 5; i++)
	{
		in.read(&buf, 1);
		Global::PlayerControl::Player2[i]=buf;
	}
	in.read(&buf, 1);
	Global::Sound::SoundSwicth=buf;
	in.close();
	return true;
}
