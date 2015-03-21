// SrvCore.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "SrvCore.h"



//��̬����
static AFX_EXTENSION_MODULE ServiceCoreDLL = {NULL, NULL};

//////////////////////////////////////////////////////////////////////////////////

//��������
extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if(dwReason == DLL_PROCESS_ATTACH) {
        if(!AfxInitExtensionModule(ServiceCoreDLL, hInstance)) return 0;
        new CDynLinkLibrary(ServiceCoreDLL);
    }
    else if(dwReason == DLL_PROCESS_DETACH) {
        AfxTermExtensionModule(ServiceCoreDLL);
    }

    return 1;
}
