#pragma once
#include"Scene.h"
class AboutScene : public virtual Scene
{
public:
    bool Init();
    void End();
    void Render();
    void Update();
private:
    LPDIRECT3DSURFACE9 background = NULL;

};

