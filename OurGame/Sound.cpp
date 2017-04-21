#include "Sound.h"


namespace Sound {
	 CSound*Start;
	 CSound*GameOver;
	 CSound*Moving;
	 CSound*Stop;
	 CSound*BGM;
}
using namespace Sound;

void Sound::Sound_Init()
{
	Start=LoadSound(Resource::Sound_Rescource::Start);
	if (Start == NULL)
		ShowMessage("��ʼ����װ��ʧ��");

	Moving = LoadSound(Resource::Sound_Rescource::Moving);
	if (Moving == NULL)
		ShowMessage("̹���ƶ�����װ��ʧ��");

	Stop = LoadSound(Resource::Sound_Rescource::Stop);
	if (Stop == NULL)
		ShowMessage("̹��ֹͣ��������װ��ʧ��");

	BGM = LoadSound(Resource::Sound_Rescource::BGM);
	if (BGM == NULL)
		ShowMessage("BGMװ��ʧ��");
	/*
	GameOver = LoadSound(Resource::Sound_Rescource::GameOver);
	if (GameOver == NULL)
		ShowMessage("��Ϸʧ������װ��ʧ��");
	*/
}

 