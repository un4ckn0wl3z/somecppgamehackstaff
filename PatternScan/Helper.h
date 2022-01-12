#pragma once
#include <Windows.h>  //DWORD, HANDLE
#include <TlHelp32.h> //CreateToolhelp32Snapshot
#include <tchar.h>    //_tcscmp
#include <Psapi.h>    //GetModuleInformation
#include <vector>
#include <iostream>



class Helper
{
public:
    Helper();
    Helper(DWORD pID);
    ~Helper();
    uintptr_t GetModuleBaseAddress(TCHAR* lpszModuleName);
    uintptr_t GetDynamicAddress(uintptr_t baseAddress, std::vector<DWORD> offsets);
    uintptr_t GetAddressFromSignature(std::vector<int> signature);
    void SetpID(DWORD pID);
    void SetpBaseAddress(char moduleName[]);
    DWORD GetpID();
    HANDLE GetprocessHandle();

private:
    DWORD pID;
    DWORD pBaseAddress; //Base Address of exe
    DWORD pSize;        //Size of exe module
    HANDLE processHandle;
};