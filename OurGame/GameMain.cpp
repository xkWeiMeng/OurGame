#include"GameMain.h"
#include<time.h>
#include<Windows.h>
#include"Global.h"
#include"Graph.h"
#include"Resource.h"
// Startup and loading code goes here
bool Game_Init()
{
    //start up the random number generator
    srand(time(NULL));

    return 1;
}

/*
    逻辑处理函数
*/
void Game_Update(HWND window)
{
    if (Global::Gameover == true) return;

    //get the drawing surface
    RECT rect;
    GetClientRect(window, &rect);

    //draw bitmap at random location
    int x = rand() % (rect.right - rect.left);
    int y = rand() % (rect.bottom - rect.top);

}

/*
    渲染处理函数
*/
void Game_Render(HWND window, HDC device)
{
    Graph::DrawBitmap(device, Resource::Backgroud, 0, 0);
}

// Shutdown code
void Game_End(HWND window, HDC device)
{
    //free the device
    ReleaseDC(window, device);
}