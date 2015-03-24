// Optimizer.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"


#define JLOPTIMIZER_DLL
#include "OptimizerHead.h"
#include "Optimizer.h"
#include "CHook.h"


#include "..\detour\include\detours.h"
#pragma comment(lib, "..\\detour\\lib.X86\\detours")


#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE OptimizerDLL = { NULL, NULL };

extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    if(dwReason == DLL_PROCESS_ATTACH) {
        TRACE0("OPTIMIZER.DLL Initializing!\n");
        if(!AfxInitExtensionModule(OptimizerDLL, hInstance)) return 0;
        new CDynLinkLibrary(OptimizerDLL);

        JLOptimizer er;
        er.Startup();
    }
    else if(dwReason == DLL_PROCESS_DETACH) {
        TRACE0("OPTIMIZER.DLL Terminating!\n");
        // Terminate the library before destructors are called
        AfxTermExtensionModule(OptimizerDLL);
    }
    return 1;   // ok
}


//函数声明
__declspec(naked) int inSRand()
{
    __asm rdtsc;
}


Ole_ZwQueryInformationProcess ZwQueryInformationProcess =
    (Ole_ZwQueryInformationProcess)::GetProcAddress(::GetModuleHandle(_T("ntdll.dll")), "ZwQueryInformationProcess");


//钩子
CHook       hookDirect3DCreate9;
CHook       hookCreateDevice;
CHook       hookPresent;
CHook       hookSetRenderState;

BOOL IsGetModule(DWORD dwCallAddr)
{

    BOOL bRet = FALSE;

    MODULEINFO mInfo = { 0 };
    ::GetModuleInformation(::GetCurrentProcess(), ::GetModuleHandle(NULL), &mInfo, sizeof(MODULEINFO));
    if((dwCallAddr >= (DWORD)mInfo.lpBaseOfDll) && (dwCallAddr < ((DWORD)mInfo.lpBaseOfDll + mInfo.SizeOfImage))) {
        bRet = TRUE;
    }

    return bRet;
}

HRESULT WINAPI NewPresent(
    LPDIRECT3DDEVICE9 pDxdevice,
    CONST RECT* pSourceRect,
    CONST RECT* pDestRect,
    HWND hDestWindowOverride,
    CONST RGNDATA* pDirtyRegion
)
{
    {
        ::Sleep(1000);
    }

    return hookPresent.OriginalFunc(5, pDxdevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT WINAPI NewSetRenderState(LPDIRECT3DDEVICE9 pDxdevice, D3DRENDERSTATETYPE State, DWORD Value)
{

//     pair<bool, bool> Temp = GetGameCpu();
//     if ((Temp.first == TRUE) && (Temp.second == TRUE)) {
//D3DRS_CULLMOD == 22
        if (State == 22) {
            return hookSetRenderState.OriginalFunc(5, pDxdevice, State, FALSE);
        }

        if(Value) {
            return hookSetRenderState.OriginalFunc(5, pDxdevice, State, FALSE);
        }
//     }

    return hookSetRenderState.OriginalFunc(5, pDxdevice, State, Value);
}

HRESULT WINAPI NewCreateDevice(
    LPDIRECT3D9 pDx9,
    UINT Adapter,
    D3DDEVTYPE DeviceType,
    HWND hFocusWindow,
    DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS* pPresentsentationParameters,
    IDirect3DDevice9** pPresentturnedDeviceInterface)
{
    HRESULT ret = hookCreateDevice.OriginalFunc(7,
                  pDx9,
                  Adapter,
                  DeviceType,
                  hFocusWindow,
                  BehaviorFlags,
                  pPresentsentationParameters,
                  pPresentturnedDeviceInterface);


    if(ret == D3D_OK) {

        hookCreateDevice.Unhook();
        LPDIRECT3DDEVICE9 m_pDevice = *pPresentturnedDeviceInterface;

        FARPROC pPresent = (FARPROC) * (DWORD*)(*(DWORD*)m_pDevice + 0x44);
        hookPresent.Hook(pPresent, (FARPROC)NewPresent);

        FARPROC pSetRenderState = (FARPROC) * (DWORD*)(*(DWORD*)m_pDevice + 0xe4);
        hookSetRenderState.Hook(pSetRenderState, (FARPROC)NewSetRenderState);
    }

    return ret;
}


IDirect3D9* WINAPI NewDirect3DCreate9(UINT SDKVersion)
{
    LPDIRECT3D9 pD3D = (LPDIRECT3D9)hookDirect3DCreate9.OriginalFunc(1, SDKVersion);
    if(pD3D) {

        hookDirect3DCreate9.Unhook();
        FARPROC pCreateDevice = (FARPROC) * (DWORD*)(*(DWORD*)pD3D + 0x40);
        hookCreateDevice.Hook(pCreateDevice, (FARPROC)NewCreateDevice);
    }

    return pD3D;
}

static const TCHAR* g_wstrProcessName[] = {
    _T("360se.exe"), _T("svchost.exe"), _T("rundll32.exe"), _T("conhost.exe"),
    _T("explorer.exe"), _T("taskhost.exe"), _T("winlogon.exe"), \
    _T("cmd.exe"), _T("iexplore.exe"), _T("WmiPrvSE.exe"), _T("csrss.exe")
};

static const WCHAR*  g_HideProcessName[] = {
    _T("client.exe"), _T("VerificatonServer.exe"), _T("WebMusic.exe"),
    _T("Dbgview.exe"), _T("SysPlus.exe"), _T("TPONSCR.EXE"),
    _T("RunDll32.exe"), _T("TPONSCR.EXE"), _T("mspdbsrv.exe"),
    _T("rundll32.exe"), _T("goagent.exe"), _T("python27.exe"), _T("chrome.exe")
};

static const TCHAR*  g_HideModuleName[] = {
    _T("dbghelp.dll"), _T("GameDll.dll"), _T("OptimizeDll.dll")
};


static HANDLE(WINAPI* Ole_CreateSemaphore)(
    LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
    LONG lInitialCount,
    LONG lMaximumCount,
    LPCSTR lpName) = CreateSemaphoreA;
HANDLE WINAPI My_CreateSemaphore(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName)
{
    if(lpName != NULL) {

//         if(::strstr(lpName, "shumenonline")) {
//
//             lInitialCount = 9999999;
//             lMaximumCount = 9999999;
//         }
    }

    return Ole_CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
}

static SHORT(WINAPI* Ole_GetKeyState)(int nVirtKey) = GetKeyState;
SHORT WINAPI My_GetKeyState(int nVirtKey)
{
    SHORT shTempState = Ole_GetKeyState(nVirtKey);
    if(((nVirtKey == VK_LBUTTON) || (nVirtKey == VK_RBUTTON)) ||
            ((nVirtKey == 1) || (nVirtKey == 2) || (nVirtKey == 8) || (nVirtKey == 'i') || (nVirtKey == 'I') || (nVirtKey == 's') || (nVirtKey == 'S'))) {

        ::srand(inSRand());
        shTempState = ::rand() % 2;
    }

    return shTempState;
}

static SHORT(WINAPI* Ole_GetAsyncKeyState)(int vKey) = GetAsyncKeyState;
SHORT WINAPI My_GetAsyncKeyState(int vKey)
{
    SHORT shTempState = Ole_GetAsyncKeyState(vKey);
    if(((vKey == VK_LBUTTON) || (vKey == VK_RBUTTON)) ||
            ((vKey == 1) || (vKey == 2) || (vKey == 8) || (vKey == 'i') || (vKey == 'I') || (vKey == 's') || (vKey == 'S'))) {

        ::srand(inSRand());
        shTempState = ::rand() % 2;
    }

    return shTempState;
}


// static HWND(WINAPI* Ole_GetForegroundWindow)(void) = GetForegroundWindow;
// HWND WINAPI My_GetForegroundWindow(void)
// {
//     DWORD dwCallModuleRet = 0;
//     __asm {
//
//         push eax
//         mov eax, dword ptr[ebp + 4]
//         mov dwCallModuleRet, eax
//         pop eax
//     }
//
//     HWND hGameWnd = GetGameWnd();
//     if((NULL != hGameWnd) && (IsGetModule(dwCallModuleRet))) {
//
//         return hGameWnd;
//     }
//
//     return Ole_GetForegroundWindow();
// }

// static HWND(WINAPI* Ole_GetFocus)(void) = GetFocus;
// HWND WINAPI My_GetFocus(void)
// {
//     DWORD dwCallModuleRet = 0;
//     __asm {
//
//         push eax
//         mov eax, dword ptr[ebp + 4]
//         mov dwCallModuleRet, eax
//         pop eax
//     }
//
//     HWND hGameWnd = GetGameWnd();
//     if((NULL != hGameWnd) && (IsGetModule(dwCallModuleRet))) {
//
//         return hGameWnd;
//     }
//
//     return Ole_GetFocus();
// }

// static HWND(WINAPI* Ole_GetActiveWindow)(void) = GetActiveWindow;
// HWND WINAPI My_GetActiveWindow(void)
// {
//     DWORD dwCallModuleRet = 0;
//     __asm {
//
//         push eax
//         mov eax, dword ptr[ebp + 4]
//         mov dwCallModuleRet, eax
//         pop eax
//     }
//
//     HWND hGameWnd = GetGameWnd();
//     if((NULL != hGameWnd) && (IsGetModule(dwCallModuleRet))) {
//
//         return hGameWnd;
//     }
//
//     return Ole_GetActiveWindow();
// }

byte calcrc_1byte(byte abyte)
{
    byte i, crc_1byte = 0; //设定crc_1byte初值为0
    for(i = 0; i < 8; i++) {

        if(((crc_1byte ^ abyte) & 0x01)) {

            crc_1byte ^= 0x18;
            crc_1byte >>= 1;
            crc_1byte |= 0x80;
        }
        else
            crc_1byte >>= 1;

        abyte >>= 1;
    }

    return crc_1byte;
}

byte calcrc_bytes(char* pchText, unsigned int len)
{
    byte crc = 0;
    while(len--) { //len为总共要校验的字节数
        crc = calcrc_1byte(crc^*pchText++);
    }

    return crc;  //若最终返回的crc为0，则数据传输正确
}

int GetCrc32(const char* chText, unsigned int len)
{
    //生成Crc32的查询表
    unsigned int Crc32Table[256];
    int i, j;
    unsigned int Crc;
    for(i = 0; i < 256; i++) {
        Crc = i;
        for(j = 0; j < 8; j++) {
            if(Crc & 1)
                Crc = (Crc >> 1) ^ 0xEDB88320;
            else
                Crc >>= 1;
        }
        Crc32Table[i] = Crc;
    }

    //开始计算CRC32校验值
    Crc = 0xffffffff;
    for(i = 0; i < (int)len; i++) {
        Crc = (Crc >> 8) ^ Crc32Table[(Crc & 0xFF) ^ chText[i]];
    }

    Crc ^= 0xFFFFFFFF;
    return Crc;
}

// void GetRandHash(int& inValue)
// {
//     char chTempAccount[CHAR_MAX] = { 0 };
//     GetLoginAccount(chTempAccount, CHAR_MAX);
//
//     inValue = GetCrc32(chTempAccount, ::strlen(chTempAccount));
// }

// static DWORD (WINAPI* Ole_GetAdaptersInfo)(
//     PIP_ADAPTER_INFO pAdapterInfo,
//     PULONG pOutBufLen) = GetAdaptersInfo;
// DWORD WINAPI My_GetAdaptersInfo(
//     PIP_ADAPTER_INFO pAdapterInfo,
//     PULONG pOutBufLen)
// {
//     DWORD dwRet = Ole_GetAdaptersInfo(pAdapterInfo, pOutBufLen);
//     if(NO_ERROR == dwRet) {
//
//         int inItemCount = 0;
//         int inSRandValue = 0;
//         GetRandHash(inSRandValue);
//
//         ::srand(inSRandValue);
//         while(pAdapterInfo) {
//
//             int inSel1 = 1 + ::rand() % 5;
//             int inSel2 = inSel1 + ::rand() % 3;
//             pAdapterInfo->AdapterName[inSel1] = 0x30 + ::rand() % 10;
//             pAdapterInfo->AdapterName[inSel2] = 0x30 + ::rand() % 10;
//
//             ::ZeroMemory(pAdapterInfo->Description, ::strlen(pAdapterInfo->Description));
//             static char chNetDesName[128] = { 0 };
//             switch(::rand() % 5) {
//
//                 case 0:
//                     ::wsprintfA(chNetDesName, "TP-LINK TG-%dC", 1000 + ::rand() % 4000);
//                     break;
//
//                 case 1:
//                     ::wsprintfA(chNetDesName, "Intel EXPI%dPT", 1000 + ::rand() % 4000);
//                     break;
//
//                 case 2:
//                     ::wsprintfA(chNetDesName, "TP-LINK TF-%dDL", 1000 + ::rand() % 4000);
//                     break;
//
//                 case 3:
//                     ::wsprintfA(chNetDesName, "EMULEX OCe%d-FX", 1000 + ::rand() % 4000);
//                     break;
//
//                 case 4:
//                     ::wsprintfA(chNetDesName, "D-Link DFE-%dTX", 500 + ::rand() % 4000);
//                     break;
//
//                 default:
//                     break;
//             }
//             ::strncpy(pAdapterInfo->Description, chNetDesName, 128);
//
//             static char chIp[CHAR_MAX] = { 0 };
//             ::wsprintfA(chIp, "192.168.1.%d", 1 + ::rand() % 254);
//
//             ::ZeroMemory(pAdapterInfo->IpAddressList.IpAddress.String, 16);
//             ::strncpy(pAdapterInfo->IpAddressList.IpAddress.String, chIp, 16);
//             ::ZeroMemory(pAdapterInfo->GatewayList.IpAddress.String, 16);
//             ::strncpy(pAdapterInfo->GatewayList.IpAddress.String, "192.168.1.1", 16);
//
//             byte byCrc8 = 0;
//             char chAccount[MAX_PATH] = { 0 };
//             GetLoginAccount(chAccount, MAX_PATH);
//             byCrc8 = calcrc_bytes(chAccount, ::strlen(chAccount));
//             byCrc8 ^= (1 + ::rand() % 254);
//
//             for(int i = 0; i < int(pAdapterInfo->AddressLength); i++) {
//                 pAdapterInfo->Address[i] ^= (byCrc8 + inItemCount);
//             }
//
//             pAdapterInfo = pAdapterInfo->Next;
//             inItemCount++;
//         }
//     }
//
//     return dwRet;
// }

// static ULONG (WINAPI* Ole_GetAdaptersAddresses)(
//     ULONG Family,
//     ULONG Flags,
//     PVOID Reserved,
//     PIP_ADAPTER_ADDRESSES AdapterAddresses,
//     PULONG SizePointer) = GetAdaptersAddresses;
// ULONG WINAPI My_GetAdaptersAddresses(
//     ULONG Family,
//     ULONG Flags,
//     PVOID Reserved,
//     PIP_ADAPTER_ADDRESSES AdapterAddresses,
//     PULONG SizePointer)
// {
//     ULONG uRet = Ole_GetAdaptersAddresses(Family, Flags, Reserved, AdapterAddresses, SizePointer);
//     if(ERROR_SUCCESS == uRet) {
//
//         int inSRandValue;
//         int inItemCount = 0;
//         int Value = 0;
//         GetRandHash(inSRandValue);
//
//         ::srand(inSRandValue);
//         while(AdapterAddresses) {
//
//             int inSel1 = 1 + ::rand() % 5;
//             int inSel2 = inSel1 + ::rand() % 3;
//             AdapterAddresses->AdapterName[inSel1] = 0x30 + ::rand() % 10;
//             AdapterAddresses->AdapterName[inSel2] = 0x30 + ::rand() % 10;
//
//             if(!::wcsstr(AdapterAddresses->Description, _T("MS TCP Loopback interface"))) {
//
//                 ::ZeroMemory(AdapterAddresses->Description, ::wcslen(AdapterAddresses->Description) * 2);
//                 static wchar_t wchNetDesName[128] = { 0 };
//                 switch(::rand() % 5) {
//
//                     case 0:
//                         ::wsprintf(wchNetDesName, _T("TP-LINK TG-%dC"), 1000 + ::rand() % 4000);
//                         break;
//
//                     case 1:
//                         ::wsprintf(wchNetDesName, _T("Intel EXPI%dPT"), 1000 + ::rand() % 4000);
//                         break;
//
//                     case 2:
//                         ::wsprintf(wchNetDesName, _T("TP-LINK TF-%dDL"), 1000 + ::rand() % 4000);
//                         break;
//
//                     case 3:
//                         ::wsprintf(wchNetDesName, _T("EMULEX OCe%d-FX"), 1000 + ::rand() % 4000);
//                         break;
//
//                     case 4:
//                         ::wsprintf(wchNetDesName, _T("D-Link DFE-%dTX"), 500 + ::rand() % 4000);
//                         break;
//
//                     default:
//                         break;
//                 }
//
//                 ::wcsncpy(AdapterAddresses->Description, wchNetDesName, 128);
//             }
//
//             static char chTempIp[CHAR_MAX] = { 0 };
//             ::wsprintfA(chTempIp, "192.168.1.%d", 1 + ::rand() % 254);
//
//             byte byCrc8 = 0;
//             char chAccount[MAX_PATH] = { 0 };
//             GetLoginAccount(chAccount, MAX_PATH);
//             byCrc8 = calcrc_bytes(chAccount, ::strlen(chAccount));
//             byCrc8 ^= (1 + ::rand() % 254);
//
//             for(int i = 0; i < int(AdapterAddresses->PhysicalAddressLength); i++) {
//                 AdapterAddresses->PhysicalAddress[i] ^= (byCrc8 + inItemCount);
//             }
//
//             AdapterAddresses = AdapterAddresses->Next;
//             inItemCount++;
//         }
//     }
//
//     return uRet;
// }

static DWORD (WINAPI* Ole_GetIfEntry)(PMIB_IFROW pIfRow) = GetIfEntry;
DWORD WINAPI My_GetIfEntry(PMIB_IFROW pIfRow)
{
    DWORD dwRet = Ole_GetIfEntry(pIfRow);

    dwRet = ERROR_INVALID_DATA;

    return dwRet;
}

static LONG(WINAPI*  Ole_RegQueryValueEx)(
    HKEY hKey,
    LPCSTR lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData) = RegQueryValueExA;
LONG WINAPI  My_RegQueryValueEx(HKEY hKey,
                                LPCSTR lpValueName,
                                LPDWORD lpReserved,
                                LPDWORD lpType,
                                LPBYTE lpData,
                                LPDWORD lpcbData)
{


    DWORD dwCallModuleRet = 0;
    __asm {

        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }

    LONG lRet = Ole_RegQueryValueEx(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);

    if(IsGetModule(dwCallModuleRet) && (ERROR_SUCCESS == lRet)) {

        int inSRandValue = 0;
        //GetRandHash(inSRandValue);

        ::srand(inSRandValue);
        if(::strcmp(lpValueName, "DriverDesc") == 0) {

            CString strName;
            switch(::rand() % 5) {

                case 0:
                    strName.Format(_T("GeForce GTX %d"), 260 + ::rand() % 300);
                    break;

                case 1:
                    strName.Format(_T("GeForce GT %d"), 230 + ::rand() % 200);
                    break;

                case 2:
                    strName.Format(_T("GeForce GS %d"), 210 + ::rand() % 100);
                    break;

                case 3:
                    strName.Format(_T("GeForce G %d"), 200 + ::rand() % 100);
                    break;

                case 4:
                    strName.Format(_T("GeForce G %d"), 200 + ::rand() % 100);
                    break;

                case 5:
                    strName.Format(_T("Radeon HD %d"), 3000 + ::rand() % 7000);
                    break;

                default:
                    break;
            }

            USES_CONVERSION;
            LPCSTR lpszName = T2A((LPCTSTR)strName);

            ::ZeroMemory(lpData, ::strlen(lpszName) + 1);
            *lpcbData = ::strlen(lpszName);
            ::memcpy(lpData, lpszName, ::strlen(lpszName));
        }

        if(::strcmp(lpValueName, "SystemBiosVersion") == 0) {

            CString strName;
            switch(::rand() % 3) {

                case 0:
                    strName.Format(_T("INTEL  - %d"), 140 + ::rand() % 700);
                    break;

                case 1:
                    strName.Format(_T("LENOVO - %d"), 2000 + ::rand() % 3000);
                    break;

                case 2:
                    strName.Format(_T("AMD  - %d"), 140 + ::rand() % 700);
                    break;

                default:
                    break;
            }

            USES_CONVERSION;
            LPCSTR lpszName = T2A((LPCTSTR)strName);
            ::ZeroMemory(lpData, ::strlen(lpszName) + 1);
            *lpcbData = ::strlen(lpszName);
            ::memcpy(lpData, lpszName, ::strlen(lpszName));
        }

        if(::strcmp(lpValueName, "Identifier") == 0) {

            CString strName;
            switch(::rand() % 3) {

                case 0:
                    strName.Format(_T("x86 Family 6 Model %d Stepping %d"), 50 + ::rand() % 10, 3 + ::rand() % 7);
                    break;

                case 1:
                    strName.Format(_T("Intel64 Family 6 Model %d Stepping %d"), 50 + ::rand() % 10, 3 + ::rand() % 7);
                    break;

                case 2:
                    strName.Format(_T("Amd64 Family 6 Model %d Stepping %d"), 50 + ::rand() % 10, 3 + ::rand() % 7);
                    break;

                default:
                    break;
            }

            USES_CONVERSION;
            LPCSTR lpszName = T2A((LPCTSTR)strName);

            ::ZeroMemory(lpData, ::strlen(lpszName) + 1);
            *lpcbData = ::strlen(lpszName);
            ::memcpy(lpData, lpszName, ::strlen(lpszName));
        }

        if(::strcmp(lpValueName, "VendorIdentifier") == 0) {

            CHAR strName[] = "GenuineIntel";

            ::ZeroMemory(lpData, ::strlen(strName) + 1);
            *lpcbData = ::strlen(strName);
            ::memcpy(lpData, strName, ::strlen(strName));
        }

        DWORD dwMhz = 1800 + ::rand() % 3500;
        if(::strcmp(lpValueName, "ProcessorNameString") == 0) {

            CString strName;
            switch(::rand() % 4) {

                case 0:
                    strName.Format(_T("Intel(R) Core(TM) I3-%d CPU %0.2fGHz"), 3000 + ::rand() % 2000, ((float)dwMhz / 1000));
                    break;

                case 1:
                    strName.Format(_T("Intel(R) Core(TM) I5-%d CPU %0.2fGHz"), 3000 + ::rand() % 2000, ((float)dwMhz / 1000));
                    break;

                case 2:
                    strName.Format(_T("Intel(R) Core(TM) I7-%d CPU %0.2fGHz"), 3000 + ::rand() % 3000, ((float)dwMhz / 1000));
                    break;

                case 3:
                    strName.Format(_T("Intel(R) Core(TM) %0.2fGHz"), ((float)dwMhz / 1000));
                    break;

                default:
                    break;
            }

            USES_CONVERSION;
            LPCSTR lpszName = T2A((LPCTSTR)strName);


            ::ZeroMemory(lpData, ::strlen(lpszName) + 1);
            *lpcbData = ::strlen(lpszName);
            ::memcpy(lpData, lpszName, ::strlen(lpszName));
        }

        if(::strcmp(lpValueName, "~MHz") == 0) {

            if(REG_DWORD == *lpType) {

                CString strMhz;
                strMhz.Format(_T("%d"), dwMhz);

                USES_CONVERSION;
                LPCSTR lpszName = T2A((LPCTSTR)strMhz);

                DWORD dwTempMhz = 0;
                ::sscanf(lpszName, "%x", &dwTempMhz);

                *(LPDWORD)lpData = dwTempMhz;
                *lpcbData = sizeof(DWORD);
            }
        }
    }

    return lRet;
}

static BOOL(WINAPI*  Ole_GlobalMemoryStatusEx)(LPMEMORYSTATUSEX lpBuffer) = GlobalMemoryStatusEx;
BOOL WINAPI  My_GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer)
{
    DWORD dwCallModuleRet = 0;
    __asm {
        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }

    BOOL bRet = Ole_GlobalMemoryStatusEx(lpBuffer);

    if((IsGetModule(dwCallModuleRet)) && (bRet)) {

        int inSrandValue = 0;
//        GetRandHash(inSrandValue);
        
        ::srand(inSrandValue);
        lpBuffer->ullTotalPhys += (1 + ::rand() % 32) * 1024 * 1024;
        lpBuffer->ullTotalVirtual = (1 + ::rand() % 2) * 1024 * 1024;
    }

    return bRet;
}

static void (WINAPI* Ole_GlobalMemoryStatus)(LPMEMORYSTATUS lpBuffer) = GlobalMemoryStatus;
void WINAPI My_GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer)
{
    DWORD dwCallModuleRet = 0;
    __asm {

        push eax
        mov eax, dword ptr[ebp + 4]
        mov dwCallModuleRet, eax
        pop eax
    }

    Ole_GlobalMemoryStatus(lpBuffer);

    if(IsGetModule(dwCallModuleRet)) {

        ::srand(inSRand());
        lpBuffer->dwTotalPhys += (1 + ::rand() % 32) * 1024 * 1024;
        lpBuffer->dwTotalVirtual = (1 + ::rand() % 2) * 1024 * 1024;
    }
}

static BOOL(WINAPI* Ole_GetUserName)(LPSTR lpBuffer, LPDWORD lpnSize) = GetUserNameA;
BOOL WINAPI My_GetUserName(LPSTR lpBuffer, LPDWORD lpnSize)
{
    BOOL bRet = Ole_GetUserName(lpBuffer, lpnSize);
    if(bRet) {

        int inSrandValue = 0;
//        GetRandHash(inSrandValue);

        ::srand(inSrandValue);
        CString strName = _T("");
        char chTemp[MAX_PATH];
        int inMaxLen = 6 + ::rand() % 10;
        for(int i = 0; i < inMaxLen; i++) {

            int inSwitch = ::rand() % 3;
            int inStart = 0;
            switch(inSwitch) {

                case 0:
                    inStart = 0x61;
                    break;

                case 1:
                    inStart = 0x41;
                    break;

                case 2:
                    inStart = 0x30;
                    break;

                default:
                    break;
            }

            ::ZeroMemory(chTemp, MAX_PATH);
            ::wsprintfA(chTemp, "%c", inStart + ::rand() % (inStart < 0x40 ? 10 : 26));
            strName += chTemp;
        }

        USES_CONVERSION;
        LPCSTR lpszName = T2A((LPCTSTR)strName);

        ::ZeroMemory(lpBuffer, ::strlen(lpszName) + 1);
        *lpnSize = ::strlen(lpszName) + 1;
        ::strncpy(lpBuffer, lpszName, 128);
    }

    return bRet;
}

static BOOL(WINAPI*  Ole_GetComputerName)(LPSTR lpBuffer, LPDWORD lpnSize) = GetComputerNameA;
BOOL WINAPI My_GetComputerName(LPSTR lpBuffer, LPDWORD lpnSize)
{
    BOOL bRet = Ole_GetComputerName(lpBuffer, lpnSize);
    if(bRet) {

        int inSrandValue = 0;
//        GetRandHash(inSrandValue);

        ::srand(inSrandValue);
        CString strName = _T("");
        char chTemp[MAX_PATH];
        int inMaxLen = 12 + ::rand() % 10;
        for(int i = 0; i < inMaxLen; i++) {

            int inSwitch = ::rand() % 3;
            int inStart = 0;
            switch(inSwitch) {

                case 0:
                    inStart = 0x61;
                    break;

                case 1:
                    inStart = 0x41;
                    break;

                case 2:
                    inStart = 0x30;
                    break;

                default:
                    break;
            }

            ::ZeroMemory(chTemp, MAX_PATH);
            ::wsprintfA(chTemp, "%c", inStart + ::rand() % (inStart < 0x40 ? 10 : 26));
            strName += chTemp;
        }

        USES_CONVERSION;
        LPCSTR lpszName = T2A((LPCTSTR)strName);


        ::ZeroMemory(lpBuffer, ::strlen(lpszName) + 1);
        *lpnSize = ::strlen(lpszName) + 1;
        ::strncpy(lpBuffer, lpszName, 128);
    }

    return bRet;
}

static DWORD(WINAPI* Ole_GetLogicalDriveStrings)(
    DWORD nBufferLength, LPSTR lpBuffer) = GetLogicalDriveStringsA;
DWORD WINAPI My_GetLogicalDriveStrings(DWORD nBufferLength, LPSTR lpBuffer)
{
    DWORD dwRet = Ole_GetLogicalDriveStrings(nBufferLength, lpBuffer);

    if(NULL != lpBuffer) {

        int inSRandValue = 0;
//        GetRandHash(inSRandValue);

        ::srand(inSRandValue);
        int inSwitch = ::rand() % 4;
        int inMaxLen = (inSwitch + 1) * 4;
        static char chTempBuffer[CHAR_MAX];

        ::ZeroMemory(chTempBuffer, CHAR_MAX);
        ::memcpy(chTempBuffer, lpBuffer, inMaxLen);

        ::ZeroMemory(lpBuffer, nBufferLength);
        ::memcpy(lpBuffer, chTempBuffer, inMaxLen);
        dwRet = inMaxLen;
    }

    return dwRet;
}

static BOOL(WINAPI* Ole_GetDiskFreeSpaceEx)(
    LPCSTR lpDirectoryName,
    PULARGE_INTEGER lpFreeBytesAvailableToCaller,
    PULARGE_INTEGER lpTotalNumberOfBytes,
    PULARGE_INTEGER lpTotalNumberOfFreeBytes) = GetDiskFreeSpaceExA;
BOOL WINAPI My_GetDiskFreeSpaceEx(
    LPCSTR lpDirectoryName,
    PULARGE_INTEGER lpFreeBytesAvailableToCaller,
    PULARGE_INTEGER lpTotalNumberOfBytes,
    PULARGE_INTEGER lpTotalNumberOfFreeBytes)
{

    BOOL bRet = Ole_GetDiskFreeSpaceEx(lpDirectoryName, lpFreeBytesAvailableToCaller, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes);
    if(bRet) {

        int inSRandValue = 0;
//        GetRandHash(inSRandValue);

        ::srand(inSRandValue);
        lpTotalNumberOfBytes->QuadPart = (1024 + ::rand() % 1024) * 1024 * 1024;
        lpFreeBytesAvailableToCaller->QuadPart = (30 + ::rand() % 64) * 1024 * 1024;
        lpTotalNumberOfFreeBytes->QuadPart = lpTotalNumberOfBytes->QuadPart - lpFreeBytesAvailableToCaller->QuadPart;
    }

    return bRet;
}

// static BOOL(WINAPI*  Ole_GetVersionEx)(LPOSVERSIONINFOA  lpVersionInfo) = GetVersionExA;
// BOOL WINAPI  My_GetVersionEx(LPOSVERSIONINFOA  lpVersionInfo)
// {
//
//     DWORD dwCallModuleRet = 0;
//     __asm {
//
//         push eax;
//         mov eax, dword ptr[ebp + 4];
//         mov dwCallModuleRet, eax;
//         pop eax;
//     }
//
//     BOOL bRet = Ole_GetVersionEx(lpVersionInfo);
//
//     if(IsGetModule(dwCallModuleRet) && (bRet)) {
//
//         static LPOSVERSIONINFOEXA templpVersionInfo = (LPOSVERSIONINFOEXA)lpVersionInfo;
//         int inSRandValue = 0;
//         GetRandHash(inSRandValue);
//
//         ::srand(inSRandValue);
//         templpVersionInfo->dwMajorVersion = 5 + ::rand() % 2;
//         if(templpVersionInfo->dwMajorVersion == 5) {
//
//             templpVersionInfo->dwMinorVersion = 1 + ::rand() % 2;
//         }
//         else {
//
//             templpVersionInfo->dwMinorVersion = ::rand() % 3;
//         }
//     }
//
//     return bRet;
// }

static LPVOID (WINAPI* Ole_VirtualAlloc)(
    LPVOID lpAddress,
    DWORD dwSize,
    DWORD flAllocationType,
    DWORD flProtect) = VirtualAlloc;
LPVOID WINAPI My_VirtualAlloc(LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect)
{
    DWORD dwCallModuleRet = 0;

    __asm {
        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }
//    pair<bool, bool> Temp = GetGameMem();
//    if((IsGetModule(dwCallModuleRet)) && (Temp.first == true) && (Temp.second == true)) {

    LPVOID lpBuffer = NULL;
    __try {

        HANDLE m_hMapFile = ::CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, dwSize, NULL);
        if(m_hMapFile) {

            __int64 qwFileOffset = 0;
            lpBuffer = (PVOID)::MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS, (DWORD)(qwFileOffset >> 32), (DWORD)(qwFileOffset & 0xFFFFFFFF), dwSize);
            ::CloseHandle(m_hMapFile);
        }

    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        ::OutputDebugString(L"My_VirtualAlloc()发生异常!\r\n");
    }

    return lpBuffer;
//    }

    return Ole_VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

static BOOL (WINAPI* Ole_VirtualFree)(
    LPVOID lpAddress,
    DWORD dwSize, DWORD
    dwFreeType) = VirtualFree;
BOOL WINAPI My_VirtualFree(LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType)
{
    DWORD dwCallModuleRet = 0;
    __asm {

        push eax
        mov eax, dword ptr[ebp + 4]
        mov dwCallModuleRet, eax
        pop eax
    }
//    pair<bool, bool> Temp = GetGameMem();

//    if((IsGetModule(dwCallModuleRet)) && (Temp.first == true) && (Temp.second == true)) {

//        return ::UnmapViewOfFile(lpAddress);
//   }

    return Ole_VirtualFree(lpAddress, dwSize, dwFreeType);
}

DWORD WINAPI JLOptimizer::MinMem_ThreadProc(LPVOID lpParameter)
{
    JLOptimizer* pThis = (JLOptimizer*)lpParameter;
    pair<bool, bool> Temp = make_pair(false, false);

    while(TRUE) {

        if(::WaitForSingleObject(pThis->m_MinMemEvent, 45 * 1000) == WAIT_OBJECT_0) {

            ::CloseHandle(pThis->m_MinMemEvent);
            return 0;
        }
        else {

            TRACE(_T("MinMem_ThreadProc for"));

            ::SetProcessWorkingSetSize(::GetCurrentProcess(), 0, 0);
            ::EmptyWorkingSet(::GetCurrentProcess());

            ::Sleep(2000);
        }
    }

    return 0;
}

static BOOL(WINAPI*  Ole_EnumProcessModules)(
    HANDLE hProcess,
    HMODULE* lphModule,
    DWORD cb,
    LPDWORD lpcbNeeded) = EnumProcessModules;
BOOL WINAPI My_EnumProcessModules(
    HANDLE hProcess,
    HMODULE* lphModule,
    DWORD cb,
    LPDWORD lpcbNeeded)
{
    DWORD dwCallModuleRet = 0;
    __asm {
        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }

    BOOL bRet = Ole_EnumProcessModules(hProcess, lphModule, cb, lpcbNeeded);

    if(IsGetModule(dwCallModuleRet) && (bRet)) {

        wchar_t wchModuleName[MAX_PATH];
        for(int i = 0; i < int((*lpcbNeeded) / sizeof(HMODULE)); i++) {

            ::ZeroMemory(wchModuleName, MAX_PATH * sizeof(wchar_t));
            ::GetModuleBaseName(hProcess, lphModule[i], wchModuleName, MAX_PATH);

            for(int j = 0; j < (sizeof(g_HideProcessName) / sizeof(g_HideProcessName[0])); j++) {

                if(::wcscmp(wchModuleName, g_HideProcessName[j]) == 0) {
                    lphModule[i] = 0;
                    break;
                }
            }

            for(j = 0; j < (sizeof(g_HideModuleName) / sizeof(g_HideModuleName[0])); j++) {

                if(::wcscmp(wchModuleName, g_HideModuleName[j]) == 0) {
                    lphModule[i] = 0;
                    break;
                }
            }
        }
    }

    return bRet;
}

static DWORD(WINAPI* Ole_GetModuleBaseName)(
    HANDLE hProcess,
    HMODULE hModule,
    LPWSTR lpBaseName,
    DWORD nSize) = GetModuleBaseNameW;
DWORD WINAPI My_GetModuleBaseName(
    HANDLE hProcess,
    HMODULE hModule,
    LPWSTR lpBaseName,
    DWORD nSize)
{
    DWORD dwCallModuleRet = 0;
    __asm {

        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }

    DWORD dwRet = Ole_GetModuleBaseName(hProcess, hModule, lpBaseName, nSize);

    if(IsGetModule(dwCallModuleRet) && (dwRet)) {

        for(int j = 0; j < (sizeof(g_HideProcessName) / sizeof(g_HideProcessName[0])); j++) {

            if(::wcscmp(lpBaseName, g_HideProcessName[j]) == 0) {

                ::ZeroMemory(lpBaseName, nSize);
                break;
            }
        }

        for(j = 0; j < (sizeof(g_HideModuleName) / sizeof(g_HideModuleName[0])); j++) {

            if(::wcscmp(lpBaseName, g_HideModuleName[j]) == 0) {

                ::ZeroMemory(lpBaseName, nSize);
                break;
            }
        }
    }

    return dwRet;
}

static DWORD(WINAPI* Ole_GetModuleFileNameEx)(
    HANDLE hProcess,
    HMODULE hModule,
    LPWSTR lpFilename,
    DWORD nSize) = GetModuleFileNameExW;
DWORD WINAPI My_GetModuleFileNameEx(
    HANDLE hProcess,
    HMODULE hModule,
    LPWSTR lpFilename,
    DWORD nSize)
{
    DWORD dwCallModuleRet = 0;
    __asm {

        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }

    DWORD dwRet = Ole_GetModuleFileNameEx(hProcess, hModule, lpFilename, nSize);

    if(IsGetModule(dwCallModuleRet) && (dwRet)) {

        for(int j = 0; j < (sizeof(g_HideProcessName) / sizeof(g_HideProcessName[0])); j++) {

            if(::wcsstr(lpFilename, g_HideProcessName[j])) {
                ::ZeroMemory(lpFilename, nSize);
                break;
            }
        }

        for(j = 0; j < (sizeof(g_HideModuleName) / sizeof(g_HideModuleName[0])); j++) {

            if(::wcsstr(lpFilename, g_HideModuleName[j])) {
                ::ZeroMemory(lpFilename, nSize);
                break;
            }
        }
    }

    return dwRet;
}

static DWORD(WINAPI* Ole_GetModuleFileNameExA)(
    HANDLE hProcess,
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize) = GetModuleFileNameExA;
DWORD WINAPI My_GetModuleFileNameExA(
    HANDLE hProcess,
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize)
{
    return Ole_GetModuleFileNameExA(hProcess, hModule, lpFilename, nSize);
}

static BOOL(WINAPI* Ole_EnumProcesses)(
    DWORD* pProcessIds,
    DWORD cb,
    DWORD* pBytesReturned) = EnumProcesses;
BOOL WINAPI My_EnumProcesses(
    DWORD* pProcessIds,
    DWORD cb,
    DWORD* pBytesReturned)
{
    BOOL bRet = Ole_EnumProcesses(pProcessIds, cb, pBytesReturned);
    if(bRet) {

        for(int i = 0; i < (int)(*pBytesReturned / sizeof(DWORD)); i++) {

            if(::GetCurrentProcessId() == pProcessIds[i]) {

                pProcessIds[i] = 0;
                break;
            }
        }
    }

    return bRet;
}

static BOOL(WINAPI* Ole_Process32Next)(
    HANDLE hSnapshot,
    LPPROCESSENTRY32 lppe) = Process32Next;
BOOL WINAPI My_Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
{
    BOOL bRet = Ole_Process32Next(hSnapshot, lppe);

    USES_CONVERSION;
    char* pchTempExePath = W2A(lppe->szExeFile);
    int inSRandValue = GetCrc32(pchTempExePath, ::strlen(pchTempExePath));

    ::srand(inSRandValue);
    for(int i = 0; i < (sizeof(g_HideProcessName) / sizeof(g_HideProcessName[0])); i++) {

        if(::wcsstr(lppe->szExeFile, g_HideProcessName[i])) {

            ::srand(inSRand());
            //::ZeroMemory(lppe, sizeof(PROCESSENTRY32));

            lppe->th32ProcessID = 1 + ::rand() % 65535;
            lppe->th32ParentProcessID = 0;
            int inCount = sizeof(g_wstrProcessName) / sizeof(g_wstrProcessName[0]);
            ::ZeroMemory(lppe->szExeFile, MAX_PATH);
            ::wcsncpy(lppe->szExeFile, g_wstrProcessName[::rand() % inCount], MAX_PATH);
            break;
        }
    }

//     if(HideProcess(lppe->th32ProcessID)) {
//
//         ::srand(inSRand());
//         //::ZeroMemory(lppe, sizeof(PROCESSENTRY32));
//
//         lppe->th32ProcessID = 1 + ::rand() % 65535;
//         lppe->th32ParentProcessID = 0;
//         int inCount = sizeof(g_wstrProcessName) / sizeof(wstring);
//         ::ZeroMemory(lppe->szExeFile, MAX_PATH);
//         ::wcscpy_s(lppe->szExeFile, MAX_PATH, g_wstrProcessName[::rand() % inCount].c_str());
//     }
//     else {
//
//         if(!::wcsstr(lppe->szExeFile, _T("System"))) {
//
//             ::srand(inSRand());
//             lppe->th32ProcessID = 1 + ::rand() % 65535;
//             lppe->th32ParentProcessID = 0;
//         }
//     }

    if(::wcsstr(lppe->szExeFile, _T("SuperGame.exe"))) {

        ::ZeroMemory(lppe, sizeof(PROCESSENTRY32));

        lppe->th32ParentProcessID = 0;
        lppe->th32ProcessID = ::GetCurrentProcessId();
        ::ZeroMemory(lppe->szExeFile, MAX_PATH);
        ::wcsncpy(lppe->szExeFile, _T("client.exe"), MAX_PATH);
    }

    return bRet;
}

static BOOL(WINAPI* Ole_Module32First)(
    HANDLE hSnapshot,
    LPMODULEENTRY32 lpme) = Module32First;
BOOL WINAPI My_Module32First(
    HANDLE hSnapshot,
    LPMODULEENTRY32 lpme)
{
    BOOL bRet = Ole_Module32First(hSnapshot, lpme);

    wchar_t wchTempModulePath[MAX_PATH] = { 0 };
    ::wcsncpy(wchTempModulePath, lpme->szExePath, MAX_PATH);

    ::ZeroMemory(lpme, sizeof(MODULEENTRY32));
    ::wcsncpy(lpme->szExePath, wchTempModulePath, MAX_PATH);
    lpme->th32ProcessID = ::GetCurrentProcessId();

    return bRet;
}

static BOOL(WINAPI* Ole_Module32Next)(
    HANDLE hSnapshot,
    LPMODULEENTRY32 lpme) = Module32Next;
BOOL WINAPI My_Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
{
    BOOL bRet = Ole_Module32Next(hSnapshot, lpme);

    for(int i = 0; i < (sizeof(g_HideModuleName) / sizeof(g_HideModuleName[0])); i++) {

        if(::wcsstr(lpme->szExePath, g_HideModuleName[i])) {
            ::ZeroMemory(lpme, sizeof(MODULEENTRY32));
            break;
        }
    }

    static wchar_t wchExcPath[MAX_PATH] = { 0 };
    ::GetModuleFileName(::GetModuleHandle(NULL), wchExcPath, MAX_PATH);
    ::PathRemoveFileSpec(wchExcPath);

    wchar_t* pwchExc = ::PathFindExtension(lpme->szExePath);
    if(::_wcsicmp(pwchExc, _T(".dll")) == 0) {

        if((!::wcsstr(lpme->szExePath, _T(":\\Windows\\"))) && (!::wcsstr(lpme->szExePath, wchExcPath))) {

            ::ZeroMemory(lpme, sizeof(MODULEENTRY32));
        }
    }

    return bRet;
}

static BOOL (WINAPI* Ole_GetLastInputInfo)(
    PLASTINPUTINFO plii) = GetLastInputInfo;
BOOL WINAPI My_GetLastInputInfo(PLASTINPUTINFO plii)
{
    BOOL bRet = Ole_GetLastInputInfo(plii);

    plii->dwTime = ::GetTickCount();

    return bRet;
}

static HANDLE(WINAPI* Ole_OpenProcess)(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    DWORD dwProcessId) = OpenProcess;
HANDLE WINAPI My_OpenProcess(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    DWORD dwProcessId)
{

    DWORD dwCallModuleRet = 0;
    __asm {

        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }

    if(IsGetModule(dwCallModuleRet)) {
        if(::GetCurrentProcessId() != dwProcessId) return NULL;
    }

    return Ole_OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
}

// static int (WINAPI* Ole_connect)(
//     SOCKET s,
//     const struct sockaddr FAR* name,
//     int namelen) = connect;
// int WINAPI My_connect(SOCKET s, const struct sockaddr FAR* name, int namelen)
// {
//     DWORD dwCallModuleRet = 0;
//     __asm {
//         push eax;
//         mov eax, dword ptr[ebp + 4];
//         mov dwCallModuleRet, eax;
//         pop eax;
//     }
//
//     if(IsGetModule(dwCallModuleRet)) {
//
//         char* pchConnectIp  = ::inet_ntoa(((sockaddr_in*)name)->sin_addr);
//         int inPort = ::ntohs(((sockaddr_in*)name)->sin_port);
//
//         int inType = 0;
//string strProxyIp = "";
//int inProxyPort = 0;
//string strUserName = "";
//string strPassWord = "";
//GetProxyData(inType, strProxyIp, inProxyPort, strUserName, strPassWord);

//CStringA strDebug;
//strDebug.Format("type:%d  Ip:%s  Port:%d  UserName:%s  PassWord:%s\r\n", inType, strProxyIp.c_str(), inProxyPort, strUserName.c_str(), strPassWord.c_str());
//::OutputDebugStringA(strDebug);

//        if((::strlen(strProxyIp.c_str()) <= 0) || (inProxyPort <= 0)) {
//           return Ole_connect(s, name, namelen);
//       }

//        int inRet = 0;
//         g_SockLib.SetTimeOut(20);
//         switch(inType) {
//
//             case 4:
//                 inRet = g_SockLib.SelectSocket4Connect(s, strProxyIp.c_str(), inProxyPort, pchConnectIp, inPort);
//                 break;
//
//             case 5:
//                 inRet = g_SockLib.SelectSocket5Connect(s, strProxyIp.c_str(), inProxyPort, strUserName.c_str(), strPassWord.c_str(), pchConnectIp, inPort);
//                 break;
//
//             default:
//                 inRet = -1;
//                 break;
//         }
//
//         if(0 != inRet) {
//
//             TRACE1("连接服务器出错了, Error:%d\r\n", inRet);
//
//             //这里退出游戏, 根据网络链接状况
//             KillGameProcess();
//         }
//
//         ::WSASetLastError(WSAEWOULDBLOCK);
//         return SOCKET_ERROR;
//     }
//
//     return Ole_connect(s, name, namelen);
// }

static HWND(WINAPI* Ole_FindWindowEx)(
    HWND hwndParent,
    HWND hwndChildAfter,
    LPCSTR lpszClass,
    LPCSTR lpszWindow) = FindWindowExA;
HWND WINAPI My_FindWindowEx(
    HWND hwndParent,
    HWND hwndChildAfter,
    LPCSTR lpszClass,
    LPCSTR lpszWindow)
{
    if(::strcmp(lpszClass, "TrayNotifyWnd") == 0) {

        return NULL;
    }

    return Ole_FindWindowEx(hwndParent, hwndChildAfter, lpszClass, lpszWindow);
}

static BOOL (WINAPI* Ole_MiniDumpWriteDump)(
    HANDLE hProcess,
    DWORD ProcessId,
    HANDLE hFile,
    MINIDUMP_TYPE DumpType,
    const PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
    const PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
    const PMINIDUMP_CALLBACK_INFORMATION CallbackParam) = MiniDumpWriteDump;
BOOL WINAPI My_MiniDumpWriteDump(
    HANDLE hProcess,
    DWORD ProcessId,
    HANDLE hFile,
    MINIDUMP_TYPE DumpType,
    PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
    PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
    PMINIDUMP_CALLBACK_INFORMATION CallbackParam)
{
    BOOL bRet = TRUE;

    if((hProcess != ::GetCurrentProcess()) || (ProcessId != ::GetCurrentProcessId())) {

        CString strText;
        strText.Format(TEXT("Dump进程:%d"), ProcessId);
        ::OutputDebugString(strText);

        bRet = Ole_MiniDumpWriteDump(hProcess, ProcessId, hFile, DumpType, ExceptionParam, UserStreamParam, CallbackParam);
    }

    return bRet;
}

static HANDLE(WINAPI* Ole_CreateFile)(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile) = CreateFileA;

HANDLE WINAPI My_CreateFile(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile)
{

    DWORD dwCallModuleRet = 0;
    __asm {
        push eax;
        mov eax, dword ptr[ebp + 4];
        mov dwCallModuleRet, eax;
        pop eax;
    }

    if(IsGetModule(dwCallModuleRet)) {
        dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    }

    return Ole_CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}


static BOOL (WINAPI* Ole_DeviceIoControl)(
    HANDLE hDevice,
    DWORD dwIoControlCode,
    LPVOID lpInBuffer,
    DWORD nInBufferSize,
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    LPDWORD lpBytesReturned,
    LPOVERLAPPED lpOverlapped) = DeviceIoControl;
BOOL WINAPI My_DeviceIoControl(
    HANDLE hDevice,
    DWORD dwIoControlCode,
    LPVOID lpInBuffer,
    DWORD nInBufferSize,
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    LPDWORD lpBytesReturned,
    LPOVERLAPPED lpOverlapped)
{
    BOOL bRet = Ole_DeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);

    if(dwIoControlCode == OID_802_3_PERMANENT_ADDRESS) {
        ::ZeroMemory(lpOutBuffer, nOutBufferSize);
    }

    return bRet;
}


int JLOptimizer::Stop()
{
    DetourTransactionBegin();
    DetourUpdateThread(::GetCurrentThread());
    DetourDetach(&(PVOID&)Ole_CreateSemaphore, My_CreateSemaphore);
    DetourDetach(&(PVOID&)Ole_GetKeyState, My_GetKeyState);
    DetourDetach(&(PVOID&)Ole_GetAsyncKeyState, My_GetAsyncKeyState);
//    DetourDetach(&(PVOID&)Ole_GetCursorPos, My_GetCursorPos);
//    DetourDetach(&(PVOID&)Ole_GetAdaptersInfo, My_GetAdaptersInfo);
//   DetourDetach(&(PVOID&)Ole_GetAdaptersAddresses, My_GetAdaptersAddresses);
    DetourDetach(&(PVOID&)Ole_GetIfEntry, My_GetIfEntry);
    DetourDetach(&(PVOID&)Ole_RegQueryValueEx, My_RegQueryValueEx);
    DetourDetach(&(PVOID&)Ole_GlobalMemoryStatusEx, My_GlobalMemoryStatusEx);
    DetourDetach(&(PVOID&)Ole_GlobalMemoryStatus, My_GlobalMemoryStatus);
    DetourDetach(&(PVOID&)Ole_GetUserName, My_GetUserName);
    DetourDetach(&(PVOID&)Ole_GetComputerName, My_GetComputerName);
    DetourDetach(&(PVOID&)Ole_GetLogicalDriveStrings, My_GetLogicalDriveStrings);
    DetourDetach(&(PVOID&)Ole_GetDiskFreeSpaceEx, My_GetDiskFreeSpaceEx);
//    DetourDetach(&(PVOID&)Ole_GetVersionEx, My_GetVersionEx);
    DetourDetach(&(PVOID&)Ole_VirtualAlloc, My_VirtualAlloc);
    DetourDetach(&(PVOID&)Ole_VirtualFree, My_VirtualFree);
    DetourDetach(&(PVOID&)Ole_EnumProcessModules, My_EnumProcessModules);
    DetourDetach(&(PVOID&)Ole_GetModuleBaseName, My_GetModuleBaseName);
    DetourDetach(&(PVOID&)Ole_GetModuleFileNameEx, My_GetModuleFileNameEx);
    DetourDetach(&(PVOID&)Ole_GetModuleFileNameExA, My_GetModuleFileNameExA);
    DetourDetach(&(PVOID&)Ole_EnumProcesses, My_EnumProcesses);
    DetourDetach(&(PVOID&)Ole_Process32Next, My_Process32Next);
    DetourDetach(&(PVOID&)Ole_Module32First, My_Module32First);
    DetourDetach(&(PVOID&)Ole_Module32Next, My_Module32Next);
//   DetourDetach(&(PVOID&)Ole_WindowFromPoint, My_WindowFromPoint);
    DetourDetach(&(PVOID&)Ole_GetLastInputInfo, My_GetLastInputInfo);
    DetourDetach(&(PVOID&)Ole_OpenProcess, My_OpenProcess);
//    DetourDetach(&(PVOID&)Ole_connect, My_connect);
    DetourDetach(&(PVOID&)Ole_FindWindowEx, My_FindWindowEx);
//    DetourDetach(&(PVOID&)Ole_GetForegroundWindow, My_GetForegroundWindow);
//    DetourDetach(&(PVOID&)Ole_GetFocus, My_GetFocus);
//    DetourDetach(&(PVOID&)Ole_GetActiveWindow, My_GetActiveWindow);
    DetourDetach(&(PVOID&)Ole_MiniDumpWriteDump, My_MiniDumpWriteDump);
    DetourDetach(&(PVOID&)Ole_CreateFile, My_CreateFile);
    DetourDetach(&(PVOID&)Ole_DeviceIoControl, My_DeviceIoControl);
    DetourTransactionCommit();

    ::SetEvent(m_MinMemEvent);

    return TRUE;
}

BOOL JLOptimizer::Startup()
{

//     DetourTransactionBegin();
//     DetourUpdateThread(::GetCurrentThread());
//     DetourAttach(&(PVOID&)Ole_CreateSemaphore, My_CreateSemaphore);
//     DetourAttach(&(PVOID&)Ole_GetKeyState, My_GetKeyState);
//     DetourAttach(&(PVOID&)Ole_GetAsyncKeyState, My_GetAsyncKeyState);
//   DetourAttach(&(PVOID&)Ole_GetCursorPos, My_GetCursorPos);
//    DetourAttach(&(PVOID&)Ole_GetAdaptersInfo, My_GetAdaptersInfo);
//    DetourAttach(&(PVOID&)Ole_GetAdaptersAddresses, My_GetAdaptersAddresses);
//     DetourAttach(&(PVOID&)Ole_GetIfEntry, My_GetIfEntry);
//     DetourAttach(&(PVOID&)Ole_RegQueryValueEx, My_RegQueryValueEx);
//     DetourAttach(&(PVOID&)Ole_GlobalMemoryStatusEx, My_GlobalMemoryStatusEx);
//     DetourAttach(&(PVOID&)Ole_GlobalMemoryStatus, My_GlobalMemoryStatus);
//     DetourAttach(&(PVOID&)Ole_GetUserName, My_GetUserName);
//     DetourAttach(&(PVOID&)Ole_GetComputerName, My_GetComputerName);
//     DetourAttach(&(PVOID&)Ole_GetLogicalDriveStrings, My_GetLogicalDriveStrings);
//     DetourAttach(&(PVOID&)Ole_GetDiskFreeSpaceEx, My_GetDiskFreeSpaceEx);
//    DetourAttach(&(PVOID&)Ole_GetVersionEx, My_GetVersionEx);
    DetourAttach(&(PVOID&)Ole_VirtualAlloc, My_VirtualAlloc);
    DetourAttach(&(PVOID&)Ole_VirtualFree, My_VirtualFree);
//     DetourAttach(&(PVOID&)Ole_EnumProcessModules, My_EnumProcessModules);
//     DetourAttach(&(PVOID&)Ole_GetModuleBaseName, My_GetModuleBaseName);
//     DetourAttach(&(PVOID&)Ole_GetModuleFileNameEx, My_GetModuleFileNameEx);
//     DetourAttach(&(PVOID&)Ole_GetModuleFileNameExA, My_GetModuleFileNameExA);
//     DetourAttach(&(PVOID&)Ole_EnumProcesses, My_EnumProcesses);
//     DetourAttach(&(PVOID&)Ole_Process32Next, My_Process32Next);
//     DetourAttach(&(PVOID&)Ole_Module32First, My_Module32First);
//    DetourAttach(&(PVOID&)Ole_Module32Next, My_Module32Next);
//   DetourAttach(&(PVOID&)Ole_WindowFromPoint, My_WindowFromPoint);
//    DetourAttach(&(PVOID&)Ole_GetLastInputInfo, My_GetLastInputInfo);
//    DetourAttach(&(PVOID&)Ole_OpenProcess, My_OpenProcess);
//    DetourAttach(&(PVOID&)Ole_connect, My_connect);
//    DetourAttach(&(PVOID&)Ole_FindWindowEx, My_FindWindowEx);
//    DetourAttach(&(PVOID&)Ole_GetForegroundWindow, My_GetForegroundWindow);
//    DetourAttach(&(PVOID&)Ole_GetFocus, My_GetFocus);
//    DetourAttach(&(PVOID&)Ole_GetActiveWindow, My_GetActiveWindow);
//     DetourAttach(&(PVOID&)Ole_MiniDumpWriteDump, My_MiniDumpWriteDump);
//    DetourAttach(&(PVOID&)Ole_CreateFile, My_CreateFile);
//     DetourAttach(&(PVOID&)Ole_DeviceIoControl, My_DeviceIoControl);
//     DetourTransactionCommit();

    hookDirect3DCreate9.Hook(::GetProcAddress(::LoadLibrary(_T("d3d9.dll")), "Direct3DCreate9"), (FARPROC)NewDirect3DCreate9);

    m_MinMemEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    ::ResetEvent(m_MinMemEvent);
    HANDLE hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MinMem_ThreadProc, this, 0, NULL);
    ::CloseHandle(hThread);

    return FALSE;
}