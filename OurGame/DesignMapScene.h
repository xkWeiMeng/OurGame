#pragma once
#include"Scene.h"
#include<fstream>
#include"DirectX.h"
#include"Global.h"
#include"Sound.h"
#include"GameMain.h"
#include<string>
class DesignMapScene :public Scene
{
public:
	bool Init();

	void End();

	void Update();

	void Render();

};