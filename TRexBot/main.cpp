#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

int get_Bitmap(int x, int y, HDC& hdcMemory, int width = 700, int height = 200) {
    HDC hdcSource = GetDC(NULL);
    hdcMemory = CreateCompatibleDC(hdcSource);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcSource, width, height);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);
    if (!BitBlt(hdcMemory, 0, 0, width, height, hdcSource, x, y, CAPTUREBLT | SRCCOPY)) {
        cout << "BitBlt failed!" << endl;
    }

    //clean up
    DeleteObject(hBitmapOld);
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hdcSource);

    return 0;
}

POINT get_tail(HDC& dc, POINT origin, int startx = 0, int starty = 0, int width = 700, int height = 200) {
    POINT p = { startx, starty };
    for (int i = startx; i < startx + width; i++) {//x
        for (int j = starty; j < starty + height; j++) {//y
            COLORREF color = GetPixel(dc, i, j);
            SetCursorPos(origin.x + i, origin.y + j);
            if (color == 5460819) {
                p = { i, j };
                return p;
            }
        }
    }
    return p;
}

int main() {
    HDC hdcMemory = NULL;
    POINT origin = {}, tail = {};//tail relative to origin
    int width = 350;
    int height = 200;
    int i = 0, j = 0, downtime = 320;
    COLORREF threat_color = 5460819;
    COLORREF color = NULL;

    cout << "[N1] Get Map" << endl;
    cout << "[N2] Get Tail" << endl;
    cout << "[N3] Start Bot" << endl;
    cout << "[N4] Pixel Info" << endl;
    cout << "[N0] Stop | Exit" << endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (GetAsyncKeyState(VK_NUMPAD0)) { // Exit
            if (hdcMemory != NULL)
                DeleteDC(hdcMemory);
            return 0;
        }
        if (GetAsyncKeyState(VK_NUMPAD1)) { // get map
            GetCursorPos(&origin);
            get_Bitmap(origin.x, origin.y, hdcMemory, width, height);
            cout << "We got the map!" << endl;
        }
        if (GetAsyncKeyState(VK_NUMPAD2)) { // get tail
            POINT p;
            GetCursorPos(&p);
            tail = get_tail(hdcMemory, origin, p.x - origin.x, p.y - origin.y, 30, 30);
            cout << "Oh f*ck it's a t-rex!" << endl;
        }
        if (GetAsyncKeyState(VK_NUMPAD4)) { // get pixel color
            POINT p;
            GetCursorPos(&p);
            if (hdcMemory != NULL) { // variable where hdc is stored
                COLORREF color = GetPixel(hdcMemory, p.x - origin.x, p.y - origin.y);
                cout << "Absolute values" << endl;
                cout << "X: " << p.x << " Y: " << p.y << " Color: " << color << endl;
            }
            else
                cout << "Get map first!" << endl;
        }
    }

}