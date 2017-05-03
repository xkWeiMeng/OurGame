#pragma once
#include<fstream>
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
	float MovedPixel;
	unsigned long ID;
	int BoomFlag;
	bool Power;
	Bullet(int,int ,int,int,int);//子弹初始化
	bool Logic();//子弹碰撞检测
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
	int FlickerFrame;
	int Health_Point;//玩家血量
	int BulletSpeed;//玩家子弹飞行速度
	int Speed;//移动速度
	int Attack_Speed;//攻击速度
	int Dir;//玩家方向
	int Grade;//玩家等级
	bool Shoot(int);
	bool Draw();
	bool Logic(int);
	bool GetHurt(int power);
};
class Enemy :public Player
{
public:
	Enemy(int x,int y,int speed,int hp,int as,int,int);
	bool Draw();
	bool Logic(bool);
	int DamageFlag;//毁坏标志
	bool MoveStage;//移动状态
	bool CrashingFlag;//碰撞标志
	unsigned long ID;
	int Time;
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
	void Logic();
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
struct RectList
{
	RECT*rect;
	RectList*last, *next;
};
struct RectListHead {
	RectList*next;
};
class MapPiece {
public:
	int X;
	int Y;
	RectListHead*rectlisthead;
	MapPiece();
	void Draw();
	void CreateMapRect(int x, int y, int wight, int hight);
	bool Create(int mapid);
	bool BeingCrash(bool,RECT&rect,int dir,int x,int y);
	int PECrach(int dir,RECT&rect);
};
struct  MapPieceList
{
	MapPiece*mappiece;
	MapPieceList*last, *next;
};
struct MapPieceListHead {
	MapPieceList*next;
};
