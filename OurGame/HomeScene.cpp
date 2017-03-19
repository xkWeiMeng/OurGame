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
    OutputDebugString("»¶Ó­³¡¾°¿ªÊ¼³õÊ¼»¯\n");
    if (!HomeScene::Create_Background())
    {
        ShowMessage("±³¾°Í¼ÔØÈëÊ§°Ü");
    }

    return true;
}
void HomeScene::End()
{
    //ÊÍ·Å±³¾°Í¼
    background->Release();
}
void HomeScene::Update()
{
    if (Mouse_Button(MLButton))
    {
        OutputDebugString("×ó¼üµ¥»÷");
    }
}
void HomeScene::Render()
{
    HomeScene::Draw_Background();

}