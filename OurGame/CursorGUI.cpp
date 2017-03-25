#include "CursorGUI.h"
#include"DirectX.h"

namespace GUI {
    namespace Cursor {
        LPDIRECT3DTEXTURE9 Cursor_Texture = NULL;
        SPRITE Cursor;

        //����ǰ���λ�ø��µ���꾫��λ��
        void Update() {
            Cursor.x = mousePoint.x;
            Cursor.y = mousePoint.y;
        }
        void Render() {
            Sprite_Transform_Draw(
                Cursor_Texture,
                Cursor.x, Cursor.y,
                Cursor.width,
                Cursor.height,
                0, 1, 0.0f, 1.0f,
                D3DCOLOR_XRGB(255, 255, 255));
        }
        bool Init()
        {
            D3DXIMAGE_INFO Info;
            //�õ�ͼƬ�ļ���Ϣ��Info
            if (D3D_OK != (D3DXGetImageInfoFromFile(Resource::Cursor::Normal, &Info)))
            {
                MessageBox(NULL, "�õ�ͼ����Ϣ����!", "LOAD PIC ERROR", MB_OK);
            }
            Cursor_Texture = LoadTexture(Resource::Cursor::Normal);
            if (!Cursor_Texture) return false;

            Cursor.x = Cursor.y = 0;
            Cursor.width = Info.Width;
            Cursor.height = Info.Height;
        }
    }
}
