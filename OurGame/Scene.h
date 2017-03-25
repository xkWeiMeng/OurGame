#pragma once
#include"DirectX.h"
#include"DirectSound.h"

//���г����Ļ��࣬����ͳһ�ӿڵ���
class Scene
{
public:
    virtual ~Scene() {};
    //�����ĳ�ʼ�����������л�����ʱ�ᱻִ��һ��
    virtual bool Init() { return true; };
    //�����Ĺرպ��������л�����ʱ�ᱻִ��һ��
    virtual void End() {};
    //��������Ⱦ����
    virtual void Render() {};
    //�������߼����º���
    virtual void Update() {};
};