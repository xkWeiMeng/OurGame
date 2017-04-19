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
	int Speed;//�ӵ��ٶ�
	int Dir;//�ӵ�����
	int BoomFlag;
	bool Power;
	Bullet(int ,int,int,int);//�ӵ���ʼ��
	bool B_Crash_and_Move();//�ӵ���ײ���
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
	int Health_Point;//���Ѫ��
					 //	int X;	//��Һ�����
					 //	int Y;	//���������
	int BulletSpeed;//����ӵ������ٶ�
	int Speed;//�ƶ��ٶ�
	int Attack_Speed;//�����ٶ�
	int Dir;//��ҷ���
	int Grade;//��ҵȼ�
	bool Shoot();
};
class Enemy :public Player
{
public:
	Enemy(int x,int y,int speed,int hp,int as,int,int);
	bool Draw();
	int DamageFlag;
	bool MoveStage;

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
	int Time;
	int WhatBoom;
	bool Draw();
	BoomFire(int ,int ,int );
};
struct BoomList{
	BoomFire*boom;
	BoomList*last, *next;
};
struct BoomListHead {
	BoomList*next;
};