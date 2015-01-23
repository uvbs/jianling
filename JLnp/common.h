#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <NTSecAPI.h>
#include <time.h> 




typedef PVOID (__stdcall *_ImageRvaToVa)(
	PIMAGE_NT_HEADERS NtHeaders, 
	PVOID Base,
	ULONG Rva,
	PIMAGE_SECTION_HEADER *LastRvaSection);


extern WORD WINAPI Module_size(DWORD base);
extern VOID WINAPI c2w(wchar_t *pwstr,size_t len,const char *str);
extern BOOL WINAPI hide(HMODULE hModMyself);


#ifdef _WIN64
typedef unsigned __int64 ULONG_PTR;
#else
typedef unsigned long ULONG_PTR;
#endif

#define ULongToPtr( ul ) ((VOID *)(ULONG_PTR)((unsigned long)ul))

#define NT_SUCCESS(Status)			((NTSTATUS)(Status) >= 0)
#define STATUS_SUCCESS				((NTSTATUS)0x00000000L) // ntsubauth0xc0000001
#define STATUS_UNSUCCESSFUL			((NTSTATUS)0xc0000001L) // ntsubauth
#define STATUS_ACCESS_DENIED        ((NTSTATUS)0xC0000022L)
#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)

extern BYTE * LoaderDll(PCHAR pDllName);
extern BOOL GetExportFuncAddr(IN PCHAR lpFunctionName,	//函数名称
							  BYTE *lpFileBase,			//模块内存地址
							  DWORD * dwFunc);				//函数地
extern BYTE *pNtdll;


typedef LONG NTSTATUS;
typedef LONG KPRIORITY;
typedef LSA_UNICODE_STRING UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;



typedef struct _RTL_DRIVE_LETTER_CURDIR {
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;


typedef struct _RTL_USER_PROCESS_PARAMETERS {
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags;
	ULONG DebugFlags;
	PVOID ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StdInputHandle;
	HANDLE StdOutputHandle;
	HANDLE StdErrorHandle;
	UNICODE_STRING CurrentDirectoryPath;
	HANDLE CurrentDirectoryHandle;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PVOID Environment;
	ULONG StartingPositionLeft;
	ULONG StartingPositionTop;
	ULONG Width;
	ULONG Height;
	ULONG CharWidth;
	ULONG CharHeight;
	ULONG ConsoleTextAttributes;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopName;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;


typedef struct _NT_PROC_THREAD_ATTRIBUTE_ENTRY {
	ULONG Attribute;    // PROC_THREAD_ATTRIBUTE_XXX，参见MSDN中UpdateProcThreadAttribute的说明
	SIZE_T Size;        // Value的大小
	ULONG_PTR Value;    // 保存4字节数据（比如一个Handle）或数据指针
	ULONG Unknown;      // 总是0，可能是用来返回数据给调用者
} PROC_THREAD_ATTRIBUTE_ENTRY, *PPROC_THREAD_ATTRIBUTE_ENTRY;

typedef struct _NT_PROC_THREAD_ATTRIBUTE_LIST {
	ULONG Length;       // 结构总大小
	PROC_THREAD_ATTRIBUTE_ENTRY Entry[1];
} NT_PROC_THREAD_ATTRIBUTE_LIST, *PNT_PROC_THREAD_ATTRIBUTE_LIST;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		PVOID SectionPointer;
	};
	ULONG CheckSum;
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	PVOID EntryPointActivationContext;
	PVOID PatchInformation;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB
{
	UCHAR InheritedAddressSpace;                     // 00h
	UCHAR ReadImageFileExecOptions;                  // 01h
	UCHAR BeingDebugged;                             // 02h
	UCHAR Spare;                                     // 03h
	PVOID Mutant;                                    // 04h
	PVOID ImageBaseAddress;                          // 08h
	PPEB_LDR_DATA Ldr;                               // 0Ch
} PEB, *PPEB;

typedef struct _PROCESS_BASIC_INFORMATION
{
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	ULONG AffinityMask;
	KPRIORITY BasePriority;
	ULONG UniqueProcessId;
	ULONG InheritedFromUniqueProcessId;
}PROCESS_BASIC_INFORMATION;

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID Pointer;
	} DUMMYUNIONNAME;

	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;


typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

typedef NTSTATUS (WINAPI *_ZwCreateFile)(OUT PHANDLE             FileHandle,
										IN ACCESS_MASK          DesiredAccess,
										IN POBJECT_ATTRIBUTES   ObjectAttributes,
										OUT PIO_STATUS_BLOCK    IoStatusBlock,
										IN PLARGE_INTEGER       AllocationSize OPTIONAL,
										IN ULONG                FileAttributes,
										IN ULONG                ShareAccess,
										IN ULONG                CreateDisposition,
										IN ULONG                CreateOptions,
										IN PVOID                EaBuffer OPTIONAL,
										IN ULONG                EaLength );


typedef enum _PROCESSINFOCLASS {
	ProcessBasicInformation,
	ProcessQuotaLimits,
	ProcessIoCounters,
	ProcessVmCounters,
	ProcessTimes,
	ProcessBasePriority,
	ProcessRaisePriority,
	ProcessDebugPort,
	ProcessExceptionPort,
	ProcessAccessToken,
	ProcessLdtInformation,
	ProcessLdtSize,
	ProcessDefaultHardErrorMode,
	ProcessIoPortHandlers,          // Note: this is kernel mode only
	ProcessPooledUsageAndLimits,
	ProcessWorkingSetWatch,
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup,
	ProcessPriorityClass,
	ProcessWx86Information,
	ProcessHandleCount,
	ProcessAffinityMask,
	ProcessPriorityBoost,
	ProcessDeviceMap,
	ProcessSessionInformation,
	ProcessForegroundInformation,
	ProcessWow64Information,
	ProcessImageFileName,
	ProcessLUIDDeviceMapsEnabled,
	ProcessBreakOnTermination,
	ProcessDebugObjectHandle,
	ProcessDebugFlags,
	ProcessHandleTracing,
	ProcessIoPriority,
	ProcessExecuteFlags,
	ProcessTlsInformation,
	ProcessCookie,
	ProcessImageInformation,
	ProcessCycleTime,
	ProcessPagePriority,
	ProcessInstrumentationCallback,
	ProcessThreadStackAllocation,
	ProcessWorkingSetWatchEx,
	ProcessImageFileNameWin32,
	ProcessImageFileMapping,
	ProcessAffinityUpdateMode,
	ProcessMemoryAllocationMode,
	ProcessGroupInformation,
	ProcessTokenVirtualizationEnabled,
	ProcessConsoleHostProcess,
	ProcessWindowInformation,
	MaxProcessInfoClass             // MaxProcessInfoClass should always be the last enum
} PROCESSINFOCLASS;

typedef enum _THREADINFOCLASS {
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair_Reusable,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,   // Obsolete
	ThreadIsIoPending,
	ThreadHideFromDebugger,
	ThreadBreakOnTermination,
	ThreadSwitchLegacyState,
	ThreadIsTerminated,
	ThreadLastSystemCall,
	ThreadIoPriority,
	ThreadCycleTime,
	ThreadPagePriority,
	ThreadActualBasePriority,
	ThreadTebInformation,
	ThreadCSwitchMon,          // Obsolete
	ThreadCSwitchPmu,
	ThreadWow64Context,
	ThreadGroupInformation,
	ThreadUmsInformation,      // UMS
	ThreadCounterProfiling,
	ThreadIdealProcessorEx,
	MaxThreadInfoClass

} THREADINFOCLASS;
#ifndef _VMP_
#define _VMP_
#define VMBEGIN \
	_asm _emit 0xEB \
	_asm _emit 0x10 \
	_asm _emit 0x56 \
	_asm _emit 0x4D \
	_asm _emit 0x50 \
	_asm _emit 0x72 \
	_asm _emit 0x6F \
	_asm _emit 0x74 \
	_asm _emit 0x65 \
	_asm _emit 0x63 \
	_asm _emit 0x74 \
	_asm _emit 0x20 \
	_asm _emit 0x62 \
	_asm _emit 0x65 \
	_asm _emit 0x67 \
	_asm _emit 0x69 \
	_asm _emit 0x6E \
	_asm _emit 0x00

#define VMEND \
	_asm _emit 0xEB \
	_asm _emit 0x0E \
	_asm _emit 0x56 \
	_asm _emit 0x4D \
	_asm _emit 0x50 \
	_asm _emit 0x72 \
	_asm _emit 0x6F \
	_asm _emit 0x74 \
	_asm _emit 0x65 \
	_asm _emit 0x63 \
	_asm _emit 0x74 \
	_asm _emit 0x20 \
	_asm _emit 0x65 \
	_asm _emit 0x6E \
	_asm _emit 0x64 \
	_asm _emit 0x00
#endif