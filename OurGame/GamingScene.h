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
	Bullet();
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
	int Speed;//移动速度
	int Attack_Speed;//攻击速度
	int Dir;//玩家方向
	int Grade;//玩家等级
	bool Shoot(Dirction, int BulletSpeed);
};
