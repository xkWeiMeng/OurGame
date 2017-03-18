#include"GameMain.h"
#include<time.h>
#include<Windows.h>
#include"Global.h"
#include"Graph.h"
#include"Resource.h"
#include"Scenes.h"
#include"DirectX.h"
#include"Scenes.h"

//当前游戏的场景
Scene *scene = NULL;
//当前游戏状态
GAME_STATE Game_State;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// Startup and loading code goes here
bool Game_Init(HWND window)
{
    //start up the random number generator
    //srand(time(NULL));

    if (!Direct3D_Init(window, Global::Window::ScreenWidth, Global::Window::ScreenHeight, false))
    {
        MessageBox(window, "Direct3D初始化失败", Global::Window::GameTitle.c_str(), MB_OK);
        return false;
    }

    Game_ChangeScene(GAME_STATE::Home);

    return true;
}

/*
    逻辑处理函数
*/
void Game_Update(HWND window)
{
    if (scene != NULL)
        scene->Update();

    //check for escape key (to exit program)

    if (KEY_DOWN(VK_ESCAPE))
        PostMessage(window, WM_DESTROY, 0, 0);

  

}

/*
    渲染处理函数
*/
void Game_Render(HWND window, HDC device)
{
    //make sure the Direct3D device is valid
    if (!d3ddev) return;

    //clear the backbuffer to bright green
    //d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    //start rendering
    if (d3ddev->BeginScene())
    {
        //do something?
        if (scene != NULL)
            scene->Render();

        //stop rendering
        d3ddev->EndScene();

        //copy back buffer to the frame buffer
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }
}
//切换游戏场景用此函数，不可直接给Global::Game_State赋值
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
        //初始化新场景
        switch (to)
        {
        case GAME_STATE::Home:
            scene = new HomeScene();
            scene->Init();
            break;
        case GAME_STATE::Playing:
            break;
        default:
            break;
        }
        Game_State = to;
    }
}

// Shutdown code
void Game_End(HWND window, HDC device)
{
    if (scene != NULL)
    {
        scene->End();
        delete scene;
    }
    Direct3D_Shutdown();
    //free the device
    ReleaseDC(window, device);
}