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
	int Health_Point;//���Ѫ��
					 //	int X;	//��Һ�����
					 //	int Y;	//���������
	int Speed;//�ƶ��ٶ�
	int Attack_Speed;//�����ٶ�
	int Dir;//��ҷ���
	int Grade;//��ҵȼ�
	bool Shoot(Dirction, int BulletSpeed);
};
