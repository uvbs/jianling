#if !defined(AFX_DB_SQL_H__43EE1F19_89D9_440D_91DB_4E5E60F7DF1C__INCLUDED_)
#define AFX_DB_SQL_H__43EE1F19_89D9_440D_91DB_4E5E60F7DF1C__INCLUDED_


//查询key
TCHAR db_sql_querykey[] =
    _T("select uk_key as 卡号, jk_recharge_time as 充值时间 ,bt_type_explanation as 充值卡类型 ,")
    _T(" datediff(ss,CONVERT(CHAR(19), Sysdatetime(), 120),dateadd(hh,b.jk_time_type,b.jk_recharge_time))/60/60 as 剩余时间 ")
    _T(" from Rr_User_Key a,Rr_Key b,Rr_Bind_type c where a.uk_key = b.jk_key and c.bt_id = b.jk_key_type and uk_user = ")
    _T("'%s' and bt_type_explanation = '韩服剑灵'  order by uk_key");

//解绑key
TCHAR db_sql_unbind[] = _T("{call UnBind('%s','%s','%s','%s','%s','%s','%s','%s','%s')}");

//绑定key
TCHAR db_sql_bindkey[] = _T("{call Bind_key('%s','%s','%s','%s','%s','%s','%s','%s','%s')}");

//添加key
TCHAR db_sql_addkey[] =
    _T("insert into Rr_Key(jk_key,jk_build_time,jk_sell_time,jk_recharge_time,jk_state,jk_time_type,jk_key_type)")
    _T("values('%s',CONVERT(CHAR(19), Sysdatetime(), 20),NULL,NULL,0,%d,%d)");


//比对用户名和密码的SQL
TCHAR db_sql_checkuser[] = _T("{call CheckUser('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')}");

//注册账号
TCHAR db_sql_register[] =
    _T("insert into Rr_User(u_user,u_psw,u_ip,u_ac,u_cpuip,u_mac,u_hd_id,")
    _T("u_bios,u_motherboard,u_time,u_game_id,u_bind_type)values('%s','%s',")
    _T("'%s','%s','%s','%s','%s','%s','%s',CONVERT(CHAR(19),")
    _T("Sysdatetime(), 20),1,'band_ip')");


#endif
