#include "HomeScene.h"
#include "Global.h"
#include "DirectX.h"
using namespace Global;
using namespace Global::Window;

bool HomeScene::Create_Background()
{
    //load background
    LPDIRECT3DSURFACE9 image = NULL;
    image = LoadSurface(Resource::Home::Backgroud);
    if (!image) return false;

    HRESULT result =
        d3ddev->CreateOffscreenPlainSurface(
            ScreenWidth,
            ScreenHeight,
            D3DFMT_X8R8G8B8,
            D3DPOOL_DEFAULT,
            &background,
            NULL);
    if (result != D3D_OK) return false;

    //copy image to upper left corner of background
    RECT source_rect = { 0, 0, ScreenWidth, ScreenHeight };
    RECT dest_ul = { 0, 0, ScreenWidth, ScreenHeight };

    d3ddev->StretchRect(
        image,
        &source_rect,
        background,
        &dest_ul,
        D3DTEXF_NONE);

    //copy image to upper right corner of background
    RECT dest_ur = { ScreenWidth, 0, ScreenWidth * 2, ScreenHeight };

    d3ddev->StretchRect(
        image,
        &source_rect,
        background,
        &dest_ur,
        D3DTEXF_NONE);

    //get pointer to the back buffer
    d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,&backbuffer);

    //remove image
    image->Release();
    return true;

}
void HomeScene::Draw_Background()
{
    RECT source_rect = {
        0,
        0,
        ScreenWidth,
        ScreenHeight
    };
    RECT dest_rect = { 0, 0, ScreenWidth, ScreenHeight };
    d3ddev->StretchRect(background, &source_rect, backbuffer,
        &dest_rect, D3DTEXF_NONE);
}

bool HomeScene::Init()
{
    OutputDebugString("欢迎场景开始初始化");
    if (!HomeScene::Create_Background())
    {
        ShowMessage("背景图载入失败");
    }
    return true;
}
void HomeScene::End()
{

}
void HomeScene::Update()
{

}
void HomeScene::Render()
{
    HomeScene::Draw_Background();
}