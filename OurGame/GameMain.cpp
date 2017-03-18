#include"GameMain.h"
#include<time.h>
#include<Windows.h>
#include"Global.h"
#include"Graph.h"
#include"Resource.h"

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

//Direct3D objects
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;


// Startup and loading code goes here
bool Game_Init(HWND window)
{
    //start up the random number generator
    srand(time(NULL));

    //initialize Direct3D
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (d3d == NULL)
    {
        MessageBox(window, "Error initializing Direct3D", "Error", MB_OK);
        return FALSE;
    }

    //set Direct3D presentation parameters
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = Global::Window::ScreenWidth;
    d3dpp.BackBufferHeight = Global::Window:: ScreenHeight;
    d3dpp.hDeviceWindow = window;

    //create Direct3D device
    d3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev);

    if (d3ddev == NULL)
    {
        MessageBox(window, "Error creating Direct3D device", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;
}

/*
    逻辑处理函数
*/
void Game_Update(HWND window)
{
    if (Global::Gameover == true) return;


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
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    //start rendering
    if (d3ddev->BeginScene())
    {
        //do something?

        //stop rendering
        d3ddev->EndScene();

        //copy back buffer to the frame buffer
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }
}

// Shutdown code
void Game_End(HWND window, HDC device)
{
    //free the device
    ReleaseDC(window, device);
}