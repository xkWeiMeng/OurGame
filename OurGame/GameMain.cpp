#include"GameMain.h"
#include"Global.h"
#include"Scenes.h"

//当前游戏的场景
Scene *scene = NULL;

//当前游戏状态
GAME_STATE Game_State;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// Startup and loading code goes here
bool Game_Init(HWND window)
{
    if (!Direct3D_Init(window, Global::Window::ScreenWidth, Global::Window::ScreenHeight, false))
    {
        ShowMessage("Direct3D初始化失败");
        return false;
    }

    //切换到欢迎场景
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
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0), 1.0f, 0);

    //start rendering
    if (d3ddev->BeginScene())
    {
        if (scene != NULL)
            scene->Render();

        //stop rendering
        d3ddev->EndScene();

        //copy back buffer to the frame buffer
        d3ddev->Present(NULL, NULL, NULL, NULL);
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
        //初始化新场景
        switch (to)
        {
        case GAME_STATE::Home:
            scene = new HomeScene();
            //调用场景的初始化函数
            if (!scene->Init())
            {
                //如果场景初始化出错则结束游戏
                EndApplication();
            }
            break;
        case GAME_STATE::Playing:
            break;
        default:
            break;
        }
        Game_State = to;
    }
}

// 只允许在消息处理函数中调用此函数，要想关闭游戏，调用EndApplication()
void Game_Free(HWND window, HDC device)
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