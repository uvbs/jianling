//==========================================
// Matt Pietrek
// Microsoft Systems Journal, April 1997
// FILE: MSJEXHND.CPP
//==========================================
#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include "msjexhnd.h"
//============================== Global Variables =============================
//
// Declare the static variables of the MSJExceptionHandler class
//
TCHAR MSJExceptionHandler::m_szLogFileName[MAX_PATH];
LPTOP_LEVEL_EXCEPTION_FILTER MSJExceptionHandler::m_previousFilter;
HANDLE MSJExceptionHandler::m_hReportFile;

MSJExceptionHandler g_MSJExceptionHandler;  // Declare global instance of class
//============================== Class Methods =============================
//=============
// Constructor
//=============
MSJExceptionHandler::MSJExceptionHandler()
{

    BOOL bRet = TRUE;
    DWORD dwOptions = SymGetOptions();

    SymSetOptions(dwOptions | SYMOPT_LOAD_LINES
                  | SYMOPT_DEFERRED_LOADS
                  | SYMOPT_OMAP_FIND_NEAREST);

    bRet = SymInitialize(GetCurrentProcess(),
                         NULL,
                         TRUE);

    // Install the unhandled exception filter function
    m_previousFilter = SetUnhandledExceptionFilter(MSJUnhandledExceptionFilter);

    // Figure out what the report file will be named, and store it away
    GetModuleFileName(0, m_szLogFileName, MAX_PATH);

    // Look for the '.' before the "EXE" extension.  Replace the extension
    // with "RPT"
    PTSTR pszDot = _tcsrchr(m_szLogFileName, _T('.'));
    if(pszDot)
    {
        pszDot++;   // Advance past the '.'
        if(_tcslen(pszDot) >= 3)
            _tcscpy(pszDot, _T("RPT"));     // "RPT" -> "Report"
    }
}
//============
// Destructor
//============
MSJExceptionHandler::~MSJExceptionHandler()
{

    BOOL bRet = TRUE;
    bRet = SymCleanup(GetCurrentProcess());

    SetUnhandledExceptionFilter(m_previousFilter);
}
//==============================================================
// Lets user change the name of the report file to be generated
//==============================================================
void MSJExceptionHandler::SetLogFileName(PTSTR pszLogFileName)
{
    _tcscpy(m_szLogFileName, pszLogFileName);
}
//===========================================================
// Entry point where control comes on an unhandled exception
//===========================================================
LONG WINAPI MSJExceptionHandler::MSJUnhandledExceptionFilter(
    PEXCEPTION_POINTERS pExceptionInfo)
{
    m_hReportFile = CreateFile(m_szLogFileName,
                               GENERIC_WRITE,
                               0,
                               0,
                               OPEN_ALWAYS,
                               FILE_FLAG_WRITE_THROUGH,
                               0);

    if(m_hReportFile)
    {
        SetFilePointer(m_hReportFile, 0, 0, FILE_END);

        GenerateExceptionReport(pExceptionInfo);

        CloseHandle(m_hReportFile);
        m_hReportFile = 0;
    }

    if(m_previousFilter)
        return m_previousFilter(pExceptionInfo);
    else
        return EXCEPTION_CONTINUE_SEARCH;
}
//===========================================================================
// Open the report file, and write the desired information to it.  Called by
// MSJUnhandledExceptionFilter
//===========================================================================
void MSJExceptionHandler::GenerateExceptionReport(
    PEXCEPTION_POINTERS pExceptionInfo)
{
    // Start out with a banner
    _tprintf(_T("//=====================================================\n"));

    PEXCEPTION_RECORD pExceptionRecord = pExceptionInfo->ExceptionRecord;

    // First print information about the type of fault
    _tprintf(_T("Exception code: %08X %s\n"),
             pExceptionRecord->ExceptionCode,
             GetExceptionString(pExceptionRecord->ExceptionCode));

    // Now print information about where the fault occured
    TCHAR szFaultingModule[MAX_PATH];
    DWORD section, offset;
    GetLogicalAddress(pExceptionRecord->ExceptionAddress,
                      szFaultingModule,
                      sizeof(szFaultingModule),
                      section, offset);

    _tprintf(_T("Fault address:  %08X %02X:%08X %s\n"),
             pExceptionRecord->ExceptionAddress,
             section, offset, szFaultingModule);

    PCONTEXT pCtx = pExceptionInfo->ContextRecord;

    // Show the registers
#ifdef _M_IX86  // Intel Only!
    _tprintf(_T("\nRegisters:\n"));

    _tprintf(_T("EAX:%08X\nEBX:%08X\nECX:%08X\nEDX:%08X\nESI:%08X\nEDI:%08X\n"),
             pCtx->Eax, pCtx->Ebx, pCtx->Ecx, pCtx->Edx, pCtx->Esi, pCtx->Edi);

    _tprintf(_T("CS:EIP:%04X:%08X\n"), pCtx->SegCs, pCtx->Eip);
    _tprintf(_T("SS:ESP:%04X:%08X  EBP:%08X\n"),
             pCtx->SegSs, pCtx->Esp, pCtx->Ebp);
    _tprintf(_T("DS:%04X  ES:%04X  FS:%04X  GS:%04X\n"),
             pCtx->SegDs, pCtx->SegEs, pCtx->SegFs, pCtx->SegGs);
    _tprintf(_T("Flags:%08X\n"), pCtx->EFlags);

    // Walk the stack using x86 specific code
    IntelStackWalk(pCtx);

#endif

    _tprintf(_T("\n"));
}
//======================================================================
// Given an exception code, returns a pointer to a static string with a
// description of the exception
//======================================================================
LPTSTR MSJExceptionHandler::GetExceptionString(DWORD dwCode)
{
#define EXCEPTION( x ) case EXCEPTION_##x: return _T(#x);

    switch(dwCode)
    {
            EXCEPTION(ACCESS_VIOLATION)
            EXCEPTION(DATATYPE_MISALIGNMENT)
            EXCEPTION(BREAKPOINT)
            EXCEPTION(SINGLE_STEP)
            EXCEPTION(ARRAY_BOUNDS_EXCEEDED)
            EXCEPTION(FLT_DENORMAL_OPERAND)
            EXCEPTION(FLT_DIVIDE_BY_ZERO)
            EXCEPTION(FLT_INEXACT_RESULT)
            EXCEPTION(FLT_INVALID_OPERATION)
            EXCEPTION(FLT_OVERFLOW)
            EXCEPTION(FLT_STACK_CHECK)
            EXCEPTION(FLT_UNDERFLOW)
            EXCEPTION(INT_DIVIDE_BY_ZERO)
            EXCEPTION(INT_OVERFLOW)
            EXCEPTION(PRIV_INSTRUCTION)
            EXCEPTION(IN_PAGE_ERROR)
            EXCEPTION(ILLEGAL_INSTRUCTION)
            EXCEPTION(NONCONTINUABLE_EXCEPTION)
            EXCEPTION(STACK_OVERFLOW)
            EXCEPTION(INVALID_DISPOSITION)
            EXCEPTION(GUARD_PAGE)
            EXCEPTION(INVALID_HANDLE)
    }

    // If not one of the "known" exceptions, try to get the string
    // from NTDLL.DLL's message table.
    static TCHAR szBuffer[512] = { 0 };

    FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
                  GetModuleHandle(_T("NTDLL.DLL")),
                  dwCode, 0, szBuffer, sizeof(szBuffer), 0);

    return szBuffer;
}
//==============================================================================
// Given a linear address, locates the module, section, and offset containing
// that address.
//
// Note: the szModule paramater buffer is an output buffer of length specified
// by the len parameter (in characters!)
//==============================================================================
BOOL MSJExceptionHandler::GetLogicalAddress(
    PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset)
{
    MEMORY_BASIC_INFORMATION mbi;

    if(!VirtualQuery(addr, &mbi, sizeof(mbi)))
        return FALSE;

    DWORD hMod = (DWORD)mbi.AllocationBase;

    if(!GetModuleFileName((HMODULE)hMod, szModule, len))
        return FALSE;

    // Point to the DOS header in memory
    PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;

    // From the DOS header, find the NT (PE) header
    PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);

    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHdr);

    DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address

    // Iterate through the section table, looking for the one that encompasses
    // the linear address.
    for(unsigned i = 0;
            i < pNtHdr->FileHeader.NumberOfSections;
            i++, pSection++)
    {
        DWORD sectionStart = pSection->VirtualAddress;
        DWORD sectionEnd = sectionStart
                           + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

        // Is the address in this section???
        if((rva >= sectionStart) && (rva <= sectionEnd))
        {
            // Yes, address is in the section.  Calculate section and offset,
            // and store in the "section" & "offset" params, which were
            // passed by reference.
            section = i + 1;
            offset = rva - sectionStart;
            return TRUE;
        }
    }

    return FALSE;   // Should never get here!
}

void MSJExceptionHandler::ShowFrame(STACKFRAME64* pFrame)
{
    const int FRAME_MSG_SIZE = MAX_PATH * 2;
    const int MAX_SYM_SIZE = MAX_PATH * 4;

    HRESULT hr = S_OK;
    TCHAR szFrame[FRAME_MSG_SIZE];
    TCHAR szSym[MAX_SYM_SIZE];
    DWORD dwDisplacement = 0;
    DWORD64 dwOffsetFromSmybol = 0;

    // get module name
    IMAGEHLP_MODULE64 module;
    memset(&module, 0, sizeof(IMAGEHLP_MODULE64));
    module.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

    if(!SymGetModuleInfo64(GetCurrentProcess(), pFrame->AddrPC.Offset, &module))
        strcpy(module.ModuleName, "Unknown");

    // find symbols
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)szSym;
    ZeroMemory(pSymbol , sizeof(SYMBOL_INFO));
    pSymbol->MaxNameLen = MAX_SYM_SIZE - sizeof(SYMBOL_INFO) / sizeof(TCHAR);
    pSymbol->Address = pFrame->AddrPC.Offset;

    if(SymFromAddr(GetCurrentProcess(), pFrame->AddrPC.Offset, &dwOffsetFromSmybol, pSymbol))
    {
        LPCTSTR lpModuleName;
        LPCTSTR lpSymbolName;
#ifdef UNICODE
        USES_CONVERSION;
        lpModuleName = A2T(module.ModuleName);
        lpSymbolName = A2T(pSymbol->Name);
#else
        lpModuleName = module.ModuleName;
        lpSymbolName = pSymbol->Name;
#endif

        _stprintf(szFrame, _T("%s!%s"), lpModuleName, lpSymbolName);
        _tprintf(szFrame);
    }


    if(pFrame->FuncTableEntry)
    {
        PFPO_DATA pFpo = (PFPO_DATA)pFrame->FuncTableEntry;
        _stprintf(szFrame, _T("FPO: Para dwords: %d; Regs: %d; Frame Type: %d "),
                  pFpo->cdwParams, pFpo->cbRegs, pFpo->cbFrame);
        _tprintf(szFrame);
    }
}
//============================================================
// Walks the stack, and writes the results to the report file
//============================================================
void MSJExceptionHandler::IntelStackWalk(PCONTEXT pContext)
{
    _tprintf(_T("\nCall stack:\n"));

    _tprintf(_T("Address   Frame     Logical addr  Module\n"));


    //Õ»»ØËÝ
    STACKFRAME64 frame;
    int nCount = 0;
    DWORD dwTimeMS;

    dwTimeMS = GetTickCount();


    memset(&frame, 0x0, sizeof(frame));

    frame.AddrPC.Offset    = pContext->Eip;
    frame.AddrPC.Mode      = AddrModeFlat;
    frame.AddrFrame.Offset = pContext->Ebp;
    frame.AddrFrame.Mode   = AddrModeFlat;
    frame.AddrStack.Offset = pContext->Esp;
    frame.AddrStack.Mode   = AddrModeFlat;

    while(nCount < 20)
    {
        nCount++;

        if(!StackWalk64(IMAGE_FILE_MACHINE_I386,
                        GetCurrentProcess(), GetCurrentThread(),
                        &frame, pContext,
                        NULL,
                        SymFunctionTableAccess64,
                        SymGetModuleBase64, NULL))
        {
            // Error occured.
            break;
        }

        ShowFrame(&frame);

        if(frame.AddrFrame.Offset == 0 || frame.AddrReturn.Offset == 0)
        {
            // End of stack.
            break;
        }
    }

}
//============================================================================
// Helper function that writes to the report file, and allows the user to use
// printf style formating
//============================================================================
int __cdecl MSJExceptionHandler::_tprintf(const TCHAR* format, ...)
{
    TCHAR szBuff[1024];
    int retValue;
    DWORD cbWritten;
    va_list argptr;

    va_start(argptr, format);
    retValue = wvsprintf(szBuff, format, argptr);
    va_end(argptr);

    WriteFile(m_hReportFile, szBuff, retValue * sizeof(TCHAR), &cbWritten, 0);

    return retValue;
}