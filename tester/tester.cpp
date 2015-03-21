// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <unknwn.h>

#define interface struct

interface IX: IUnknown {
    virtual void fx1() = 0;
};

interface IY: public IUnknown {
    virtual void fy1() = 0;
};


class COM: public IY, public IX
{
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) {
        return S_OK;
    }


    virtual ULONG __stdcall AddRef() {
        return 0;
    }

    virtual ULONG __stdcall Release() {
        return 0;
    }

    virtual void fy1() {
        printf("fy1 call\r\n");
    }

    virtual void fx1() {
        printf("fx1 call\r\n");
    }
};

void entry()
{

    if(1) {
        return;
    }


    COM c1;
    IX* pIx = &c1;
    IY* pIy = &c1;

    pIx->fx1();
    pIy->fy1();


    printf("Hello World");
}