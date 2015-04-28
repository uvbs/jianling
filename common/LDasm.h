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

class LDasm
{
public:
    static unsigned long __fastcall SizeOfCode(void* Code, unsigned char** pOpcode);
    static unsigned long __fastcall SizeOfProc(void* Proc);
    static char __fastcall IsRelativeCmd(unsigned char* pOpcode);

};


#endif