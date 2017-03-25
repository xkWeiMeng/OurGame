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
    GUI::Cursor::Init();

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

    //����˳������º��˳���Ϸ
    if (Key_Down(DIK_ESCAPE))
        PostMessage(window, WM_DESTROY, 0, 0);
}

/*
    ��Ⱦ������
*/
void Game_Render(HWND window, HDC device)
{
    //ȷ��DX�Ѿ���Ч
    if (!d3dDev) return;

    //����
    d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 255, 179, 167), 1.0f, 0);

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
            scene = new HomeScene();
        case GAME_STATE::Playing:
            break;
        case GAME_STATE::About:
            scene = new AboutScene();
            break;
        default:
            scene = NULL;
            break;
        }
        //���ó����ĳ�ʼ������
        if (scene == NULL || !scene->Init())
        {
            //���������ʼ�������������Ϸ
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