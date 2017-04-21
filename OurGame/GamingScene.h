#pragma once
#include"Scene.h"
#include"DirectX.h"
#include"Global.h"
#include"Sound.h"
enum Dirction {
	up,
	right,
	below,
	lift
};
class Bullet {
public:
	SPRITE bullet;
	int Shooter;//子弹射击者
	int Speed;//子弹速度
	int Dir;//子弹方向
	unsigned long ID;
	int BoomFlag;
	bool Power;
	Bullet(int,int ,int,int,int);//子弹初始化
	bool B_Crash_and_Move();//子弹碰撞检测
	bool Draw();
private:

};
struct BulletList {
	Bullet*bullet;
	BulletList*next;
	BulletList*last;

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
	bool Draw();
	bool Logic(int);
};
class Enemy :public Player
{
public:
	Enemy(int x,int y,int speed,int hp,int as,int,int,int);
	bool Draw();
	int DamageFlag;//毁坏标志
	int XY;		//敌人坐标表的位置
	bool MoveStage;//移动状态
	unsigned long ID;

};


struct EnemyList {
	Enemy *enemy;
	EnemyList*last, *next;
};

struct EnemyListHead {
	EnemyList*next;
};

class BoomFire {
public:
	int x;
	int y;
	unsigned long ID;
	int Dir;
	int Time;
	int WhatBoom;
	bool Draw();
	BoomFire(int ,int ,int ,int);
};
struct BoomList{
	BoomFire*boom;
	BoomList*last, *next;
};
struct BoomListHead {
	BoomList*next;
};

//无用对象链表
struct UselessObj{
	unsigned long ID;
	UselessObj*next;
};
struct UselessObjHead
{
	UselessObj*next;
};