#include "AboutScene.h"
#include"DirectX.h"
#include"GameMain.h"
bool AboutScene::Init()
{
    background = LoadSurface(Resource::About::Backgroud);
    return background != NULL;
}

void AboutScene::End()
{
    background->Release();
}

void AboutScene::Render()
{
    RECT source_rect = {
        0,
        0,
        Global::Window::ScreenWidth,
        Global::Window::ScreenHeight
    };
    d3dDev->StretchRect(background, NULL, backBuffer, &source_rect, D3DTEXF_NONE);
}

void AboutScene::Update()
{
    if (Key_Up(DIK_SPACE))
    {
        Game_ChangeScene(GAME_STATE::Home);
    }
}
