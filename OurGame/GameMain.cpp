#include"GameMain.h"
#include"Global.h"
#include"Scenes.h"

//当前游戏的场景
Scene *scene = NULL;

//当前游戏状态
GAME_STATE Game_State;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// Startup and loading code goes here
bool Game_Init(HWND window)
{
	if (!Direct3D_Init(window, Global::Window::ScreenWidth, Global::Window::ScreenHeight, false))
	{
		ShowMessage("Direct3D初始化失败");
		return false;
	}

	//切换到欢迎场景
	Game_ChangeScene(GAME_STATE::Home);

	return true;
}

/*
	逻辑处理函数
*/
void Game_Update(HWND window)
{
	if (scene != NULL)
		scene->Update();

	//检测退出键按下后退出游戏
	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(window, WM_DESTROY, 0, 0);
}

/*
	渲染处理函数
*/
void Game_Render(HWND window, HDC device)
{
	//确认DX已经生效
	if (!d3ddev) return;

	//清屏
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0), 1.0f, 0);

	//开始渲染
	if (d3ddev->BeginScene())
	{
		//调用当前场景的渲染函数
		if (scene != NULL)
			scene->Render();

		//停止渲染
		d3ddev->EndScene();

		//把后台缓存刷到前台显示
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}
//切换游戏场景
void Game_ChangeScene(GAME_STATE to)
{
	if (to != Game_State)
	{
		if (scene != NULL)
		{
			//释放当前场景的资源
			scene->End();
			delete scene;
		}
		switch (to)
		{
		case GAME_STATE::Home:
			scene = new HomeScene();
			//调用场景的初始化函数

			break;
		case GAME_STATE::Playing:
			scene = new GamingScene();

			break;
		default:
			break;
		}
		if (!scene->Init())
		{
			//如果场景初始化出错则结束游戏
			EndApplication();
		}
		Game_State = to;
	}
}

// 只允许在消息处理函数中调用此函数，要想关闭游戏，调用EndApplication()
void Game_Free(HWND window, HDC device)
{
	if (scene != NULL)
	{
		scene->End();
		delete scene;
	}
	Direct3D_Shutdown();
	//free the device
	ReleaseDC(window, device);
}