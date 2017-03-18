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


}