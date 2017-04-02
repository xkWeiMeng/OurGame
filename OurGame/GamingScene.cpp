#include "GamingScene.h"

LPDIRECT3DSURFACE9 GrayRect=NULL;
LPDIRECT3DSURFACE9 BlackRect = NULL;
/*����*/
LPDIRECT3DTEXTURE9 Flag = NULL;
LPDIRECT3DTEXTURE9 Something = NULL;
LPDIRECT3DTEXTURE9 Tile = NULL;
LPDIRECT3DTEXTURE9 Player_1 = NULL;
/*����*/
Player player;

BulletListHead bulletlisthead;
int Map[13][13] = { 0 };//��ͼ

Player::Player()
{
	Health_Point = 1;
	Speed = 1;
	Attack_Speed = 1;
	Dir = Dirction::up;
	Grade = 1;
	player.scaling = 2;
	player.columns = 8;
	player.frame = 0;
	player.color= D3DCOLOR_XRGB(255, 255, 255);
	player.x = 64;
	player.y = 64;
	player.width = 28;
	player.height = 28;
}
bool Player::Shoot(Dirction, int BulletSpeed) {
	Bullet*b = new Bullet;
	return 0;
}


Bullet::Bullet() {

}


void FillRect(RECT&rect,long l, long r, long t, long b)
{
	rect.left = l;
	rect.right = r;
	rect.top = t;
	rect.bottom = b;
}
void DrawNet()
{
	RECT rect;
	for (int i = 0; i < 12; i++)
	{
		FillRect(rect, 128 + i * 64, 129 + i * 64, 64, 896);
		d3dDev->StretchRect(BlackRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
	}

	for (int i = 0; i < 12; i++)
	{
		FillRect(rect, 64, 896, 128 + i * 64, 129 + i * 64);
		d3dDev->StretchRect(BlackRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
	}
}
GamingScene::GamingScene()
{
	
}


GamingScene::~GamingScene()
{

}

bool GamingScene::Init()
{
	Sound::Sound_Init();//��ʼ��������Դ
	Sound::Start->Play();
	HRESULT result = d3dDev->CreateOffscreenPlainSurface(
		100,
		100,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&GrayRect,
		NULL
	);
	if (result != D3D_OK)
	{
		ShowMessage("��ɫ-���� ��ʼ��ʧ�ܣ�");
		return false;
	}

	result = d3dDev->CreateOffscreenPlainSurface(
		100,
		100,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&BlackRect,
		NULL
	);
	if (result != D3D_OK)
	{
		ShowMessage("��ɫ-���� ��ʼ��ʧ�ܣ�");
		return false;
	}
	d3dDev->ColorFill(GrayRect, NULL, D3DCOLOR_XRGB(110,110,110));
	d3dDev->ColorFill(BlackRect, NULL, D3DCOLOR_XRGB(69, 139, 116));

	Flag = LoadTexture(Resource::Texture::Flag, D3DCOLOR_XRGB(255, 255, 255));
	if (!Flag)
	{
		ShowMessage("װ�� ���� ����ʧ�ܣ�");
		return false;
	}
	Something = LoadTexture(Resource::Texture::Something, D3DCOLOR_XRGB(255, 255, 255));
	if (!Something)
	{
		ShowMessage("װ�� ���� ����ʧ��!");
		return false;
	}
	Tile= LoadTexture(Resource::Texture::Tile, D3DCOLOR_XRGB(255, 255, 255));
	if (!Tile)
	{
		ShowMessage("װ�� ש ����ʧ��!");
		return false;
	}
	Player_1 = LoadTexture(Resource::Texture::Player_1, D3DCOLOR_XRGB(0, 0, 0));
	if (!Player_1)
	{
		ShowMessage("װ�� ����� ����ʧ��!");
		return false;
	}
	return 1;
}

void GamingScene::End()
{

}

void GamingScene::Render()
{
	if (!d3dDev) return;
	if (d3dDev->BeginScene())
	{
		d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		/*��Ϸ�߿�*/
		RECT rect;
		FillRect(rect, 0, 1024, 32, 64);   //�ֱ��ʲ�Ϊ1024*960ʱ��Ҫ�޸�
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 0, 64, 64, 896);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 896, 1024, 64, 896);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 0, 1024, 896, 928);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);

		DrawNet();//��������ʽ��ɾ��
		/*��Ϸ����*/
		spriteObj->Begin(D3DXSPRITE_ALPHABLEND);
		Sprite_Transform_Draw(Flag, 926, 704, 32, 32, 0, 1, 0, 2.0, D3DCOLOR_XRGB(255, 255, 255));
		//���һ����Ϣ
		Sprite_Transform_Draw(Something, 928, 512, 14, 14, 2, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 960, 512, 14, 14, 3, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 928, 544, 14, 14, 1, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		//��Ҷ�����Ϣ
		Sprite_Transform_Draw(Something, 928, 608, 14, 14, 4, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 960, 608, 14, 14, 3, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 928, 640, 14, 14, 1, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));

		Sprite_Transform_Draw(Player_1, player.player.x, player.player.y, player.player.width, player.player.height,
			player.player.frame, player.player.columns, 0, 2, D3DCOLOR_XRGB(255, 255, 255));

		spriteObj->End();
		d3dDev->EndScene();

		d3dDev->Present(NULL,NULL,NULL,NULL);
	}
}

void GamingScene::Update()
{
	if (KEY_DOWN(VK_UP))
	{
		player.player.y -= player.Speed;
		player.player.frame = 0;
	}
	if (KEY_DOWN(VK_DOWN))
	{
		player.player.y += player.Speed;
		player.player.frame = 16;
	}
	if (KEY_DOWN(VK_LEFT))
	{
		player.player.x -= player.Speed;
		player.player.frame = 24;
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		player.player.x += player.Speed;
		player.player.frame = 8;
	}
}
