// CVPNFile.h: interface for the CCVPNFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CVPNFILE_H__48C63982_DEC4_4960_B822_BB8302AB9242__INCLUDED_)
#define AFX_CVPNFILE_H__48C63982_DEC4_4960_B822_BB8302AB9242__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CCVPNFile: public CStdioFile
{
public:
	CCVPNFile();
	virtual ~CCVPNFile();


	void DisConnectVPN();
	int ConnectVPN();
	void AlwaysConnect();		//Ò»Ö±Á¬

	BOOL Open(TCHAR szFilePath[]);

private:
	POSITION curLine;
	DWORD dwMaxLine;
	CStringList cStrList;
};

#endif // !defined(AFX_CVPNFILE_H__48C63982_DEC4_4960_B822_BB8302AB9242__INCLUDED_)
