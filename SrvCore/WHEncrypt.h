#ifndef WH_ENCRYPT_HEAD_FILE
#define WH_ENCRYPT_HEAD_FILE



//////////////////////////////////////////////////////////////////////////////////

//宏定义
#define XOR_TIMES					8									//加密倍数
#define MAX_SOURCE_LEN				64									//最大长度
#define MAX_ENCRYPT_LEN				(MAX_SOURCE_LEN*XOR_TIMES)			//最大长度


//资料数据
#define LEN_MD5						33									//加密密码
#define LEN_USERNOTE				32									//备注长度
#define LEN_ACCOUNTS				32									//帐号长度
#define LEN_NICKNAME				32									//昵称长度
#define LEN_PASSWORD				33									//密码长度
#define LEN_GROUP_NAME				32									//社团名字
#define LEN_UNDER_WRITE				32									//个性签名
//////////////////////////////////////////////////////////////////////////////////

//加密组件
class CWHEncrypt
{
	//函数定义
public:
	//构造函数
	CWHEncrypt();
	//析构函数
	virtual ~CWHEncrypt();

	//加密函数
public:
	//生成密文
	static bool MD5Encrypt(LPCTSTR pszSourceData, TCHAR szMD5Result[LEN_MD5]);

	//加密函数
public:
	//生成密文
	static bool XorEncrypt(LPCTSTR pszSourceData, LPTSTR pszEncrypData, WORD wMaxCount);
	//解开密文
	static bool XorCrevasse(LPCTSTR pszEncrypData, LPTSTR pszSourceData, WORD wMaxCount);

	//加密函数
public:
	//生成密文
	static bool MapEncrypt(LPCTSTR pszSourceData, LPTSTR pszEncrypData, WORD wMaxCount);
	//解开密文
	static bool MapCrevasse(LPCTSTR pszEncrypData, LPTSTR pszSourceData, WORD wMaxCount);
};

//////////////////////////////////////////////////////////////////////////////////

#endif