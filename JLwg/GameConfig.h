// GameConfig.h: interface for the GameConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
#define AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

typedef std::vector<std::wstring> ItemVector;
typedef std::vector<std::wstring>::iterator ItemIterator;

//��Ϸ����
class GameConfig: public CSimpleIniW
{
protected:
    GameConfig();
    virtual ~GameConfig();

    DECLARE_SINGLETON(GameConfig)

public:
    bool isHave(ItemVector& vec, wchar_t* pszItem);

    //�����ļ�·��
public:
    TCHAR m_szLujingPath[MAX_PATH];
    TCHAR m_szConfigPath[MAX_PATH];
    TCHAR m_szLujingTest[MAX_PATH];


    //����
    ItemVector m_SellItem;

    //���
    ItemVector m_BankItem;

    //�ֽ�
    ItemVector m_DisenchantItem;

    //����
    ItemVector m_TradeItem;

    //ɾ��
    ItemVector m_DelItem;

    //ǿ����Ʒ
    ItemVector m_QHAccessories;

    //ǿ������
    ItemVector m_QHWeapons;

    //ս������
    ItemVector m_FirstKill;

    //ս����ɱ
    ItemVector m_DontKill;

    //ս����ɱ
    ItemVector m_AlwaysKill;

    //��ҩ�ٷֱ�
    int m_HealthPercent;

    //ǿ�����������ɫ
    TCHAR m_szQHColor[BUFSIZ / 4];




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



    SHAREINFO* m_pMyData;


    //�����ڴ�
private:
    JLShareMem m_SMem;

    //��ʼ��
public:
    BOOL Init();

    //��������
    void LoadConfig();

    //��������
    void SaveConfig();

    //�������
    void ClearConfig();
};

#endif // !defined(AFX_GAMECONFIG_H__F88A8AE2_C451_47B0_A88C_A933A4EAE5E1__INCLUDED_)
