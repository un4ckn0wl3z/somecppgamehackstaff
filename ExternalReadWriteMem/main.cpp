#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h> // _tcscmp
#include <vector>


DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID) {
	DWORD dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID); // make snapshot of all modules within process
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32)) //store first Module in ModuleEntry32
	{
		do {
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) // if Found Module matches Module we look for -> done!
			{
				dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32)); // go through Module entries in Snapshot and store in ModuleEntry32


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

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
	HANDLE processHandle = NULL;
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL) { // error handling
		std::cout << "Failed to open process" << std::endl;
		return 0;
	}

	char gameName[] = "Zuma.exe";
	DWORD gameBaseAddress = GetModuleBaseAddress(_T(gameName), pid);
	DWORD  offsetGameToBaseeAddress = 0x147EF8;
	DWORD baseAddress = NULL;

	//Get value at gamebase+offset -> store it in baseAddress
	ReadProcessMemory(processHandle, (LPVOID)(gameBaseAddress + offsetGameToBaseeAddress), &baseAddress, sizeof(baseAddress), NULL);
	std::cout << "debugginfo: baseaddress = " << std::hex << baseAddress << std::endl;

	std::vector<DWORD> pointsOffsets{ 0x14 ,0x174 ,0x55C ,0xD0 ,0xB8 };
	DWORD pointsAddress = baseAddress; //the Adress we need -> change now while going through offsets
	std::cout << "debugginfo: pointaddress now (before adding with offset) = " << std::hex << pointsAddress << std::endl;

	for (int i = 0; i < pointsOffsets.size() - 1; i++) // -1 because we dont want the value at the last offset
	{
		ReadProcessMemory(processHandle, (LPVOID)(pointsAddress + pointsOffsets.at(i)), &pointsAddress, sizeof(pointsAddress), NULL);
		std::cout << "debugginfo: Value at offset" << "[" << i << "]" << " = " << std::hex << pointsAddress << std::endl;
	}

	std::cout << "debugginfo: pointaddress now (after adding with offset) = " << std::hex << pointsAddress << std::endl;
	pointsAddress += pointsOffsets.at(pointsOffsets.size() - 1); //Add Last offset -> done!!
	std::cout << "debugginfo: pointaddress now (after adding last offset) = " << std::hex << pointsAddress << std::endl;


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
			WriteProcessMemory(processHandle, (LPVOID)(pointsAddress), &newPoints, 4, 0);
		}
	}

	return 0;
}