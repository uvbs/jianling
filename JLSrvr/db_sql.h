#if !defined(AFX_DB_SQL_H__43EE1F19_89D9_440D_91DB_4E5E60F7DF1C__INCLUDED_)
#define AFX_DB_SQL_H__43EE1F19_89D9_440D_91DB_4E5E60F7DF1C__INCLUDED_


//��ѯkey
TCHAR db_sql_querykey[] =
    _T("select uk_key as ����, ")
    _T("convert(int,(datediff(ss,CONVERT(CHAR(19), Sysdatetime(), 120),dateadd(hh,b.jk_time_type,b.jk_recharge_time))/60/60)) as ʣ��ʱ�� ")
    _T("from Rr_User_Key a,Rr_Key b,Rr_Bind_type c where a.uk_key = b.jk_key and c.bt_id = b.jk_key_type and uk_user =\'%s\' ")
    _T("and bt_type_explanation = '��������'  order by uk_key");



//���key
TCHAR db_sql_unbind[] = _T("{call UnBind(\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')}");

//��key
TCHAR db_sql_bindkey[] = _T("{call Bind_key(\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')}");

//���key
TCHAR db_sql_addkey[] =
    _T("insert into Rr_Key(jk_key, jk_build_time, jk_sell_time, jk_recharge_time, jk_state, jk_time_type, jk_key_type)")
    _T("values(\'%s\', CONVERT(CHAR(19), Sysdatetime(), 20), NULL, NULL, 0, % d, % d)");


//�ȶ��û����������SQL
TCHAR db_sql_checkuser[] = _T("{call CheckUser(\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')}");

//ע���˺�
TCHAR db_sql_register[] =
    _T("insert into Rr_User(u_user, u_psw, u_ip, u_ac, u_cpuip, u_mac, u_hd_id, ")
    _T("u_bios, u_motherboard, u_time, u_game_id, u_bind_type)values(\'%s\', \'%s\', ")
    _T("\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', CONVERT(CHAR(19), ")
    _T("Sysdatetime(), 20), 1, '')");

TCHAR db_sql_userexit[] =
    _T("insert into Rr_User_Sign ")
    _T("select top 1 s_user,s_ip,CONVERT(CHAR(19), Sysdatetime(), 120),0,s_Sign_type,s_ac,s_cpuip,s_mac,s_hd_id,s_bios,s_motherboard,s_game_id,s_record_time ")
    _T("from Rr_User_Sign ")
    _T("where s_user = \'%s\' order by s_record_time desc");


#endif
