#include "stdafx.h"
#include "protocol.h"



//计算应答值
//算法就是/2 + 110;
DWORD calcNvalue(DWORD n)
{
	return (n/2 + 110);
}
