#pragma once
#include"DirectX.h"
#include"DirectSound.h"

//���г����Ļ��࣬����ͳһ�ӿڵ���
class Scene
{
public:
    virtual ~Scene() {};
    virtual bool Init() { return true; };
    virtual void End() {};
    virtual void Render() {};
    virtual void Update() {};
};