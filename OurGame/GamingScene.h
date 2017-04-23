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
	int Shooter;//�ӵ������
	int Speed;//�ӵ��ٶ�
	int Dir;//�ӵ�����
	unsigned long ID;
	int BoomFlag;
	bool Power;
	Bullet(int,int ,int,int,int);//�ӵ���ʼ��
	bool Logic();//�ӵ���ײ���
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
	int BulletSpeed;//����ӵ������ٶ�
	int Speed;//�ƶ��ٶ�
	int Attack_Speed;//�����ٶ�
	int Dir;//��ҷ���
	int Grade;//��ҵȼ�
	bool Shoot(int);
	bool Draw();
	bool Logic(int);
	bool GetHurt(int power);
};
class Enemy :public Player
{
public:
	Enemy(int x,int y,int speed,int hp,int as,int,int,int);
	bool Draw();
	bool Logic(bool);
	int DamageFlag;//�ٻ���־
	int XY;		//����������λ��
	bool MoveStage;//�ƶ�״̬
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

//���ö�������
struct UselessObj{
	unsigned long ID;
	UselessObj*next;
};
struct UselessObjHead
{
	UselessObj*next;
};