#pragma once
//所有场景的基类，用于统一接口调用
class Scene
{
public:
    virtual void Init() {};
    virtual void End() {};
    virtual void Render() {};
    virtual void Update() {};
};