#include <iostream>
#include <Windows.h>


int main() {

	while (true)
	{
		LPCWSTR window_title = L"Untitled - Paint";
		HWND hWND = FindWindow(NULL, window_title);

		while (hWND == NULL)
		{
			hWND = FindWindow(NULL, window_title);
			std::cout << "Start game!" << std::endl;
		}

		Sleep(10);
		if (GetAsyncKeyState(VK_NUMPAD0)) { // Exit
			return 0;
		}

		if (GetAsyncKeyState(VK_NUMPAD1)) { // Get Mouse-Pos
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(hWND, &p);
			std::cout << "x pos: " << p.x << " | " << "y pos: " << p.y << std::endl;
			Sleep(1000);
		}

		if (GetAsyncKeyState(VK_NUMPAD2)) { 
			INPUT input = {0};
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &input, sizeof(input));
			ZeroMemory(&input, sizeof(input));
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &input, sizeof(input));

		}

		if (GetAsyncKeyState(VK_NUMPAD3)) {
			INPUT input = { 0 };
			input.type = INPUT_KEYBOARD;
			input.ki.wVk = VkKeyScan('a');
			SendInput(1, &input, sizeof(input));
			ZeroMemory(&input, sizeof(input));
			input.mi.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &input, sizeof(input));
		}

		

	}

	return 0;
}