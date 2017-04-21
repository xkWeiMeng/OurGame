#include "GamingScene.h"
#define EnemyNumberMAX 20
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
int Crash(int iswho, int x, int y, int speed, int dir, bool power,int shooter=0);
void AddUselessObj(unsigned long id);
bool DelListNode(EnemyList*listhead, unsigned long id);//删除成功返回true，否则返回false
bool DelListNode(BulletList*listhead, unsigned long id);//删除成功返回true，否则返回false
bool DelListNode(BoomList*listhead, unsigned long id);//删除成功返回true，否则返回false
void DelUselessObj();
void ClearUselessObj();
/*工具函数*/
BulletListHead bulletlisthead;//子弹链表头
EnemyListHead enemylisthead;//敌人链表头
UselessObjHead uselessobjhead;//失效对象链表头
BoomListHead boomlisthead;//爆炸链表头

static unsigned long IDNumber = 0;
int EnemyXY[EnemyNumberMAX][2];//敌人位置坐标表
int Map[13][13] = { //第一个是y轴，第二个是x轴
	{1,2,3,4,5,6,7,8,9,10,11,12,13},
	{2,14,15,16,17,18,19,20,21,22,23,24,25},
	{ 3,26,27,28,29,0,0,0,0,0,0,0,0 },
	{ 4,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 5,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 6,0,0,13,13,0,0,0,13,13,0,0,0 },
	{ 7,0,0,0,13,13,0,13,13,0,0,0,0 },
	{ 8,0,0,0,0, 0,13,0,0,0,0,0,0 },
	{ 9,0,0,0,0,0,13,0,0,0,0,0,0 },
	{10,0,0,0,13,13,0,13,13,0,0,0,0 },
	{11,0,0,13,13,0,0,0,13,13,0,0,0 },
	{12,0,0,0,0,0,0,0,0,0,0,0,0 },
	{13,0,0,0,0,0,0,0,0,0,0,0,0 },

};//地图

//敌人的构造函数
Enemy::Enemy(int x, int y, int speed, int hp, int as,int grade,int dir,int xy)
{
	player.x = x;
	player.y = y;
	Speed = speed;
	Health_Point = hp;
	Attack_Speed = as;
	Grade = grade;
	Dir = dir;
	XY = xy;
}
//敌人的渲染方法
bool Enemy::Draw()
{
	if (DamageFlag == 1)
	{
		return false;
	}
	else
	{
		if (Grade <= 3) {
			if (MoveStage) {
				Sprite_Transform_Draw(Enemy_TXTTURE, player.x, player.y, player.width, player.height,
					Dir * 8 + Grade * 2, player.columns, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
				MoveStage = !MoveStage;
			}
			else
			{
				Sprite_Transform_Draw(Enemy_TXTTURE, player.x, player.y, player.width, player.height,
					Dir * 8 + Grade * 2 + 1, player.columns, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
				MoveStage = !MoveStage;
			}
		}
		else
		{
			if (MoveStage) {
				Sprite_Transform_Draw(Enemy_TXTTURE, player.x, player.y, player.width, player.height,
					Dir * 8 + Grade * 2+24, player.columns, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
				MoveStage = !MoveStage;
			}
			else
			{
				Sprite_Transform_Draw(Enemy_TXTTURE, player.x, player.y, player.width, player.height,
					Dir * 8 + Grade * 2 + 25, player.columns, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
				MoveStage = !MoveStage;
			}
		}
		return true;
	}
	return false;
}

//初始化玩家信息
Player::Player()
{
	Health_Point = 1;//玩家血量
	Speed = 10;
	Attack_Speed = 10;
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
	Bullet*b = new Bullet(0,Player::player.x,Player::player.y,
		Player::BulletSpeed, Player::Dir);
	IDNumber++;
	b->ID = IDNumber;
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
		d->bullet = b;
		if (c->next != NULL)
		{
			d->next = c->next;
			c->next = d;
			d->next->last = d;
			d->last = c;
		}
		else
		{
			c->next = d;
			d->last = c;
			d->next = NULL;
		}
	}
		return true;
}
//玩家渲染方法
bool Player::Draw()
{

	return false;
}
//玩家逻辑方法
bool Player::Logic(int d)
{
	switch (d)
	{
	case Dirction::up:
		Dir = Dirction::up;
		player.y -=Speed;
		if (player.y < 64)
			player.y = 64;
		break;
	case Dirction::right:
		Dir = Dirction::right;
		player.x += Speed;
		if (player.x > 840)
			player.x = 840;
		break;
	case Dirction::below:
		Dir = Dirction::below;
		player.y += Speed;
		if (player.y > 840)
			player.y = 840;
		break;
	case Dirction::lift:
		Dir = Dirction::lift;
		player.x -= Speed;
		if (player.x < 64)
			player.x = 64;
		break;
	default:
		break;
	}
	return false;
}

//子弹对象构造函数
Bullet::Bullet(int shooter,int x, int y, int S, int D) :Speed(S), Dir(D),Shooter(shooter)
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
//子弹移动和碰撞检测方法
bool Bullet::B_Crash_and_Move()
{
	//碰撞检测
	int result = Crash( 0,bullet.x, bullet.y, Speed, Dir, Power);
	if (result == 1)
	{
		AddUselessObj(ID);//记录对象ID用于销毁
		//创建爆炸
		switch (Dir){
		case Dirction::up:
			bullet.x -= 22;
			bullet.y -= 5;
			break;
		case Dirction::below:
			bullet.x -= 22;
			bullet.y -= 25;
			break;
		case Dirction::lift:
			bullet.x -= 5;
			bullet.y -= 22;
			break;
		case Dirction::right:
			bullet.x -= 27;
			bullet.y -= 22;
			break;
		default:
			break;
		}
		BoomFire*b = new BoomFire(bullet.x, bullet.y, BoomFlag, Dir);
		IDNumber++;
		b->ID = IDNumber;
		BoomList*h = boomlisthead.next;
		BoomList*New = new BoomList;
		New->boom = b;
		if (h == NULL)
		{
			boomlisthead.next = New;
			New->last = NULL;
			New->next = NULL;
		}
		else
		{
			if (h->next != NULL)
			{
				New->next = h->next;
				h->next = New;
				New->next->last = New;
				New->last = h;
			}
			else
			{
				h->next = New;
				New->last = h;
				New->next = NULL;
			}
		}
	}
	if(result==2)
		BoomFlag = 2;
	//子弹逻辑移动
	if (result == 1 || result == 2)
		return true;
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
//子弹渲染方法
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
	else
	{
		return false;
	}

}
//碰撞检测
int Crash(int iswho,int x,int y,int speed,int dir,bool power,int shooter) {
	//先检测子弹是否碰撞到敌人
	RECT BulletRect = { x,y,x + 16,y + 16 };
	RECT EnemyRect,Rect;
	for (int i = 0; i < EnemyNumberMAX; i++)
	{
		if (EnemyXY[i][0] == -1)
			continue;
		EnemyRect.left=EnemyXY[i][0];
		EnemyRect.top=EnemyXY[i][1];
		EnemyRect.bottom = EnemyXY[i][1] + 56;
		EnemyRect.right = EnemyXY[i][0] + 56;
		if (IntersectRect(&Rect, &EnemyRect, &BulletRect))
		{
			EnemyList* ep = enemylisthead.next;
			while (ep != NULL)
			{
				if (ep->enemy->player.x == EnemyRect.left)
					if (ep->enemy->player.y == EnemyRect.top)
						ep->enemy->DamageFlag = true; 
				ep = ep->next;
			}
			return 2;//目前为测试状态 正式版应为爆炸2
		}
	}

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
//游戏地图绘画函数                   
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
//填充RECT
void FillRect(RECT&rect,long l, long r, long t, long b)
{
	rect.left = l;
	rect.right = r;
	rect.top = t;
	rect.bottom = b;
}
//画辅助网格
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
//清除失效对象
void ClearUselessObj()
{
	UselessObj*up = uselessobjhead.next;
	//清除失效子弹
	BulletList*b=bulletlisthead.next;
	while (up!=NULL)
	{
		while (b != NULL&&up!=NULL)
		{
			if (b->bullet->ID != up->ID)
				b = b->next;
			else
			{
				DelListNode(bulletlisthead.next, b->bullet->ID);
				DelUselessObj();
				up = uselessobjhead.next;
				break;
			}
		}
		if (bulletlisthead.next != NULL)
			b = bulletlisthead.next;
		if(up!=NULL)
		up = up->next;
	}
	//清除失效敌人
	up = uselessobjhead.next;
	EnemyList*ep = enemylisthead.next;
	while (up != NULL)
	{
		while (ep!=NULL&&up != NULL)
		{
			if (ep->enemy->ID != up->ID)
				ep = ep->next;
			else
			{
				DelListNode(enemylisthead.next, ep->enemy->ID);
				DelUselessObj();
				up = uselessobjhead.next;
				break;
			}
		}
		if (up != NULL)
			up = up->next;
	}
	//清除失效爆炸
	up = uselessobjhead.next;
	BoomList*bp = boomlisthead.next;
	while (up != NULL)
	{
		while (bp != NULL&&up != NULL)
		{
			if (bp->boom->ID != up->ID)
				bp = bp->next;
			else
			{
				DelListNode(boomlisthead.next, bp->boom->ID);
				DelUselessObj();
				up = uselessobjhead.next;
				break;
			}
		}
		if (up != NULL)
			up = up->next;
	}

}
//添加链表元素
/*
bool AddListNode(EnemyList*listhead, int id)
{
	if(listhead!=NULL)
		listhead->last=
}
*/
void AddUselessObj(unsigned long id)
{
	UselessObj*p = new UselessObj;
	p->next = uselessobjhead.next;
    p->ID = id;
	uselessobjhead.next = p;
}
//删除链表元素
void DelUselessObj()
{
	UselessObj*p = uselessobjhead.next;
	if(p!=NULL)
	uselessobjhead.next = p->next;
	delete p;
}
bool DelListNode(EnemyList*listhead, unsigned long id)//删除成功返回true，否则返回false
{
	EnemyList*p = listhead;
	while (p != NULL)
	{
		if (p->enemy->ID != id)
			p = p->next;
		else
		{
			if (p->last != NULL)
			{
				if (p->next != NULL) {
					p->last->next = p->next;
					p->next->last = p->last;
				}
				else
					p->last->next = NULL;
			}
			else if (p->next != NULL)
			{
				p->next->last = NULL;
				enemylisthead.next = p->next;
			}
			else
			{
				enemylisthead.next = NULL;
			}
			delete p;
			return true;
		}
	}
	return false;
}

bool DelListNode(BulletList*listhead, unsigned long id)//删除成功返回true，否则返回false
{
	BulletList*p = listhead;
	while (p != NULL)
	{
		if (p->bullet->ID != id)
			p = p->next;
		else
		{
			if (p->last != NULL)
			{
				if (p->next != NULL) {
					p->last->next = p->next;
					p->next->last = p->last;
				}
				else
					p->last->next = NULL;
			}
			else if (p->next != NULL)
			{
				p->next->last = NULL;
				bulletlisthead.next = p->next;
			}
			else
			{
				bulletlisthead.next = NULL;
			}
			delete p;
			return true;
		}
	}
	return false;
}

bool DelListNode(BoomList*listhead, unsigned long id)//删除成功返回true，否则返回false
{
	BoomList*p = listhead;
	while (p != NULL)
	{
		if (p->boom->ID != id)
			p = p->next;
		else
		{
			if (p->last != NULL)
			{
				if (p->next != NULL) {
					p->last->next = p->next;
					p->next->last = p->last;
				}
				else
					p->last->next = NULL;
			}
			else if (p->next != NULL)
			{
				p->next->last = NULL;
				boomlisthead.next = p->next;
			}
			else
			{
				boomlisthead.next = NULL;
			}
			delete p;
			return true;
		}
	}
	return false;
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
//场景初始化
bool GamingScene::Init()
{
	//
	srand((unsigned)time(0));

	for (int i = 0; i < EnemyNumberMAX; i++)//初始化敌人坐标表
	{
		EnemyXY[i][0] = -1;
		EnemyXY[i][1] = -1;
	}
	//
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
	Boom1 = LoadTexture(Resource::Texture::Boom1, D3DCOLOR_XRGB(0, 0, 0));
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
	Enemy_TXTTURE= LoadTexture(Resource::Texture::Enemy, D3DCOLOR_XRGB(4, 4, 4));
	if (!Enemy_TXTTURE)
	{
		ShowMessage("装载 敌人 纹理失败!");
		return false;
	}
	RECT rect;
	int n = 0,i=960;//无论窗口大小，游戏分辨率总是不变
	int delayNew=0, delayOld=GetTickCount();
	for (; n < Global::Window::ScreenHeight/2; n+=2,i-=2)
	{
		FillRect(rect, 0, 1024, n, n + 2);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		FillRect(rect, 0, 1024, i - 2, i);
		d3dDev->StretchRect(GrayRect, NULL, backBuffer, &rect, D3DTEXF_NONE);
		d3dDev->EndScene();
		d3dDev->Present(NULL, NULL, NULL, NULL);
	/*	while (1)
		{
			if (delayNew > delayOld + 1)
			{
				delayOld = delayNew;
				break;
			}
			delayNew = GetTickCount();
		}
		*/
	}
	Sound::Sound_Init();//初始化声音资源
	Sound::Start->Play();
	return 1;
}

void GamingScene::End()
{

}
//游戏渲染
void GamingScene::Render()
{
		d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		Sprite_Transform_Draw(Boom1, 600, 600,
			28, 28, 0, 1, 0, 2, D3DCOLOR_XRGB(255, 255, 255));

		Sprite_Transform_Draw(Boom2, 700, 700,
			64, 64, 0, 1, 0, 2, D3DCOLOR_XRGB(255, 255, 255));

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
		//渲染子弹 并清除已失效子弹
		BulletList*bp = bulletlisthead.next;
		while (bp != NULL)
		{
			bp->bullet->Draw();
			bp = bp->next;
		}
		
		//渲染敌人
		EnemyList *ep = enemylisthead.next, *ebuf;
		while (ep != NULL)
		{
			if (ep->enemy->Draw())
				ep = ep->next;
			else//销毁失效敌人
			{
				//先更新敌人坐标表信息
				EnemyXY[ep->enemy->XY][0] = -1;

				if (ep->last != NULL&&ep->next != NULL)
				{
					ebuf = ep->next;
					ep->last->next = ep->next;
					delete ep;
					ep = ebuf;
				}
				else if (ep->last == NULL&&ep->next == NULL)
				{
					delete ep;
					ep = NULL;
					enemylisthead.next = NULL;
				}
				else if (ep->last == NULL&&ep->next != NULL)
				{
					enemylisthead.next = ep->next;
					delete ep;
					ep = enemylisthead.next;
					ep->last = NULL;
				}
				else//敌人链表尾
				{
					ep->last->next = NULL;
					delete ep;
					ep = NULL;
				}
			}
		}

		//渲染爆炸
		BoomList *pboom = boomlisthead.next, *bbuf;
		while (pboom != NULL)
		{
			if (pboom->boom->Draw())
				pboom = pboom->next;
			else
			{
				if (pboom->last != NULL&&pboom->next != NULL)
				{
					bbuf = pboom->next;
					pboom->last->next = pboom->next;
					delete pboom;
					pboom = bbuf;
				}
				else if (pboom->last == NULL&&pboom->next == NULL)
				{
					delete pboom;
					pboom = NULL;
					boomlisthead.next = NULL;
				}
				else if (pboom->last == NULL&&pboom->next != NULL)
				{
					boomlisthead.next = pboom->next;
					delete pboom;
					pboom = boomlisthead.next;
					pboom->last = NULL;
				}
				else//爆炸链表尾
				{
					pboom->last->next = NULL;
					delete pboom;
					pboom = NULL;
				}
			}
		}


		DIDA();//产生时间信息
}
//游戏逻辑更新
void GamingScene::Update()
{
	static bool StarSoundPlaying = true;
	if (StarSoundPlaying)
		if (!Sound::Start->IsSoundPlaying())
		{
			Sound::BGM->Play(0, DSBPLAY_LOOPING);
			StarSoundPlaying = false;
		}

	if (KEY_DOWN(VK_UP)&&!KEY_DOWN(VK_RIGHT)&& !KEY_DOWN(VK_LEFT))
	{			
		player.Logic(Dirction::up);
		//up
	}
	if (KEY_DOWN(VK_DOWN) && !KEY_DOWN(VK_RIGHT) && !KEY_DOWN(VK_LEFT))
	{
		player.Logic(Dirction::below);
		//blow
	}
	if (KEY_DOWN(VK_LEFT))
	{
		player.Logic(Dirction::lift);
		//left
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		player.Logic(Dirction::right);
		//right
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
	//更新敌人逻辑
	static int BornEnemy =30;//生成敌人记时器
	static int NeedBornEnemy = 1;
	static int EnemyNumber = 0;
	if(NeedBornEnemy)
	if (ShowTime)//ShowTime 100ms一次
		BornEnemy++;

	if (BornEnemy >= 30)//生成新的敌人
	{
		EnemyNumber++;
		if (EnemyNumber > 10)
			NeedBornEnemy = 0;

		int NewEnemyX = rand() % 896;
		int NewEnemyY = rand() % 896;
		int EnemyI = 0;
		//更新敌人坐标表
		for (int i = 0; i < 20; i++)
		{
			if (EnemyXY[i][0] == -1) {
				EnemyXY[i][0] = NewEnemyX;
				EnemyXY[i][1] = NewEnemyY;
				EnemyI = i;
				break;
			}
		}
		//生成敌人对象
		Enemy*e = new Enemy(NewEnemyX,NewEnemyY,2,1,1,rand()%7,rand()%3,EnemyI);
		IDNumber++;
		e->ID = IDNumber;
		EnemyList*h = enemylisthead.next;
		EnemyList*newE = new EnemyList;
		newE->enemy = e;
		if (h == NULL)
		{
			enemylisthead.next = newE;
			newE->last = NULL;
			newE->next = NULL;
		}
		else
		{
			if (h->next != NULL)
			{
				newE->next = h->next;
				h->next = newE;
				newE->next->last = newE;
				newE->last = h;
			}
			else
			{
				h->next = newE;
				newE->last = h;
				newE->next = NULL;
			}
		}
		BornEnemy = 0;

	}
	//清除失效对象
	ClearUselessObj();
	//读取时间完毕 
	ShowTime = false;
}
//爆炸渲染方法
bool BoomFire::Draw()
{

	if (WhatBoom == 1)
	{
		Sprite_Transform_Draw(Boom1,x,y,
			28, 28, 0, 1, 0, 2, D3DCOLOR_XRGB(255, 255, 255));

	}
	else
	{
		Sprite_Transform_Draw(Boom1, x, y,
			28, 28, 0, 1, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		if (Time >= 50) {
			if (Time == 50)
				switch (Dir)//假定爆炸类型为boom1，其它爆炸类型在Draw()方法中修改
				{
				case Dirction::up:
					x -= 50;
					y -= 11;
					break;
				case Dirction::below:
					x -= 50;
					y -= 57;
					break;
				case Dirction::lift:
					x -= 11;
					y -= 50;
					break;
				case Dirction::right:
					x -= 61;
					y -= 50;
					break;
				default:
					break;
				}
			Sprite_Transform_Draw(Boom2, x, y,
				64, 64, 0, 1, 0, 2, D3DCOLOR_XRGB(255, 255, 255));
		}
	}
	Time++;
	if (Time >= 100)
		return false;
	else
		return true;
}

BoomFire::BoomFire(int x,int y,int wb,int d):
	x(x),y(y),WhatBoom(wb),Dir(d)
{
	Time = 0;
}
