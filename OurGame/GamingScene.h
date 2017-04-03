#pragma once
#include"Scene.h"
#include"DirectX.h"
#include"Global.h"
#include"Sound.h"
enum Dirction {
	lift,
	right,
	up,
	below
};
class Bullet {
public:
	SPRITE bullet;
	int Speed;//子弹速度
	int Dir;//子弹方向
	Bullet(int ,int,int,int);//子弹初始化
	bool B_Crash_and_Move();//子弹碰撞检测
	void Draw();
private:

};
struct BulletList {
	Bullet*bullet;
	BulletList*next;
};

struct BulletListHead {
	BulletList*next;
};
class GamingScene:public Scene
{
public:
	GamingScene();
	~GamingScene();
	virtual bool Init();
	virtual void End();
	virtual void Render();
	virtual void Update();
};



class Player {
public:
	SPRITE player;
	Player();
	int Health_Point;//玩家血量
					 //	int X;	//玩家横坐标
					 //	int Y;	//玩家纵坐标
	int BulletSpeed;//玩家子弹飞行速度
	int Speed;//移动速度
	int Attack_Speed;//攻击速度
	int Dir;//玩家方向
	int Grade;//玩家等级
	bool Shoot();
};
