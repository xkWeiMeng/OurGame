#include"GameMain.h"
#include"Global.h"
#include"Scenes.h"

//��ǰ��Ϸ�ĳ���
Scene *scene = NULL;

//��ǰ��Ϸ״̬
GAME_STATE Game_State;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// Startup and loading code goes here
bool Game_Init(HWND window)
{
	if (!Direct3D_Init(window, Global::Window::ScreenWidth, Global::Window::ScreenHeight, false))
	{
		ShowMessage("Direct3D��ʼ��ʧ��");
		return false;
	}

	//�л�����ӭ����
	Game_ChangeScene(GAME_STATE::Home);

	return true;
}

/*
	�߼�������
*/
void Game_Update(HWND window)
{
	if (scene != NULL)
		scene->Update();

	//����˳������º��˳���Ϸ
	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(window, WM_DESTROY, 0, 0);
}

/*
	��Ⱦ������
*/
void Game_Render(HWND window, HDC device)
{
	//ȷ��DX�Ѿ���Ч
	if (!d3ddev) return;

	//����
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 128, 0), 1.0f, 0);

	//��ʼ��Ⱦ
	if (d3ddev->BeginScene())
	{
		//���õ�ǰ��������Ⱦ����
		if (scene != NULL)
			scene->Render();

		//ֹͣ��Ⱦ
		d3ddev->EndScene();

		//�Ѻ�̨����ˢ��ǰ̨��ʾ
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}
//�л���Ϸ����
void Game_ChangeScene(GAME_STATE to)
{
	if (to != Game_State)
	{
		if (scene != NULL)
		{
			//�ͷŵ�ǰ��������Դ
			scene->End();
			delete scene;
		}
		switch (to)
		{
		case GAME_STATE::Home:
			scene = new HomeScene();
			//���ó����ĳ�ʼ������

			break;
		case GAME_STATE::Playing:
			scene = new GamingScene();

			break;
		default:
			break;
		}
		if (!scene->Init())
		{
			//���������ʼ�������������Ϸ
			EndApplication();
		}
		Game_State = to;
	}
}

// ֻ��������Ϣ�������е��ô˺�����Ҫ��ر���Ϸ������EndApplication()
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