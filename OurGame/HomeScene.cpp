#include "HomeScene.h"
#include "Global.h"
#include "DirectX.h"
using namespace Global;
using namespace Global::Window;

bool HomeScene::Create_Background()
{
    background = LoadSurface(Resource::Home::Backgroud);
    return background != NULL;
}

void HomeScene::Draw_Background()
{
    RECT source_rect = {
        0,
        0,
        ScreenWidth,
        ScreenHeight
    };
    d3dDev->StretchRect(background, &source_rect, backBuffer, &source_rect, D3DTEXF_NONE);
}

bool HomeScene::Init()
{
    OutputDebugString("欢迎场景开始初始化\n");
    if (!HomeScene::Create_Background())
    {
        ShowMessage("背景图载入失败");
        return false;
    }
    //DXSound组件是软解码，库里暂时只支持wav
    //if (bgm = LoadSound(Resource::Home::BGM), bgm == NULL) {
        //ShowMessage("BGM载入失败");
        //return false;
    //}
    //LoopSound(bgm);


    return true;
}
void HomeScene::End()
{
    //释放背景图
    background->Release();
    //delete bgm;
}
void HomeScene::Update()
{
    if (Mouse_Button(MLButton))
    {
        OutputDebugString("左键单击");
    }
}
void HomeScene::Render()
{
    HomeScene::Draw_Background();

}