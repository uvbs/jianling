#include "stdafx.h"
#include "lde32.h"

#define C_NULL         _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_ERROR         0xFFFFFFFF
#define C_ERROR         _asm _emit 0xff _asm _emit 0xff _asm _emit 0xff _asm _emit 0xff
//#define C_PREFIX        0x00000001
#define C_PREFIX        _asm _emit 0x01 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_66            0x00000002
#define C_66             _asm _emit 0x02 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
#define C_PREFIX_C_66     _asm _emit 0x03 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_67            0x00000004
#define C_67             _asm _emit 0x04 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
#define C_PREFIX_C_67     _asm _emit 0x05 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_DATA66        0x00000008
#define C_DATA66         _asm _emit 0x08 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_DATA1         0x00000010
#define C_DATA1          _asm _emit 0x10 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_DATA2         0x00000020
#define C_DATA2          _asm _emit 0x20 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_DATA4         0x00000040
#define C_DATA4          _asm _emit 0x40 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_MEM67         0x00000080
#define C_MEM67          _asm _emit 0x80 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
//#define C_MEM1          0x00000100
#define C_MEM1          _asm _emit 0x00 _asm _emit 0x01 _asm _emit 0x00 _asm _emit 0x00
//#define C_MEM2          0x00000200
#define C_MEM2          _asm _emit 0x00 _asm _emit 0x02 _asm _emit 0x00 _asm _emit 0x00
//#define C_MEM4          0x00000400
#define C_MEM4          __asm _emit 0x00 _asm _emit 0x04 _asm _emit 0x00 _asm _emit 0x00
//#define C_MODRM         0x00000800
#define C_MODRM         _asm _emit 0x00 _asm _emit 0x08 _asm _emit 0x00 _asm _emit 0x00
//#define C_DATAW0        0x00001000
#define C_DATAW0        _asm _emit 0x00 _asm _emit 0x10 _asm _emit 0x00 _asm _emit 0x00
//#define C_FUCKINGTEST   0x00002000
#define C_FUCKINGTEST   _asm _emit 0x00 _asm _emit 0x20 _asm _emit 0x00 _asm _emit 0x00
//#define C_TABLE_0F      0x00004000
#define C_TABLE_0F      _asm _emit 0x00 _asm _emit 0x40 _asm _emit 0x00 _asm _emit 0x00

#define C_MODRM_C_DATA66  _asm _emit 0x08 _asm _emit 0x08 _asm _emit 0x00 _asm _emit 0x00
#define C_MODRM_C_DATA1  _asm _emit 0x10 _asm _emit 0x08 _asm _emit 0x00 _asm _emit 0x00
#define C_DATA66_C_MEM2  _asm _emit 0x08 _asm _emit 0x02 _asm _emit 0x00 _asm _emit 0x00
#define C_DATA2_C_DATA1  _asm _emit 0x30 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00
#define C_DATA1_C_DATA4  _asm _emit 0x50 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00


void __declspec ( naked ) dis()
{

    _asm{
        jmp over
        table_1:
        call callback1
        C_MODRM
        /* 01 */  C_MODRM
        /* 02 */  C_MODRM
        /* 03 */  C_MODRM
        /* 04 */  C_DATAW0
        /* 05 */  C_DATAW0
        /* 06 */  C_NULL
        /* 07 */  C_NULL
        /* 08 */  C_MODRM
        /* 09 */  C_MODRM
        /* 0A */  C_MODRM
        /* 0B */  C_MODRM
        /* 0C */  C_DATAW0
        /* 0D */  C_DATAW0
        /* 0E */  C_NULL
        /* 0F */  C_TABLE_0F
        /* 10 */  C_MODRM
        /* 11 */  C_MODRM
        /* 12 */  C_MODRM
        /* 13 */  C_MODRM
        /* 14 */  C_DATAW0
        /* 15 */  C_DATAW0
        /* 16 */  C_NULL
        /* 17 */  C_NULL
        /* 18 */  C_MODRM
        /* 19 */  C_MODRM
        /* 1A */  C_MODRM
        /* 1B */  C_MODRM
        /* 1C */  C_DATAW0
        /* 1D */  C_DATAW0
        /* 1E */  C_NULL
        /* 1F */  C_NULL
        /* 20 */  C_MODRM
        /* 21 */  C_MODRM
        /* 22 */  C_MODRM
        /* 23 */  C_MODRM
        /* 24 */  C_DATAW0
        /* 25 */  C_DATAW0
        /* 26 */  C_PREFIX
        /* 27 */  C_NULL
        /* 28 */  C_MODRM
        /* 29 */  C_MODRM
        /* 2A */  C_MODRM
        /* 2B */  C_MODRM
        /* 2C */  C_DATAW0
        /* 2D */  C_DATAW0
        /* 2E */  C_PREFIX
        /* 2F */  C_NULL
        /* 30 */  C_MODRM
        /* 31 */  C_MODRM
        /* 32 */  C_MODRM
        /* 33 */  C_MODRM
        /* 34 */  C_DATAW0
        /* 35 */  C_DATAW0
        /* 36 */  C_PREFIX
        /* 37 */  C_NULL
        /* 38 */  C_MODRM
        /* 39 */  C_MODRM
        /* 3A */  C_MODRM
        /* 3B */  C_MODRM
        /* 3C */  C_DATAW0
        /* 3D */  C_DATAW0
        /* 3E */  C_PREFIX
        /* 3F */  C_NULL
        /* 40 */  C_NULL
        /* 41 */  C_NULL
        /* 42 */  C_NULL
        /* 43 */  C_NULL
        /* 44 */  C_NULL
        /* 45 */  C_NULL
        /* 46 */  C_NULL
        /* 47 */  C_NULL
        /* 48 */  C_NULL
        /* 49 */  C_NULL
        /* 4A */  C_NULL
        /* 4B */  C_NULL
        /* 4C */  C_NULL
        /* 4D */  C_NULL
        /* 4E */  C_NULL
        /* 4F */  C_NULL
        /* 50 */  C_NULL
        /* 51 */  C_NULL
        /* 52 */  C_NULL
        /* 53 */  C_NULL
        /* 54 */  C_NULL
        /* 55 */  C_NULL
        /* 56 */  C_NULL
        /* 57 */  C_NULL
        /* 58 */  C_NULL
        /* 59 */  C_NULL
        /* 5A */  C_NULL
        /* 5B */  C_NULL
        /* 5C */  C_NULL
        /* 5D */  C_NULL
        /* 5E */  C_NULL
        /* 5F */  C_NULL
        /* 60 */  C_NULL
        /* 61 */  C_NULL
        /* 62 */  C_MODRM
        /* 63 */  C_MODRM
        /* 64 */  C_PREFIX
        /* 65 */  C_PREFIX
        /* 66 */  C_PREFIX_C_66
        /* 67 */  C_PREFIX_C_67
        /* 68 */  C_DATA66
        /* 69 */  C_MODRM_C_DATA66
        /* 6A */  C_DATA1
        /* 6B */  C_MODRM_C_DATA1
        /* 6C */  C_NULL
        /* 6D */  C_NULL
        /* 6E */  C_NULL
        /* 6F */  C_NULL
        /* 70 */  C_DATA1
        /* 71 */  C_DATA1
        /* 72 */  C_DATA1
        /* 73 */  C_DATA1
        /* 74 */  C_DATA1
        /* 75 */  C_DATA1
        /* 76 */  C_DATA1
        /* 77 */  C_DATA1
        /* 78 */  C_DATA1
        /* 79 */  C_DATA1
        /* 7A */  C_DATA1
        /* 7B */  C_DATA1
        /* 7C */  C_DATA1
        /* 7D */  C_DATA1
        /* 7E */  C_DATA1
        /* 7F */  C_DATA1
        /* 80 */  C_MODRM_C_DATA1
        /* 81 */  C_MODRM_C_DATA66
        /* 82 */  C_MODRM_C_DATA1
        /* 83 */  C_MODRM_C_DATA1
        /* 84 */  C_MODRM
        /* 85 */  C_MODRM
        /* 86 */  C_MODRM
        /* 87 */  C_MODRM
        /* 88 */  C_MODRM
        /* 89 */  C_MODRM
        /* 8A */  C_MODRM
        /* 8B */  C_MODRM
        /* 8C */  C_MODRM
        /* 8D */  C_MODRM
        /* 8E */  C_MODRM
        /* 8F */  C_MODRM
        /* 90 */  C_NULL
        /* 91 */  C_NULL
        /* 92 */  C_NULL
        /* 93 */  C_NULL
        /* 94 */  C_NULL
        /* 95 */  C_NULL
        /* 96 */  C_NULL
        /* 97 */  C_NULL
        /* 98 */  C_NULL
        /* 99 */  C_NULL
        /* 9A */  C_DATA66_C_MEM2
        /* 9B */  C_NULL
        /* 9C */  C_NULL
        /* 9D */  C_NULL
        /* 9E */  C_NULL
        /* 9F */  C_NULL
        /* A0 */  C_MEM67
        /* A1 */  C_MEM67
        /* A2 */  C_MEM67
        /* A3 */  C_MEM67
        /* A4 */  C_NULL
        /* A5 */  C_NULL
        /* A6 */  C_NULL
        /* A7 */  C_NULL
        /* A8 */  C_DATA1
        /* A9 */  C_DATA66
        /* AA */  C_NULL
        /* AB */  C_NULL
        /* AC */  C_NULL
        /* AD */  C_NULL
        /* AE */  C_NULL
        /* AF */  C_NULL
        /* B0 */  C_DATA1
        /* B1 */  C_DATA1
        /* B2 */  C_DATA1
        /* B3 */  C_DATA1
        /* B4 */  C_DATA1
        /* B5 */  C_DATA1
        /* B6 */  C_DATA1
        /* B7 */  C_DATA1
        /* B8 */  C_DATA66
        /* B9 */  C_DATA66
        /* BA */  C_DATA66
        /* BB */  C_DATA66
        /* BC */  C_DATA66
        /* BD */  C_DATA66
        /* BE */  C_DATA66
        /* BF */  C_DATA66
        /* C0 */  C_MODRM_C_DATA1
        /* C1 */  C_MODRM_C_DATA1
        /* C2 */  C_DATA2
        /* C3 */  C_NULL
        /* C4 */  C_MODRM
        /* C5 */  C_MODRM
        /* C6 */  C_MODRM_C_DATA66
        /* C7 */  C_MODRM_C_DATA66
        /* C8 */  C_DATA2_C_DATA1
        /* C9 */  C_NULL
        /* CA */  C_DATA2
        /* CB */  C_NULL
        /* CC */  C_NULL
        /* CD */  C_DATA1_C_DATA4
        /* CE */  C_NULL
        /* CF */  C_NULL
        /* D0 */  C_MODRM
        /* D1 */  C_MODRM
        /* D2 */  C_MODRM
        /* D3 */  C_MODRM
        /* D4 */  C_NULL
        /* D5 */  C_NULL
        /* D6 */  C_NULL
        /* D7 */  C_NULL
        /* D8 */  C_MODRM
        /* D9 */  C_MODRM
        /* DA */  C_MODRM
        /* DB */  C_MODRM
        /* DC */  C_MODRM
        /* DD */  C_MODRM
        /* DE */  C_MODRM
        /* DF */  C_MODRM
        /* E0 */  C_DATA1
        /* E1 */  C_DATA1
        /* E2 */  C_DATA1
        /* E3 */  C_DATA1
        /* E4 */  C_DATA1
        /* E5 */  C_DATA1
        /* E6 */  C_DATA1
        /* E7 */  C_DATA1
        /* E8 */  C_DATA66
        /* E9 */  C_DATA66
        /* EA */  C_DATA66_C_MEM2
        /* EB */  C_DATA1
        /* EC */  C_NULL
        /* ED */  C_NULL
        /* EE */  C_NULL
        /* EF */  C_NULL
        /* F0 */  C_PREFIX
        /* F1 */  C_NULL                       // 0xF1
        /* F2 */  C_PREFIX
        /* F3 */  C_PREFIX
        /* F4 */  C_NULL
        /* F5 */  C_NULL
        /* F6 */  C_FUCKINGTEST
        /* F7 */  C_FUCKINGTEST
        /* F8 */  C_NULL
        /* F9 */  C_NULL
        /* FA */  C_NULL
        /* FB */  C_NULL
        /* FC */  C_NULL
        /* FD */  C_NULL
        /* FE */  C_MODRM
        /* FF */  C_MODRM

        table_0F:
        call callback2
        /* 00 */   C_MODRM
        /* 01 */  C_MODRM
        /* 02 */  C_MODRM
        /* 03 */  C_MODRM
        /* 04 */  C_ERROR
        /* 05 */  C_ERROR
        /* 06 */  C_NULL
        /* 07 */  C_ERROR
        /* 08 */  C_NULL
        /* 09 */  C_NULL
        /* 0A */  C_NULL
        /* 0B */  C_NULL
        /* 0C */  C_ERROR
        /* 0D */  C_ERROR
        /* 0E */  C_ERROR
        /* 0F */  C_ERROR
        /* 10 */  C_ERROR
        /* 11 */  C_ERROR
        /* 12 */  C_ERROR
        /* 13 */  C_ERROR
        /* 14 */  C_ERROR
        /* 15 */  C_ERROR
        /* 16 */  C_ERROR
        /* 17 */  C_ERROR
        /* 18 */  C_ERROR
        /* 19 */  C_ERROR
        /* 1A */  C_ERROR
        /* 1B */  C_ERROR
        /* 1C */  C_ERROR
        /* 1D */  C_ERROR
        /* 1E */  C_ERROR
        /* 1F */  C_ERROR
        /* 20 */  C_ERROR
        /* 21 */  C_ERROR
        /* 22 */  C_ERROR
        /* 23 */  C_ERROR
        /* 24 */  C_ERROR
        /* 25 */  C_ERROR
        /* 26 */  C_ERROR
        /* 27 */  C_ERROR
        /* 28 */  C_ERROR
        /* 29 */  C_ERROR
        /* 2A */  C_ERROR
        /* 2B */  C_ERROR
        /* 2C */  C_ERROR
        /* 2D */  C_ERROR
        /* 2E */  C_ERROR
        /* 2F */  C_ERROR
        /* 30 */  C_ERROR
        /* 31 */  C_ERROR
        /* 32 */  C_ERROR
        /* 33 */  C_ERROR
        /* 34 */  C_ERROR
        /* 35 */  C_ERROR
        /* 36 */  C_ERROR
        /* 37 */  C_ERROR
        /* 38 */  C_ERROR
        /* 39 */  C_ERROR
        /* 3A */  C_ERROR
        /* 3B */  C_ERROR
        /* 3C */  C_ERROR
        /* 3D */  C_ERROR
        /* 3E */  C_ERROR
        /* 3F */  C_ERROR
        /* 40 */  C_ERROR
        /* 41 */  C_ERROR
        /* 42 */  C_ERROR
        /* 43 */  C_ERROR
        /* 44 */  C_ERROR
        /* 45 */  C_ERROR
        /* 46 */  C_ERROR
        /* 47 */  C_ERROR
        /* 48 */  C_ERROR
        /* 49 */  C_ERROR
        /* 4A */  C_ERROR
        /* 4B */  C_ERROR
        /* 4C */  C_ERROR
        /* 4D */  C_ERROR
        /* 4E */  C_ERROR
        /* 4F */  C_ERROR
        /* 50 */  C_ERROR
        /* 51 */  C_ERROR
        /* 52 */  C_ERROR
        /* 53 */  C_ERROR
        /* 54 */  C_ERROR
        /* 55 */  C_ERROR
        /* 56 */  C_ERROR
        /* 57 */  C_ERROR
        /* 58 */  C_ERROR
        /* 59 */  C_ERROR
        /* 5A */  C_ERROR
        /* 5B */  C_ERROR
        /* 5C */  C_ERROR
        /* 5D */  C_ERROR
        /* 5E */  C_ERROR
        /* 5F */  C_ERROR
        /* 60 */  C_ERROR
        /* 61 */  C_ERROR
        /* 62 */  C_ERROR
        /* 63 */  C_ERROR
        /* 64 */  C_ERROR
        /* 65 */  C_ERROR
        /* 66 */  C_ERROR
        /* 67 */  C_ERROR
        /* 68 */  C_ERROR
        /* 69 */  C_ERROR
        /* 6A */  C_ERROR
        /* 6B */  C_ERROR
        /* 6C */  C_ERROR
        /* 6D */  C_ERROR
        /* 6E */  C_ERROR
        /* 6F */  C_ERROR
        /* 70 */  C_ERROR
        /* 71 */  C_ERROR
        /* 72 */  C_ERROR
        /* 73 */  C_ERROR
        /* 74 */  C_ERROR
        /* 75 */  C_ERROR
        /* 76 */  C_ERROR
        /* 77 */  C_ERROR
        /* 78 */  C_ERROR
        /* 79 */  C_ERROR
        /* 7A */  C_ERROR
        /* 7B */  C_ERROR
        /* 7C */  C_ERROR
        /* 7D */  C_ERROR
        /* 7E */  C_ERROR
        /* 7F */  C_ERROR
        /* 80 */  C_DATA66
        /* 81 */  C_DATA66
        /* 82 */  C_DATA66
        /* 83 */  C_DATA66
        /* 84 */  C_DATA66
        /* 85 */  C_DATA66
        /* 86 */  C_DATA66
        /* 87 */  C_DATA66
        /* 88 */  C_DATA66
        /* 89 */  C_DATA66
        /* 8A */  C_DATA66
        /* 8B */  C_DATA66
        /* 8C */  C_DATA66
        /* 8D */  C_DATA66
        /* 8E */  C_DATA66
        /* 8F */  C_DATA66
        /* 90 */  C_MODRM
        /* 91 */  C_MODRM
        /* 92 */  C_MODRM
        /* 93 */  C_MODRM
        /* 94 */  C_MODRM
        /* 95 */  C_MODRM
        /* 96 */  C_MODRM
        /* 97 */  C_MODRM
        /* 98 */  C_MODRM
        /* 99 */  C_MODRM
        /* 9A */  C_MODRM
        /* 9B */  C_MODRM
        /* 9C */  C_MODRM
        /* 9D */  C_MODRM
        /* 9E */  C_MODRM
        /* 9F */  C_MODRM
        /* A0 */  C_NULL
        /* A1 */  C_NULL
        /* A2 */  C_NULL
        /* A3 */  C_MODRM
        /* A4 */  C_MODRM_C_DATA1
        /* A5 */  C_MODRM
        /* A6 */  C_ERROR
        /* A7 */  C_ERROR
        /* A8 */  C_NULL
        /* A9 */  C_NULL
        /* AA */  C_NULL
        /* AB */  C_MODRM
        /* AC */  C_MODRM_C_DATA1
        /* AD */  C_MODRM
        /* AE */  C_ERROR
        /* AF */  C_MODRM
        /* B0 */  C_MODRM
        /* B1 */  C_MODRM
        /* B2 */  C_MODRM
        /* B3 */  C_MODRM
        /* B4 */  C_MODRM
        /* B5 */  C_MODRM
        /* B6 */  C_MODRM
        /* B7 */  C_MODRM
        /* B8 */  C_ERROR
        /* B9 */  C_ERROR
        /* BA */  C_MODRM_C_DATA1
        /* BB */  C_MODRM
        /* BC */  C_MODRM
        /* BD */  C_MODRM
        /* BE */  C_MODRM
        /* BF */  C_MODRM
        /* C0 */  C_MODRM
        /* C1 */  C_MODRM
        /* C2 */  C_ERROR
        /* C3 */  C_ERROR
        /* C4 */  C_ERROR
        /* C5 */  C_ERROR
        /* C6 */  C_ERROR
        /* C7 */  C_ERROR
        /* C8 */  C_NULL
        /* C9 */  C_NULL
        /* CA */  C_NULL
        /* CB */  C_NULL
        /* CC */  C_NULL
        /* CD */  C_NULL
        /* CE */  C_NULL
        /* CF */  C_NULL
        /* D0 */  C_ERROR
        /* D1 */  C_ERROR
        /* D2 */  C_ERROR
        /* D3 */  C_ERROR
        /* D4 */  C_ERROR
        /* D5 */  C_ERROR
        /* D6 */  C_ERROR
        /* D7 */  C_ERROR
        /* D8 */  C_ERROR
        /* D9 */  C_ERROR
        /* DA */  C_ERROR
        /* DB */  C_ERROR
        /* DC */  C_ERROR
        /* DD */  C_ERROR
        /* DE */  C_ERROR
        /* DF */  C_ERROR
        /* E0 */  C_ERROR
        /* E1 */  C_ERROR
        /* E2 */  C_ERROR
        /* E3 */  C_ERROR
        /* E4 */  C_ERROR
        /* E5 */  C_ERROR
        /* E6 */  C_ERROR
        /* E7 */  C_ERROR
        /* E8 */  C_ERROR
        /* E9 */  C_ERROR
        /* EA */  C_ERROR
        /* EB */  C_ERROR
        /* EC */  C_ERROR
        /* ED */  C_ERROR
        /* EE */  C_ERROR
        /* EF */  C_ERROR
        /* F0 */  C_ERROR
        /* F1 */  C_ERROR
        /* F2 */  C_ERROR
        /* F3 */  C_ERROR
        /* F4 */  C_ERROR
        /* F5 */  C_ERROR
        /* F6 */  C_ERROR
        /* F7 */  C_ERROR
        /* F8 */  C_ERROR
        /* F9 */  C_ERROR
        /* FA */  C_ERROR
        /* FB */  C_ERROR
        /* FC */  C_ERROR
        /* FD */  C_ERROR
        /* FE */  C_ERROR
        /* FF */  C_ERROR

        over:

        PUSH ESI
        MOV ESI, DWORD PTR SS:[ESP+8]
        XOR EAX, EAX
        L003:
        MOV CL, BYTE PTR DS:[ESI]
        MOVZX EDX, CL
        push edi//save edi
        jmp table_1//relative address

        callback1:
        pop edi//get table_1 address
        //OR EAX,DWORD PTR DS:[EDX*4+table_1]
        OR EAX, DWORD PTR DS:[EDX*4+edi]
        pop edi
        INC ESI
        TEST AH, 0x20
        JE L015
        MOV AL, BYTE PTR DS:[ESI]
        AND AL, 0x38
        NEG AL
        SBB EAX, EAX
        AND EAX, 0xFFFFF000
        ADD EAX, 0x1800
        L015:
        TEST AH, 0x40
        JE L021
        MOV CL, BYTE PTR DS:[ESI]
        MOVZX EAX, CL
        push edi//save edi
        jmp table_0f//relative address
        callback2:
        pop edi
        //MOV EAX,DWORD PTR DS:[EAX*4+table_0F]
        MOV EAX, DWORD PTR DS:[EAX*4+edi]
        pop edi
        INC ESI
        L021:
        TEST AL, 1
        JE L025
        AND EAX, 0xFFFFFFFE
        JMP L003
        L025:
        TEST AH, 0x10
        JE L032
        TEST CL, 0x1
        JE L031
        OR EAX, 0x8
        JMP L032
        L031:
        OR EAX, 0x10
        L032:
        TEST AH, 0x8
        PUSH EBX
        PUSH EBP
        PUSH EDI
        MOV EDI, 0x200
        MOV EBP, 0x400
        MOV EBX, 0x100
        JE L077
        MOV CL, BYTE PTR DS:[ESI]
        MOV DL, CL
        AND DL, 0xC0
        INC ESI
        AND CL, 0x7
        CMP DL, 0xC0
        JE L077
        TEST AL, 0x4
        JE L061
        TEST DL, DL
        JNZ L054
        CMP CL, 0x6
        JNZ L077
        OR EAX, EDI
        L054:
        CMP DL, 0x40
        JNZ L057
        OR EAX, EBX
        L057:
        CMP DL, 0x80
        JNZ L077
        OR EAX, EDI
        JMP L077
        L061:
        CMP DL, 0x40
        JNZ L064
        OR EAX, EBX
        L064:
        CMP DL, 0x80
        JNZ L067
        OR EAX, EBP
        L067:
        CMP CL, 0x4
        JNZ L072
        MOV CL, BYTE PTR DS:[ESI]
        AND CL, 0x7
        INC ESI
        L072:
        CMP CL, 0x5
        JNZ L077
        TEST DL, DL
        JNZ L077
        OR EAX, EBP
        L077:
        TEST AL, AL
        JNS L084
        TEST AL, 0x4
        JE L083
        OR EAX, EDI
        JMP L084
        L083:
        OR EAX, EBP
        L084:
        TEST AL, 0x8
        JE L091
        TEST AL, 0x2
        JE L090
        OR EAX, 0x20
        JMP L091
        L090:
        OR EAX, 0x40
        L091:
        TEST EBX, EAX
        JE L094
        INC ESI
        L094:
        TEST EDI, EAX
        JE L098
        INC ESI
        INC ESI
        L098:
        POP EDI
        TEST EBP, EAX
        POP EBP
        POP EBX
        JE L104
        ADD ESI, 0x4
        L104:
        TEST AL, 0x10
        JE L107
        INC ESI
        L107:
        TEST AL, 0x20
        JE L111
        INC ESI
        INC ESI
        L111:
        TEST AL, 0x40
        JE L114
        ADD ESI, 0x4
        L114:
        SUB ESI, DWORD PTR SS:[ESP+0x8]
        MOV EAX, DWORD PTR SS:[ESP+0xC]
        MOV DWORD PTR DS:[EAX], ESI
        POP ESI
        RETN 0x8
    }
}

DWORD lde32(void* ADDR)
{
    DWORD len;
    __asm {
        pusha;
        lea eax, len;
        push eax;
        push ADDR;
        call dis;
        popa;
    }
    return len;
}