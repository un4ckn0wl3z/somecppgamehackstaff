#include "Helper.h"
int main() {
	LPCWSTR window_title = L"Zuma Deluxe 1.0";
	HWND hGameWindow = FindWindowW(NULL, window_title);
	while (hGameWindow == NULL)
	{
		hGameWindow = FindWindowW(NULL, window_title);
		std::cout << "Start game!" << std::endl;
		Sleep(1000);
		if (hGameWindow != NULL) {
			break;
		}
	}

	DWORD pid = NULL;
	GetWindowThreadProcessId(hGameWindow, &pid);
	char gameName[] = "Zuma.exe";
	Helper helper = Helper(pid);
	DWORD moduleBaseAddress = helper.GetModuleBaseAddress(gameName);
	std::vector<DWORD> pointsOffsets{ 0x147EF8, 0x14 ,0x174 ,0x55C ,0xD0 ,0xB8 };
	DWORD dynamicPointsAddress = helper.GetDynamicAddress(moduleBaseAddress, pointsOffsets);

	// Start  AOBScan with : 55 8B EC 8B 45 08 85 C0 56 8B F1 0F 8E BE 00 00 00 8B 8E B8 00 00 00  
	// xx8Bxx8Bxxxx85xxxx8Bxx0F8Exxxxxxxx8Bxxxxxxxxxx 

	std::vector<int> sig{0x55 ,-1, 0xEC, -1, 0x45, 0x08, -1, 0xC0, 0x56, -1, 0xF1, -1, -1, 0xBE, 0x00, 0x00, 0x00, -1, 0x8E, 0xB8, 0x00, 0x00, 0x00,};
	DWORD signature_ptr = helper.GetAddressFromSignature(sig);
	std::cout << "dynamicPointsAddress: = " << std::hex << dynamicPointsAddress << std::endl;
	std::cout << "signature_ptr: = " << std::hex << signature_ptr << std::endl;

	//"UI"
	std::cout << "Zuma Deluxe 1.0 Hack" << std::endl;
	std::cout << "Press Numpad 0 to EXIT" << std::endl;
	std::cout << "Press Numpad 1 to set Points" << std::endl;
	while (true) {
		Sleep(50);
		if (GetAsyncKeyState(VK_NUMPAD0)) { // Exit
			return 0;
		}
		if (GetAsyncKeyState(VK_NUMPAD1)) {//Mouseposition
			std::cout << "How many points you want?" << std::endl;
			int newPoints = 0;
			std::cin >> newPoints;
			WriteProcessMemory(helper.GetprocessHandle(), (LPVOID)(dynamicPointsAddress), &newPoints, 4, 0);
		}
	}




	return 0;
}