#include"GameMain.h"
#include"Global.h"
#include"Scenes.h"
#include"DebugTools.h"
#include"GUIs.h"
//当前游戏的场景
Scene *scene = NULL;

//当前游戏状态
GAME_STATE Game_State;

// Startup and loading code goes here
bool Game_Init(HWND window)
{
    if (!Direct3D_Init(window, Global::Window::ScreenWidth, Global::Window::ScreenHeight, false))
    {
        ShowMessage("Direct3D初始化失败");
        return false;
    }
    if (!DirectInput_Init(window))
    {
        ShowMessage("Direct Input 初始化失败");
        return false;
    }

    GUI::Cursor::Init();

    //切换到欢迎场景
    Game_ChangeScene(GAME_STATE::Home);

    return true;
}

/*
    逻辑处理函数
*/
void Game_Update(HWND window)
{
    //获取最新的鼠标键盘输入
    DirectInput_Update(window);

    GUI::Cursor::Update();

    //执行当前场景的Update逻辑处理函数
    if (scene != NULL)
        scene->Update();

    //检测退出键按下后退出游戏
    if (Key_Down(DIK_ESCAPE))
        PostMessage(window, WM_DESTROY, 0, 0);
}

/*
    渲染处理函数
*/
void Game_Render(HWND window, HDC device)
{
    //确认DX已经生效
    if (!d3dDev) return;

    //清屏
    d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 255, 179, 167), 1.0f, 0);

    //开始渲染
    if (d3dDev->BeginScene())
    {
        spriteObj->Begin(D3DXSPRITE_ALPHABLEND);

        //调用当前场景的渲染函数
        if (scene != NULL)
            scene->Render();

        if (Global::Debug::ShowDebugInfo)
        {
            DebugTools::PrintMouseInfo();
        }


        GUI::Cursor::Render();

        spriteObj->End();
        d3dDev->EndScene();
        //把后台缓存刷到前台显示
        d3dDev->Present(NULL, NULL, NULL, NULL);
    }
}
//切换游戏场景
void Game_ChangeScene(GAME_STATE to)
{
    if (to != Game_State)
    {
        if (scene != NULL)
        {
            //释放当前场景的资源
            scene->End();
            delete scene;
        }
        switch (to)
        {
        case GAME_STATE::Home:
            scene = new HomeScene();
        case GAME_STATE::Playing:
            break;
        default:
            scene = NULL;
            break;
        }
        //调用场景的初始化函数
        if (scene == NULL && !scene->Init())
        {
            //如果场景初始化出错则结束游戏
            EndApplication();
        }
        Game_State = to;
    }
}

// 只允许在消息处理函数WinProc中调用此函数，要想关闭游戏，调用WinMain里的EndApplication
void Game_Free(HWND window, HDC device)
{
    //调用场景的关闭函数并释放场景
    if (scene != NULL)
    {
        scene->End();
        delete scene;
    }
    DirectInput_Shutdown();
    Direct3D_Shutdown();
    ReleaseDC(window, device);
}