/*
  ___________________________________________________
  Opcode Length Disassembler.
  Coded By Ms-Rem ( Ms-Rem@yandex.ru ) ICQ 286370715
  ---------------------------------------------------
  12.08.2005 - fixed many bugs...
  09.08.2005 - fixed bug with 0F BA opcode.
  07.08.2005 - added SSE, SSE2, SSE3 and 3Dnow instruction support.
  06.08.2005 - fixed bug with F6 and F7 opcodes.
  29.07.2005 - fixed bug with OP_WORD opcodes.
*/

#ifndef _LDASM_
#define _LDASM_

#ifdef __cplusplus
extern "C" {
#endif

unsigned long __fastcall SizeOfCode(void *Code, unsigned char **pOpcode);
unsigned long __fastcall SizeOfProc(void *Proc);
char __fastcall IsRelativeCmd(unsigned char *pOpcode);

#ifdef __cplusplus
}
#endif


#define OP_NONE           0x00
#define OP_MODRM          0x01
#define OP_DATA_I8        0x02
#define OP_DATA_I16       0x04
#define OP_DATA_I32       0x08
#define OP_DATA_PRE66_67  0x10
#define OP_WORD           0x20
#define OP_REL32          0x40

#define UCHAR unsigned char
#define ULONG unsigned long
#define PVOID void*
#define PUCHAR unsigned char*
#define BOOLEAN char
#define FALSE 0
#define TRUE  1
 


#endif