#include "AboutScene.h"
#include"DirectX.h"
#include"GameMain.h"

int STime = 0, NTime, SurTime = 0;
bool SoTime = false;
void DD() {
	NTime = (int)GetTickCount();
	if (NTime > STime + 100)
	{
		if (STime != 0)
			SurTime = NTime - STime + 100;
		STime = NTime;
		SoTime = true;
	}
}

bool AboutScene::Init()
{
    background = LoadSurface(Resource::About::Backgroud);
	Could1 = LoadTexture(Resource::About::Cloud1, D3DCOLOR_XRGB(255, 255, 255));
	Could2 = LoadTexture(Resource::About::Cloud2, D3DCOLOR_XRGB(255, 255, 255));
	Could3 = LoadTexture(Resource::About::Cloud3, D3DCOLOR_XRGB(255, 255, 255));
	Mountain = LoadTexture(Resource::About::BKG);
	Feiting =LoadTexture(Resource::About::Feiting);
 //   return background != NULL;



	Sound::Sound_Init();
	LoopSound(Sound::BGM);
	return true;
}

void AboutScene::End()
{
	Sound::BGM->Stop();
    background->Release();
}

/*
SPRITE sprite[5];
sprite[0].height = 80;
sprite[0].width = 200;
sprite[0].x = 124;
sprite[0].y = 440;

sprite[1].height = 144;
sprite[1].width = 354;
sprite[1].x = 600;
sprite[1].y = 300;

sprite[2].height = 62;
sprite[2].width = 210;
sprite[2].x = 700;
sprite[2].y = 700;

sprite[3].height = 135;
sprite[3].width = 314;
sprite[3].x = 211;
sprite[3].y = 0;
*/
void AboutScene::Render()
{
	d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    RECT source_rect = {
        0,
        0,
        Global::Window::ScreenWidth,
        Global::Window::ScreenHeight
    };

  //  d3dDev->StretchRect(Mountain, NULL, backBuffer, &source_rect, D3DTEXF_NONE);
	Sprite_Transform_Draw(Mountain, 0, 120, 1000, 625, 0, 1, 0, 1.03, D3DCOLOR_XRGB(255, 255, 255));
	/**
	Sprite_Transform_Draw(Could1, sprite[0].x, sprite[0].y, sprite[0].width, sprite[0].height, 0, 1, 1.1, 1, D3DCOLOR_XRGB(255, 255, 255));
	Sprite_Transform_Draw(Could2, 0, 180, 1000, 625, 0, 1, 1.1, 1, D3DCOLOR_XRGB(255, 255, 255));
	Sprite_Transform_Draw(Could3, 0, 180, 1000, 625, 0, 1, 1.1, 1, D3DCOLOR_XRGB(255, 255, 255));
	Sprite_Transform_Draw(Feiting, 0, 180, 1000, 625, 0, 1, 1.1, 1, D3DCOLOR_XRGB(255, 255, 255));
	*/
	DD();//产生时间信息
}

void AboutScene::Update()
{
	
    if (Key_Up(DIK_SPACE))
    {
        Game_ChangeScene(GAME_STATE::Home);
    }
	SoTime = false;
}
