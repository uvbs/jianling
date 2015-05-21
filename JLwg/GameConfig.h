// GameConfig.h: interface for the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
#define AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_


typedef std::vector<std::wstring> ItemVector;
typedef std::vector<std::wstring>::iterator ItemIterator;



//��Ϸ����
class GameConfig
{
protected:
    GameConfig();
    virtual ~GameConfig();

    DECLARE_SINGLETON(GameConfig)

public:
    bool isHave(ItemVector& vec, wchar_t* pszItem);

    //�����ļ�·��
public:

    ItemVector m_SellItem;    //����
    ItemVector m_BankItem;    //���
    ItemVector m_DisenchantItem;    //�ֽ�
    ItemVector m_TradeItem;    //����
    ItemVector m_DelItem;    //ɾ��
    ItemVector m_QHAccessories;    //ǿ����Ʒ
    ItemVector m_QHWeapons;    //ǿ������

    //ս��
    ItemVector m_FirstKill;
    ItemVector m_DontKill;
    ItemVector m_AlwaysKill;


    //��ҩ�ٷֱ�
    int m_HealthPercent;

    //ǿ�����������ɫ
    std::basic_string<TCHAR> m_szQHColor;




    // �Զ��������
    BOOL m_bInvite_Auto;

    //�����������
    BOOL m_bInvite_ALL;

    //ֻ��ͬ��ͼ�������
    BOOL m_bInvite_INMAP;

    //����Χ
    BOOL m_bInvite_Range;

    // ������ӷ�Χ
    int m_nInvite_Range;



    // ֻ����ͬ��ͼ�����
    BOOL m_bAccept_INMAP;

    // �Զ��������
    BOOL m_bAccept_Auto;

    // �����������
    BOOL m_bAccept_ALL;

    // ���ܷ�Χ�����
    BOOL m_bAccept_Range;

    //���ܷ�Χ
    int m_nAccept_Range;



public:
    //��������
    BOOL LoadConfig();

    //��������
    void SaveConfig();

    //�������
    void ClearConfig();

};

#endif // !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
