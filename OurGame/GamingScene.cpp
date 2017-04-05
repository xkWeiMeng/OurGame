#include "GamingScene.h"

LPDIRECT3DSURFACE9 GrayRect=NULL;
LPDIRECT3DSURFACE9 BlackRect = NULL;
/*纹理*/
LPDIRECT3DTEXTURE9 Flag = NULL;
LPDIRECT3DTEXTURE9 Something = NULL;
LPDIRECT3DTEXTURE9 Tile = NULL;
LPDIRECT3DTEXTURE9 Player_1 = NULL;
LPDIRECT3DTEXTURE9 Player_2 = NULL;
LPDIRECT3DTEXTURE9 Bullet_TXTTURE = NULL;
LPDIRECT3DTEXTURE9 Enemy_TXTTURE = NULL;
LPDIRECT3DTEXTURE9 Award = NULL;
LPDIRECT3DTEXTURE9 Boom1 = NULL;
LPDIRECT3DTEXTURE9 Boom2 = NULL;
LPDIRECT3DTEXTURE9 GameOver = NULL;
LPDIRECT3DTEXTURE9 Shield = NULL;
/*对象*/
Player player;
/*工具函数*/
int Crash(int x, int y, int w, int h, int speed, int dir, bool power);
BulletListHead bulletlisthead;
int Map[13][13] = { //第一个是y轴，第二个是x轴
	{1,2,3,4,5,6,7,8,9,10,11,12,13},
	{2,14,15,16,17,18,19,20,21,22,23,24,25},
	{ 3,26,27,28,29,0,0,0,0,0,0,0,0 },
	{ 4,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 5,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 6,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 7,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 8,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 9,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 10 ,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 11,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 12,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 13,0,0,0,0,0,0,0,0,0,0,0,0 },

};//地图

//初始化玩家信息
Player::Player()
{
	Health_Point = 1;
	Speed = 10;
	Attack_Speed = 5;
	Dir = Dirction::up;
	Grade = 0;
	player.scaling = 2;
	player.columns = 8;
	player.frame = 0;
	player.color= D3DCOLOR_XRGB(255, 255, 255);
	player.x = 64*6;
	player.y = 64*13;
	player.width = 28;
	player.height = 28;
	BulletSpeed = 10;
}
//玩家射击
bool Player::Shoot() {
	Bullet*b = new Bullet(Player::player.x,Player::player.y,
		Player::BulletSpeed, Player::Dir);
	if (b == NULL)
		return false;
	BulletList*c = bulletlisthead.next;
	if (c == NULL)
	{
		bulletlisthead.next = new BulletList;//将子弹插入子弹链表
		bulletlisthead.next->bullet = b;
		bulletlisthead.next->next = c;
		bulletlisthead.next->last = NULL;
	}
	else
	{
		BulletList*d = new BulletList;
		d->next = c->next;
		c->next = d;
		d->next->last = d;
	}
		return true;
}


Bullet::Bullet(int x, int y, int S, int D) :Speed(S), Dir(D)
{
	BoomFlag = 0;
	Power = false;
	bullet.width = 16;
	bullet.height = 16;
	switch (D)
	{
	case Dirction::up:
		bullet.x = x + 20;
		bullet.y = y - 8;
		break;
	case Dirction::below:
		bullet.x = x+20;
		bullet.y = y+56;
		break;
	case Dirction::lift:
		bullet.x = x-8;
		bullet.y = y+20;
		break;
	case Dirction::right:
		bullet.x = x + 56;
		bullet.y = y + 20;
		break;
	default:
		break;
	}
}

bool Bullet::B_Crash_and_Move()
{
	//碰撞检测
	if (Crash(bullet.x, bullet.y, bullet.width, bullet.height, Speed, Dir, Power) == 1)
		BoomFlag = 1;
	//子弹逻辑移动
	switch (Dir)
	{
	case Dirction::up:
		bullet.y -= Speed;
		break;
	case Dirction::below:
		bullet.y += Speed;
		break;
	case Dirction::lift:
		bullet.x -= Speed;
		break;
	case Dirction::right:
		bullet.x += Speed;
		break;
	default:
		break;
	}
	return false;
}

bool Bullet::Draw()
{
	if (BoomFlag == 0) {
		switch (Dir)
		{
		case Dirction::up:
			Sprite_Transform_Draw(Bullet_TXTTURE, bullet.x, bullet.y,
				8, 8, 0, 4, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			break;
		case Dirction::below:
			Sprite_Transform_Draw(Bullet_TXTTURE, bullet.x, bullet.y,
				8, 8, 2, 4, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			break;
		case Dirction::lift:
			Sprite_Transform_Draw(Bullet_TXTTURE, bullet.x, bullet.y,
				8, 8, 3, 4, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			break;
		case Dirction::right:
			Sprite_Transform_Draw(Bullet_TXTTURE, bullet.x, bullet.y,
				8, 8, 1, 4, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			break;
		default:
			break;
		}
		return true;
	}
	else if (BoomFlag == 1)
	{

		return false;
	}
	else
	{
		return false;

	}
}

int Crash(int x,int y,int w,int h,int speed,int dir,bool power) {
	int X = x / 64;
	int Y = y / 64;
	if ((x + speed) < 64 || (x + speed) > 896 || (y + speed) < 64 || (y + speed) > 896)
		return 1;
	switch (Map[Y-1][X-1])
	{
	case 0:
		break;
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	case 18:
		break;
	case 19:
		break;
	case 20:
		break;
	case 21:
		break;
	case 22:
		break;
	case 23:
		break;
	case 24:
		break;
	case 25:
		break;
	case 26:
		break;
	case 27:
		break;
	case 28:
		break;
	case 29:
		break;
	default:
		break;
	}
}

void DrawMap()
{
for (int i = 0; i<13; i++)
	for (int j = 0; j < 13; j++){
		switch (Map[j][i])
		{
		case 0:break;
			//
		case 13:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			32, 32, 0, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 26:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			32, 32, 1, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 27:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			32, 32, 2, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 28:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			32, 32, 3, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 29:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			32, 32, 4, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
			//
		case 1:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			16, 16, 0, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255));break;
		case 2:Sprite_Transform_Draw(Tile, 64*i+96, (j + 1) * 64,
			16, 16, 1, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 3:Sprite_Transform_Draw(Tile, 64*i+96, 64*j+96,
			16, 16, 14, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 4:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
			16, 16, 15, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 5:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 64,
			32, 16, 0, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 6:Sprite_Transform_Draw(Tile, 64 * i + 96, 64 * j + 64,
			16, 32, 1, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 7:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
			32, 16, 0, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 8:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 64,
			16, 32, 1, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 9:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 64,
			16, 32, 1, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, 64 * i + 96, (j + 1) * 64,
				16, 16, 1, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 10:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
				16, 16, 0, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, 64 * i + 96, 64 * j + 64,
				16, 32, 1, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 11:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
			32, 16, 0, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, 64 * i + 96, (j + 1) * 64,
				16, 16, 14, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 12:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 64,
			16, 32, 1, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, 64 * i + 96, (j + 1) * 96,
				16, 16, 15, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 14:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			16, 16, 2, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 15:Sprite_Transform_Draw(Tile, 64 * i + 96, (j + 1) * 64,
			16, 16, 3, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 16:Sprite_Transform_Draw(Tile, 64 * i + 96, 64 * j + 96,
			16, 16, 16, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 17:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
			16, 16, 17, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 18:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 64,
			32, 16, 1, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 19:Sprite_Transform_Draw(Tile, 64 * i + 96, 64 * j + 64,
			16, 32, 3, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 20:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
			32, 16, 1, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 21:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 64,
			16, 32, 2, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;

		case 22:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 64,
			32, 16, 1, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
				16, 16, 17, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 23:Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
			16, 16, 2, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, 64 * i + 96, 64 * j + 64,
				16, 32, 3, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 24:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
			32, 16, 1, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, 64 * i + 96, (j + 1) * 64,
				16, 16, 3, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		case 25:Sprite_Transform_Draw(Tile, 64 * i + 64, 64 * j + 96,
			32, 16, 1, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			Sprite_Transform_Draw(Tile, (i + 1) * 64, (j + 1) * 64,
				16, 16, 2, 14, 0, 2, D3DCOLOR_XRGB(255, 255, 255)); break;
		default:
			break;
		}
}
}

/*工具函数*/
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

//产生时间脉冲
int StartTime = 0,NowTime,SurplusTime=0;
bool ShowTime = false;
void DIDA() {
	NowTime = (int)GetTickCount();
	if (NowTime > StartTime + 100)
	{
		if (StartTime != 0)
			SurplusTime = NowTime - StartTime + 100;
		StartTime = NowTime;
		ShowTime = true;
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
		ShowMessage("灰色-格子 初始化失败！");
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
		ShowMessage("黑色-格子 初始化失败！");
		return false;
	}
	d3dDev->ColorFill(GrayRect, NULL, D3DCOLOR_XRGB(110,110,110));
	d3dDev->ColorFill(BlackRect, NULL, D3DCOLOR_XRGB(69, 139, 116));

	Flag = LoadTexture(Resource::Texture::Flag, D3DCOLOR_XRGB(255, 255, 255));
	if (!Flag)
	{
		ShowMessage("装载 旗子 纹理失败！");
		return false;
	}
	Something = LoadTexture(Resource::Texture::Something, D3DCOLOR_XRGB(255, 255, 255));
	if (!Something)
	{
		ShowMessage("装载 杂项 纹理失败!");
		return false;
	}
	Tile= LoadTexture(Resource::Texture::Tile, D3DCOLOR_XRGB(4, 4, 4));
	if (!Tile)
	{
		ShowMessage("装载 砖 纹理失败!");
		return false;
	}
	Player_1 = LoadTexture(Resource::Texture::Player_1, D3DCOLOR_XRGB(0, 0, 0));
	if (!Player_1)
	{
		ShowMessage("装载 主玩家 纹理失败!");
		return false;
	}
	Bullet_TXTTURE = LoadTexture(Resource::Texture::Bullet, D3DCOLOR_XRGB(4, 4, 4));
	if (!Bullet_TXTTURE)
	{
		ShowMessage("装载 子弹 纹理失败!");
		return false;
	}
	Boom1 = LoadTexture(Resource::Texture::Boom1, D3DCOLOR_XRGB(4, 4, 4));
	if (!Boom1)
	{
		ShowMessage("装载 爆炸一 纹理失败!");
		return false;
	}
	Boom2 = LoadTexture(Resource::Texture::Boom2, D3DCOLOR_XRGB(4, 4, 4));
	if (!Boom2)
	{
		ShowMessage("装载 爆炸二 纹理失败!");
		return false;
	}
	Player_2 = LoadTexture(Resource::Texture::Player_2, D3DCOLOR_XRGB(0, 0, 0));
	if (!Player_2)
	{
		ShowMessage("装载 玩家二 纹理失败!");
		return false;
	}
	Award = LoadTexture(Resource::Texture::Award, D3DCOLOR_XRGB(234, 234, 234));
	if (!Award)
	{
		ShowMessage("装载 奖励 纹理失败!");
		return false;
	}
	Shield = LoadTexture(Resource::Texture::Shield, D3DCOLOR_XRGB(234, 234, 234));
	if (!Shield)
	{
		ShowMessage("装载 盾牌 纹理失败!");
		return false;
	}
	GameOver = LoadTexture(Resource::Texture::GameOver, D3DCOLOR_XRGB(234, 234, 234));
	if (!GameOver)
	{
		ShowMessage("装载 游戏结束 纹理失败!");
		return false;
	}

	RECT rect;
	int n = 0,i=960;//无论窗口大小，游戏分辨率总是不变
	for (; n < Global::Window::ScreenHeight/2; n+=2,i-=2)
	{
		FillRect(rect, 0, 1024, n, n + 2);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 0, 1024, i - 2, i);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		d3dDev->EndScene();
		d3dDev->Present(NULL, NULL, NULL, NULL);
	}
	Sound::Sound_Init();//初始化声音资源
	Sound::Start->Play();
	return 1;
}

void GamingScene::End()
{

}

void GamingScene::Render()
{
		d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
		/*游戏边框*/
		RECT rect;
		FillRect(rect, 0, 1024, 32, 64);   //分辨率不为1024*960时需要修改
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 0, 64, 64, 896);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 896, 1024, 64, 896);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 0, 1024, 896, 928);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);

		DrawNet();//画网格，正式版删除
		/*游戏内容*/
		spriteObj->Begin(D3DXSPRITE_ALPHABLEND);
		Sprite_Transform_Draw(Flag, 926, 704, 32, 32, 0, 1, 0, 2.0, D3DCOLOR_XRGB(255, 255, 255));
		//玩家一的信息
		Sprite_Transform_Draw(Something, 928, 512, 14, 14, 2, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 960, 512, 14, 14, 3, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 928, 544, 14, 14, 1, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		//玩家二的信息
		Sprite_Transform_Draw(Something, 928, 608, 14, 14, 4, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 960, 608, 14, 14, 3, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		Sprite_Transform_Draw(Something, 928, 640, 14, 14, 1, 6, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		//画玩家一
		static bool ChangeFrame = false; 
		if (ChangeFrame) {
			Sprite_Transform_Draw(Player_1, player.player.x, player.player.y, player.player.width, player.player.height,
				player.Dir * 8 + player.Grade * 2, player.player.columns, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			if (KEY_DOWN(VK_LEFT) ||KEY_DOWN(VK_RIGHT) || KEY_DOWN(VK_UP) || KEY_DOWN(VK_DOWN))
				ChangeFrame = !ChangeFrame;
		}
		else {
			Sprite_Transform_Draw(Player_1, player.player.x, player.player.y, player.player.width, player.player.height,
				player.Dir * 8 + player.Grade * 2 + 1, player.player.columns, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
			if (KEY_DOWN(VK_LEFT) || KEY_DOWN(VK_RIGHT) || KEY_DOWN(VK_UP) || KEY_DOWN(VK_DOWN))
				ChangeFrame = !ChangeFrame;
		}
		//画地图
		DrawMap();
		Sprite_Transform_Draw(Tile, 512, 832, 32, 32, 5, 7, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		//渲染子弹
		BulletList*bp = bulletlisthead.next,*buf;
		while (bp != NULL)
		{
			if(bp->bullet->Draw())
			bp = bp->next;
			else
			{
				if (bp->last != NULL&&bp->next != NULL) {
					buf = bp->next;
					bp->last->next = bp->next;
					delete bp;
					bp = buf;
				}
				else if (bp->last == NULL)
					bulletlisthead.next = bp->next;
				else
					delete bp;
			}
		}
		
		DIDA();//产生时间信息
}
void GamingScene::Update()
{

	if (KEY_DOWN(VK_UP)&&!KEY_DOWN(VK_RIGHT)&& !KEY_DOWN(VK_LEFT))
	{
		player.player.y -= player.Speed;
		player.Dir = Dirction::up;
	}
	if (KEY_DOWN(VK_DOWN) && !KEY_DOWN(VK_RIGHT) && !KEY_DOWN(VK_LEFT))
	{
		player.player.y += player.Speed;
		player.Dir = Dirction::below;
	}
	if (KEY_DOWN(VK_LEFT))
	{
		player.player.x -= player.Speed;
		player.Dir = Dirction::lift;
		player.player.frame = 24;
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		player.player.x += player.Speed;
		player.Dir = Dirction::right;
	}
	//玩家射击
	static int ShootTime=10;
	if (ShowTime)
		ShootTime++;
	if (KEY_DOWN(0x58))
	{

		if (ShootTime > 10 / player.Attack_Speed)
		{
			player.Shoot();
			ShootTime = 0;
		}
		
	}
	//更新子弹逻辑
	BulletList*bp = bulletlisthead.next;
	while (bp!= NULL)
	{
		bp->bullet->B_Crash_and_Move();
		bp = bp->next;
	}
	//读取时间完毕 
	ShowTime = false;
}
