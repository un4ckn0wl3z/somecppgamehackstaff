#include <iostream>
#include <Windows.h>


int main() {



	while (true)
	{
		LPCWSTR window_title = L"Zuma Deluxe 1.0";
		HWND hWND = FindWindow(NULL, window_title);

		while (hWND == NULL)
		{
			hWND = FindWindow(NULL, window_title);
			std::cout << "Start game!" << std::endl;
		}

		Sleep(1000);
		if (GetAsyncKeyState(VK_NUMPAD1)) {
			std::cout << "Numpad 1 pressed" << std::endl;
			POINT p;
			//HDC hDC = GetDC(hWND);
			GetCursorPos(&p);
			ScreenToClient(hWND, &p);
			//ReleaseDC(hWND, hDC);
			std::cout << "x pos: " << p.x << " | " << "y pos: " << p.y << std::endl;

			Sleep(1000);
		}
		if (GetAsyncKeyState(VK_NUMPAD2)) {
			std::cout << "Numpad 2 pressed" << std::endl;
			HDC hDC = GetDC(hWND);
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(hWND, &p);
			COLORREF color = GetPixel(hDC, p.x, p.y);
			ReleaseDC(hWND, hDC);
			std::cout << "color: " << color << std::endl;
			std::cout << "RED: " << (int)GetRValue(color) << " | " << "Green: " << (int)GetGValue(color) << " | " << "Blue: " << (int)GetBValue(color) << std::endl;
			Sleep(1000);
		}
		if (GetAsyncKeyState(VK_NUMPAD3)) {
			std::cout << "Numpad 3 pressed" << std::endl;
			Sleep(1000);
		}
		if (GetAsyncKeyState(VK_NUMPAD0)) {
			return 0;
		}

	}

	return 0;
}