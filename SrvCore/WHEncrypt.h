#ifndef WH_ENCRYPT_HEAD_FILE
#define WH_ENCRYPT_HEAD_FILE



//////////////////////////////////////////////////////////////////////////////////

//�궨��
#define XOR_TIMES					8									//���ܱ���
#define MAX_SOURCE_LEN				64									//��󳤶�
#define MAX_ENCRYPT_LEN				(MAX_SOURCE_LEN*XOR_TIMES)			//��󳤶�


//��������
#define LEN_MD5						33									//��������
#define LEN_USERNOTE				32									//��ע����
#define LEN_ACCOUNTS				32									//�ʺų���
#define LEN_NICKNAME				32									//�ǳƳ���
#define LEN_PASSWORD				33									//���볤��
#define LEN_GROUP_NAME				32									//��������
#define LEN_UNDER_WRITE				32									//����ǩ��
//////////////////////////////////////////////////////////////////////////////////

//�������
class CWHEncrypt
{
	//��������
public:
	//���캯��
	CWHEncrypt();
	//��������
	virtual ~CWHEncrypt();

	//���ܺ���
public:
	//��������
	static bool MD5Encrypt(LPCTSTR pszSourceData, TCHAR szMD5Result[LEN_MD5]);

	//���ܺ���
public:
	//��������
	static bool XorEncrypt(LPCTSTR pszSourceData, LPTSTR pszEncrypData, WORD wMaxCount);
	//�⿪����
	static bool XorCrevasse(LPCTSTR pszEncrypData, LPTSTR pszSourceData, WORD wMaxCount);

	//���ܺ���
public:
	//��������
	static bool MapEncrypt(LPCTSTR pszSourceData, LPTSTR pszEncrypData, WORD wMaxCount);
	//�⿪����
	static bool MapCrevasse(LPCTSTR pszEncrypData, LPTSTR pszSourceData, WORD wMaxCount);
};

//////////////////////////////////////////////////////////////////////////////////

#endif