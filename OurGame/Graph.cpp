#include"Graph.h"
#include<Windows.h>
#include"Resource.h"
namespace Graph {
    // Loads and draws a bitmap from a file and then frees the memory
    // (not really suitable for a game loop but it's self contained)
    void DrawBitmap(HDC device, const char *filename, int x, int y)
    {
        //load the bitmap image
        HBITMAP image = (HBITMAP)LoadImage(0, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        //read the bitmap's properties
        BITMAP bm;
        GetObject(image, sizeof(BITMAP), &bm);

        //create a device context for the bitmap
        HDC hdcImage = CreateCompatibleDC(device);
        SelectObject(hdcImage, image);

        //draw the bitmap to the window (bit block transfer)
        BitBlt(
            device,                  //destination device context
            x, y,                    //x,y position
            bm.bmWidth, bm.bmHeight, //size of source bitmap
            hdcImage,                //source device context
            0, 0,                    //upper-left source position
            SRCCOPY);                //blit method

                                     //delete the device context and bitmap
        DeleteDC(hdcImage);
        DeleteObject((HBITMAP)image);
    }
    float GetFPS()
    {
        static float  fps = 0;
        static int    frameCount = 0;
        static float  currentTime = 0.0f;//当前时间
        static float  lastTime = 0.0f;//持续时间

        frameCount++;//每调用一次Get_FPS()函数，帧数+1
        currentTime = timeGetTime()*0.001f;//获取系统时间,并转化成秒为单位
                                           //经过了一秒，就进行一次FPS的计算和持续时间的更新，并将帧数值清零
        if (currentTime - lastTime > 1.0f) //将时间控制在1秒钟
        {
            fps = (float)frameCount / (currentTime - lastTime);//计算这1秒钟的FPS值
            lastTime = currentTime; //将当前时间currentTime作为下一秒的基准时间
            frameCount = 0;//将本次帧数frameCount值清零
        }
        return fps;
    }
}