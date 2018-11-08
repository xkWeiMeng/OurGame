#include "HomeScene.h"
#include "Global.h"
#include "DirectX.h"
#include"GameMain.h"


using namespace Global;
using namespace Global::Window;

bool HomeScene::Create_Background()
{
    background = LoadTexture(Resource::Home::Backgroud, D3DCOLOR_XRGB(255, 255, 255));
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

	Sprite_Transform_Draw(background, 150, 150, 686, 239,
		0, 1, 0, 1, D3DCOLOR_XRGB(255, 255, 255));
}

bool HomeScene::Init()
{
    OutputDebugString("��ӭ������ʼ��ʼ��\n");
    if (!HomeScene::Create_Background())
    {
        ShowMessage("����ͼ����ʧ��");
        return false;
    }

    HomeScene::choose = 0;
    HomeScene::font = MakeFont("΢���ź�", 32);
    //DXSound���������룬������ʱֻ֧��wav
    //if (bgm = LoadSound(Resource::Home::BGM), bgm == NULL) {
        //ShowMessage("BGM����ʧ��");
        //return false;
    //}
    //LoopSound(bgm);


    return true;
}
void HomeScene::End()
{
    //�ͷű���ͼ
    background->Release();
    //delete bgm;
}
void HomeScene::Update()
{
    //if (Mouse_Button(MLButton))
    //{
    //    OutputDebugString("�������");
    //}

    if (Key_Up(DIK_DOWN))
    {
        HomeScene::choose++;
        HomeScene::choose %= 3;
    }
    if (Key_Up(DIK_UP))
    {
        HomeScene::choose = HomeScene::choose > 0 ? HomeScene::choose - 1 : 2;
        HomeScene::choose %= 3;
    }
    if (Key_Up(DIK_SPACE))
    {
        Global::Home::selectedType = choose;
		Global::Window::Now_GAME_STATE = 1;
        switch (choose)
        {
        case 0:
			Game_ChangeScene(GAME_STATE::SinglePlayer);
            break;
		case 1:
			Game_ChangeScene(GAME_STATE::GameSatting);
			break;
        case 2:
            Game_ChangeScene(GAME_STATE::About);
            break;

        default:
            break;
        }
    }
}
void HomeScene::Render()
{
    HomeScene::Draw_Background();
    for (int i = 0; i < 3; i++) {
        FontPrint(font, 450, 500 + i * 40, Resource::Home::OptionsStr[i], i == HomeScene::choose ? Resource::Home::SelectedColor : Resource::Home::UnselectedColor);
    }
}