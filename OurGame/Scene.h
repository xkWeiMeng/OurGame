#pragma once
#include"DirectX.h"
#include"DirectSound.h"
//所有场景的基类，用于统一接口调用
class Scene
{
public:
    virtual bool Init() { return true; };
    virtual void End() {};
    virtual void Render() {};
    virtual void Update() {};
};