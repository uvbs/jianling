//{游戏基址 00401200}
#define Offset_Game_Base 0x00FC0170

#define Pbsengine_Shipping 0x043E0000

//{动作信息基址}
#define Const_Movement_BBase 0x06506C50

//{窗口句柄基址 04C06553}
#define Const_Game_PWin 0x0650F7F0

//{动作信息 04E1BB20}
#define Const_Movement_Base 0x06315F18
#define Offset_Movement_1 0x000003BC
#define Offset_Movement_2 0x0
#define Offset_Movement_3 0x00000040
#define Offset_Movement_4 0x00000214

//{跳跃高度 049DC32C 默认410}
#define Offset_Movement_JumpHeight 0x000002D4

//{人物移动速度偏移 054BCC30 默认速度248 加速极限 434}
#define Offset_Movement_Speed 0x000002C0

//{加速跑标记位 054C3B64 Word 正常1804 加速跑 1A04}
#define Offset_Movement_Acceleration 0x0000023C

//{环境指针 00401209}
#define Offset_Game_Offset 0x00000034

//{取对象名字 00A29A96}
#define OFFSET_GETOBJECTNAME_1 0x00FC15D4
#define OFFSET_GETOBJECTNAME_2 0x00002868
#define OFFSET_GETOBJECTNAME_3 0x00000048

//{取名字Id 00A2C2DB}
#define OFFSET_GETNAMEIDBYID_1 0x00FC15D4
#define OFFSET_GETNAMEIDBYID_2 0x00001244
#define OFFSET_GETNAMEIDBYID_3 0x00000048
#define OFFSET_GETNAMEIDBYID_4 0x000006E8

//{快捷栏控件偏移1 0059EEFD}
#define Offset_ShorCutPanel_Offset1 0x0000002C
//{快捷栏控件偏移2 0059EEFD}
#define Offset_ShorCutPanel_Offset2 0x00000004
//{快捷栏控件偏移3 00A54E49}
#define Offset_ShorCutPanel_Offset3 0x00000008
//{快捷栏控件偏移4 00A6CF4C}
#define Offset_ShorCutPanel_Offset4 0x0000568C
//{快捷栏控件偏移5 00A8EE7D}
#define Offset_ShorCutPanel_Offset5 0x0000000C
//{快捷栏控件偏移6 00A95444}
#define Offset_ShorCutPanel_Offset6 0x0002FBA0

//{地图Id偏移 00A9473D}
#define Offset_Map_Offset 0x0000A3F8

//{人物指针 006D77BC}
#define Offset_Role_Offset 0x00000080
#define Offset_Role_Attr 0x14

//{基础最大生命值偏移 006F2A51}
#define Offset_Role_MaxLife1 0x00000204
//{附加最大生命值偏移 006F2A4B}
#define Offset_Role_MaxLife2 0x00000208

//{背包总格数 004D01EB}
#define Offset_Role_PackageCount 0x0000017C{Byte}
//{当前频道 00A45029}
#define Offset_Role_Channel 0x00000744

//{最后查询物品信息 00468B32}
#define Offset_Role_LastQueryItemOffset 0x000007FC
#define Offset_Role_LastQueryItemId 0x00000030{004682B8}
#define Offset_Role_LastQueryItemPrice 0x00000038{004682BB}

//{是否在等待室 00501C6E}
#define Offset_Role_IsInWaitingRoom1 0x000008D0
#define Offset_Role_IsInWaitingRoom2 0x000008D4

//{交易对方Sn 005027A1}
#define Offset_Role_TradeGuestSn 0x000007D8
//{交易对方TId 005027A1}
#define Offset_Role_TradeGuestTId 0x000007DC

//{背包指针 00795219}
#define Offset_Item_Offset 0x00000788

//{物品名字Id偏移 00A2C437}
#define Offset_Item_NameId 0x000006E8

//{交易视窗信息指针 008C3E1A}
#define Offset_Item_PTrade 0x000007CC
//{对方交易视窗物品偏移 008C5444}
#define Offset_Item_GuestTrade 0x000000B8
//{对方交易视窗金钱偏移}
#define Offset_Item_GuestTradeMoney 0x000000B0

//{对象名字Id偏移1 004E6DBB}
#define Offset_Object_NameId_1 0x00000708
//{对象名字Id偏移2 00A229A1}
#define Offset_Object_NameId_2 0x0000001C

//{尸体物品指针 00A50598}
#define Offset_Object_PBodyGoods 0x00000048
//{资源物品指针 00A50598}
#define Offset_Object_PSourceGoods 0x00000054

//{商店3级偏移 007178BD}
#define Offset_Store_Offset3 0x00017F58

//{交易状态指针 008C5C80}
#define Offset_UI_PTradeState 0x000006D0
//{自己是否已确认物品 008C5C86}
#define Offset_UI_bSelfConfirmItems 0x000000A0
//{自己是否已确定交易}
#define Offset_UI_bSelfConfirmTrade Offset_UI_bSelfConfirmItems+ 0x1{Byte 0未确认 1已确认}
//{对方是否已确认物品 00570871}
#define Offset_UI_bGuestConfirmItems 0x00000140
//{对方是否已确定交易}
#define Offset_UI_bGuestConfirmTrade Offset_UI_bGuestConfirmItems+ 0x1{Byte 0未确认 1已确认}

//{队伍偏移 004F91B8}
#define Offset_Party_Offset 0x0000079C

//{邮件偏移 0075B052}
#define Offset_Mail_Offset 0x000007F8

//{生产委托 008D3E91}
#define Offset_Production_Processing_Offset 0x000007D0
#define Offset_Production_Processing_Sturct 0x00000030
#define Offset_Production_Processing_POffset 0x00000008
#define Offset_Production_Processing_Head 0x00000004
#define Offset_Production_Processing_End 0x00000008

//{KeyTable基址 0078E584}
#define Offset_KeyTable_Base 0x00FC15D4
//{KeyTable偏移 0078E58A}
#define Offset_KeyTable_Offset 0x00001348

//{拍卖偏移 008FC06F}
#define Offset_Auction_Offset1 0x00000080
#define Offset_Auction_Offset2 0x000007FC
#define Offset_Auction_Offset3 0x0000000C
#define Offset_Auction_Offset4 0x0
#define Offset_Auction_Offset5 0x00000028
#define Offset_Auction_OrderHead 0x00000004{0046594A}
#define Offset_Auction_OrderEnd 0x00000008
#define Offset_Auction_OrderStruct 0x00000098
#define Offset_Auction_ItemHead 0x00000004{00465A16}
#define Offset_Auction_ItemEnd 0x00000008
#define Offset_Auction_ItemStruct 0x00000038
#define Offset_Auction_ItemOffset 0x00000080

//{队伍拍卖偏移 00000000}
#define Offset_PartyAuction_Offset 0x00000000
#define Offset_PartyAuction_Head 0x00000060
#define Offset_PartyAuction_End 0x00000064

//{跨服副本信息偏移 0097A021}
#define Offset_Dungeon_Offset1 0x00000C00
#define Offset_Dungeon_Offset2 0x00000014
#define Offset_Dungeon_CurrRoomIndex 0x00000020

//{/////////////////////////////////////////////}

//{申请内存}
#define FUNC_ALLOCGAMEMMORY 0x00AF6710

//{明文发包 0046D98B}
#define FUNC_SENDPACKET 0x0059E8A0

//{整理背包}
#define FUNC_PACKAGEARRANGE 0x004C6330

//{激活NPC 006D78F1}
#define FUNC_ACTIVENPC 0x00479350
#define OFFSET_ACTIVENPC 0x00000704

//{使用物品 006D7E81}
#define FUNC_USEITEM 0x004C0370

//{出售物品 0087359D}
#define FUNC_SELLITEMS 0x00873930

//{购买物品 00875103}
#define FUNC_BUYITEMS 0x00872CE0

//{使用技能}
#define FUNC_CASTSKILL 0x00473110
#define OFFSET_CASTSKILL OFFSET_ACTIVENPC;

//{使用宠物技能 0050ADB9}
#define FUNC_CASTFOLLOWERSKILL 0x00473CE0
#define OFFSET_CASTFOLLOWERSKILL OFFSET_ACTIVENPC;

//{走路}
#define FUNC_WALK 0x00642430

//{功能操作}
#define FUNC_OPERATION 0x006D7640

//{全部拾取BOSS 0046E1F4}
#define PHEAD_ACQUIREBOSSITEMS 0x0000034F
#define CONST_ACQUIREBOSSITEMS 0x00D5538C

//{营地修理}
#define FUNC_CAMPREPAIR 0x0046F130
#define OFFSET_CAMPREPAIR OFFSET_ACTIVENPC;

//{进入游戏 0089483A}
#define FUNC_ENTERGAME_1 0x0045E7F0
#define FUNC_ENTERGAME_2 0x00AAC4B0

//{取当前地图名Id 0080FBB3}
#define CONST_GETMAPNAMEID 0x00FC15D4
#define OFFSET_GETMAPNAMEID_1 0x00001584
#define OFFSET_GETMAPNAMEID_2 0x00000048

//{结束NPC对话 00772703}
#define FUNC_ENDTALK 0x00AA3450
#define OFFSET_ENDTALK_1 0x0000002C
#define OFFSET_ENDTALK_2 0x0000001C
#define OFFSET_ENDTALK_3 0x00037FF0

//{复活 0046EF6E}
#define PHEAD_REVIVE 0x0000007E
#define CONST_REVIVE 0x00D552B4

//{打开普通尸体 0046D665}
#define PHEAD_OPENNORMALPOUCH 0x00000341
#define CONST_OPENNORMALPOUCH 0x00C88820

//{销毁物品 004C171C}
#define PHEAD_DESTROYITEMS 0x0000035D
#define CONST_DESTROYITEMS 0x00D5541C

//{穿上装备 0046E75F}
#define PHEAD_EQUIPARMOR 0x0000036E
#define CONST_EQUIPARMOR 0x00D5541C

//{物品是否可用}
#define FUNC_ISITEMAVIABLE 0x004FFE20

//{分解物品 004A0060}
#define PHEAD_DECOMPOSEITEM 0x0000039A
#define CONST_DECOMPOSEITEM 0x00C93FB8

//{开启物品 004A0060}
#define PHEAD_OPENITEM 0x0000039A
#define CONST_OPENITEM 0x00C93FB8
#define CONST_OPENITEM_PROP 0x00D5564C

//{快捷栏按键}
#define FUNC_USESHORTCUT 0x00A95240

//{切换频道 00503168}
#define PHEAD_CHANNELMOVE 0x000000D6
#define CONST_CHANNELMOVE 0x00D552B4

//{取控件指针}
#define FUNC_GETPUI 0x00672390

//{取控件Id 00669479}
#define CONST_GETUIID 0x00FC0154
#define OFFSET_GETUIID 0x00000028

//{交还任务 0077977A}
#define FUNC_QUESTREWARD 0x0052FF50
#define OFFSET_QUESTREWARD 0x0000078C

//{操纵对象 0045DA60}
#define PHEAD_MANIPULATEOBJECT 0x00000327
#define CONST_MANIPULATEOBJECT 0x00C88808

//{操纵对象-龙脉 00479865}
#define PHEAD_MANIPULATEOBJECT_SPECIL 0x00000309
#define CONST_MANIPULATEOBJECT_SPECIL 0x00C887A8

//{传送地图 00565FD0}
#define PHEAD_TRANSFERMAP 0x0000030D
#define CONST_TRANSFERMAP 0x00C887F0
#define FUNC_TRANSFERMAP_INIT 0x00567F60

//{接受任务 0051FC40}
#define PHEAD_ACCEPTQUEST 0x000003B3
#define CONST_ACCEPTQUEST 0x00C9A290

//{创建角色 00AAC48B}
#define FUNC_CREATECHARACTER 0x005AFE50
#define OFFSET_CREATECHARACTER_1 0x00FC0170
#define OFFSET_CREATECHARACTER_2 0x00000014

//{签订灵兽 005310B7}
#define FUNC_COPYPETNAME 0x00AFA7A0
#define PHEAD_SIGNPET 0x000003B9
#define CONST_SIGNPET 0x00C9A2C0

//{抱起尸体 0046E380}
#define PHEAD_PICKUPBODY 0x00000325
#define CONST_PICKUPBODY 0x00C887F0

//{装备成长 004A00A0}
#define PHEAD_ARMORGROW 0x000003A1
#define CONST_ARMORGROW 0x00C93FD0

//{扩展背包 007F014D}
#define PHEAD_EXTENSIONPACKAGE 0x00000357
#define CONST_EXTENSIONPACKAGE 0x00D553D4
#define CONST_EXTENSIONPACKAGE_PROP 0x00D5564C

//{创建社区昵称}
#define FUNC_CREATECOMMUNITYNAME 0x00AAD910

//{加入工会 00523A85}
#define PHEAD_JOINGUILD 0x0000012D
#define CONST_JOINGUILD 0x00D552B4

//{离开工会 00523AF1}
#define PHEAD_LEAVEGUILD 0x00000130
#define CONST_LEAVEGUILD 0x00D552B4

//{货币购买 005D4AF0}
#define PHEAD_CURRENCYBUYITEMS 0x00000366
#define CONST_CURRENCYBUYITEMS 0x00D55404
#define CONST_CURRENCYBUYITEMS_CY 0x00D5564C

//{邮寄物品 0045DCC0}
#define PHEAD_DELIVERYITEMS 0x000003F1
#define CONST_DELIVERYITEMS 0x00C88880
#define OFFSET_DELIVERYITEMS 0x00000020
#define CONST_DELIVERYITEMS_ANNEX 0x00D5564C

//{更新邮件附件信息 004819A0}
#define PHEAD_UPDATEANNEX 0x0000011D
#define CONST_UPDATEANNEX 0x00D552B4

//{收取邮件1 004825FC}
#define PHEAD_GETMAILANNEX_1 0x000003EB
#define CONST_GETMAILANNEX_1 0x00D554F4

//{收取邮件 00482004}
#define PHEAD_GETMAILANNEX 0x000003EE
#define CONST_GETMAILANNEX 0x00D554F4
#define OFFSET_GETMAILANNEX_1 0x00000788
#define OFFSET_GETMAILANNEX_2 0x0000014C
#define OFFSET_GETMAILANNEX_3 0x00000150

//{收取邮件3 00481E0C}
#define PHEAD_GETMAILANNEX_3 0x000003E8
#define CONST_GETMAILANNEX_3 0x00D554F4

//{领取问卷奖励 00564AA0}
#define PHEAD_QUESTIONNAIREREWARD 0x00000141
#define CONST_QUESTIONNAIREREWARD 0x00D2B1EC

//{取下宝石 004C195B}
#define PHEAD_REMOVEGEM 0x0000037B
#define CONST_REMOVEGEM 0x00D5541C

//{镶嵌宝石 0049FF30}
#define PHEAD_INLAIDGEM 0x00000378
#define CONST_INLAIDGEM 0x00C88868
#define CONST_INLAIDGEM_GEM 0x00D5564C

//{突破成长 004A0150}
#define PHEAD_ARMORGROWBREAK 0x000003A4
#define CONST_ARMORGROWBREAK 0x00C93FE8
#define CONST_ARMORGROWBREAK_PROP 0x00D5564C

//{进化装备 0049FD50}
#define PHEAD_ARMOREVOLUTION 0x0000027D
#define CONST_ARMOREVOLUTION 0x00C93F88
#define CONST_ARMOREVOLUTION_COM 0x00D5564C

//{解印装备 0049FFE0}
#define PHEAD_UNLOCKARMOR 0x0000038B
#define CONST_UNLOCKARMOR 0x00C93FB8
#define CONST_UNLOCKARMOR_PROP 0x00D5564C{004C2B02}

//{卸下装备 0046E939}
#define PHEAD_UNEQUIPARMOR 0x00000373
#define CONST_UNEQUIPARMOR 0x00D5541C

//{刷新频道数量 00502E80}
#define PHEAD_GETCHANNELCOUNT 0x000000D3
#define CONST_GETCHANNELCOUNT 0x00D552B4

//{单件拾取 0045DB30}
#define PHEAD_SINGLEPICKUP 0x0000034A
#define CONST_SINGLEPICKUP 0x00C88850
#define CONST_SINGLEPICKUP_GOODS 0x00D5564C

//{关闭拾取 0046D735}
#define PHEAD_CLOSEPOUCH 0x00000347
#define CONST_CLOSEPOUCH 0x00C88838

//{拍卖上架 00466C8C}
#define PHEAD_AUCTIONSHELVES 0x000003FA
#define CONST_AUCTIONSHELVES 0x00C88898

//{查询物品拍卖行最低价 0054E337}
#define PHEAD_QUERYLOWESTPRICE 0x000002D6
#define CONST_QUERYLOWESTPRICE 0x00D552B4

//{更新武神塔 00000000}
#define PHEAD_UPDATETOWERPROGRESS 0x00000000
#define CONST_UPDATETOWERPROGRESS 0x00000000
#define CONST_UPDATETOWERPROGRESS_PROP 0x00000000

//{刷新拍卖行物品 004673E7}
#define PHEAD_QUERYAUCTIONITEM 0x0000040F
#define CONST_QUERYAUCTIONITEM 0x00C88898

//{购买拍卖行物品 00467328}
#define PHEAD_BUYAUCTIONITEM 0x0000040C
#define CONST_BUYAUCTIONITEM 0x00C88898

//{进入等待室 1比武, 2副本 00501BED}
#define PHEAD_ENTERWAITINGROOM 0x000001E5
#define CONST_ENTERWAITINGROOM 0x00D552B4
#define OFFSET_ENTERWAITINGROOM_1 0x000008C8
#define OFFSET_ENTERWAITINGROOM_2 0x000008CC

//{选择排队副本 PartyType：6人=4 4人=3 005997AC}
#define PHEAD_SELECTDUNGEON 0x000001F4
#define CONST_SELECTDUNGEON 0x00D55710
#define CONST_SELECTDUNGEON_PARAM 0x00D5564C

//{申请副本排队 005913ED}
#define PHEAD_QUEUEDUNGEON 0x00000209
#define CONST_QUEUEDUNGEON 0x00D552B4

//{离开副本广场 00594C85}
#define PHEAD_LEAVEDUNGEONHALL 0x0000022D
#define CONST_LEAVEDUNGEONHALL 0x00D552B4

//{离开队伍 004EDB61}
#define PHEAD_PARTYLEAVE 0x00000098
#define CONST_PARTYLEAVE 0x00D552B4

//{队伍拍卖 004F146D}
#define PHEAD_PARTYAUCTIONBUY 0x000000BC
#define CONST_PARTYAUCTIONBUY 0x00D552B4

//{放弃队伍拍卖 004F14FF}
#define PHEAD_PARTYAUCTIONABORT 0x000000BF
#define CONST_PARTYAUCTIONABORT 0x00D552B4

//{离开副本等待室 0057D78B}
#define PHEAD_LEAVEDUNGEONWAITINGROOM 0x000001EB
#define CONST_LEAVEDUNGEONWAITINGROOM 0x00D552B4

//{开关窗口 007EAC96}
#define OFFSET_SWITCHWINDOW 0x00000024

//{确认技能修炼 0080D64D}
#define OFFSET_CONFIRMSKILLTRAIN 0x0000005C

//{接受组队 004ED730}
#define PHEAD_PARTYACCEPT 0x00000091
#define CONST_PARTYACCEPT 0x00D552B4

//{设置队伍竞拍品质 004EDE3A}
#define PHEAD_PARTYSETAUCTIONQUALITY 0x000000A0
#define CONST_PARTYSETAUCTIONQUALITY 0x00D552B4

//{邀请组队 004ECF70}
#define PHEAD_PARTYINVITE 0x0000008D
#define CONST_PARTYINVITE 0x00C9A218

//{完成任务步骤}
#define FUNC_QUESTPROGRESSSTEP 0x005328D0
//{小退 0080A827}

#define OFFSET_BACKTOCHARACTER_1 0x00000050
#define OFFSET_BACKTOCHARACTER_2 0x0000005C
#define OFFSET_BACKTOCHARACTER_3 0x0000001C
#define OFFSET_BACKTOCHARACTER_4 0x0000001C
#define FUNC_BACKTOCHARACTER_EAX_1 0x0045E7F0
#define FUNC_BACKTOCHARACTER_EAX_2 0x004037D0
#define FUNC_BACKTOCHARACTER 0x00A6F730

//{删除角色}
#define FUNC_DELETECHARACTER 0x00893770
#define OFFSET_DELETECHARACTER 0x000001B0

//{应用设置}
#define FUNC_APPLYSETTINGS 0x008BD8E0
#define OFFSET_APPLYSETTINGS_1 0x00036DAC
#define OFFSET_APPLYSETTINGS_2 0x8{在函数 [OptionPanel指针+ OFFSET_APPLYSETTINGS_1] 下}
#define OFFSET_APPLYSETTINGS_3 0x00000020

//{请求交易 00502560}
#define PHEAD_TRADEREQUEST 0x000000E1
#define CONST_TRADEREQUEST 0x00D552B4

//{接受交易 00502720}
#define PHEAD_TRADEACCEPTREQUEST 0x000000E4
#define CONST_TRADEACCEPTREQUEST 0x00D552B4

//{确认交易物品 00570750}
#define PHEAD_TRADECONFIRMITEMS 0x000000F7
#define CONST_TRADECONFIRMITEMS 0x00D552B4

//{确定交易 005707F0}
#define PHEAD_TRADECONFIRMTRADE 0x000000FD
#define CONST_TRADECONFIRMTRADE 0x00D552B4

//{交易放钱 005703C0}
#define PHEAD_TRADEPUTMONEY 0x000000F4
#define CONST_TRADEPUTMONEY 0x00D552B4

//{交易放物 005705F6}
#define PHEAD_TRADEPUTITEMS 0x000000EE
#define CONST_TRADEPUTITEMS 0x00D552B4

//{提仓}
#define FUNC_WAREHOUSEABSTRACT 0x0074ADA0

//{存仓}
#define FUNC_WAREHOUSESTORAGE 0x007097F0

//{领取委托1}
#define PHEAD_RECEIVEPRODUCTION_1 PHEAD_GETMAILANNEX_1
#define CONST_RECEIVEPRODUCTION_1 CONST_GETMAILANNEX_1

//{领取委托2}
#define PHEAD_RECEIVEPRODUCTION PHEAD_GETMAILANNEX
#define CONST_RECEIVEPRODUCTION CONST_GETMAILANNEX
#define OFFSET_RECEIVEPRODUCTION_1 OFFSET_GETMAILANNEX_1
#define OFFSET_RECEIVEPRODUCTION_2 OFFSET_GETMAILANNEX_2
#define OFFSET_RECEIVEPRODUCTION_3 OFFSET_GETMAILANNEX_3

//{领取委托3 00524691}
#define PHEAD_RECEIVEPRODUCTION_3 0x00000120
#define CONST_RECEIVEPRODUCTION_3 0x00D552B4

//{领取委托4}
#define PHEAD_RECEIVEPRODUCTION_4 PHEAD_GETMAILANNEX_3
#define CONST_RECEIVEPRODUCTION_4 CONST_GETMAILANNEX_3

//{委托取消}
#define FUNC_PRODUCTIONCANCEL 0x005245E0

//{委托生产}
#define FUNC_PRODUCTIONAUTHORIZE 0x00523F40

//{进入指定编号副本房间 0057D978}
#define PHEAD_CROSSDUNGEONENTERROOM 0x00000203
#define CONST_CROSSDUNGEONENTERROOM 0x00C9A218

//{副本房间加锁 0057D6C4}
#define PHEAD_CROSSDUNGEONLOCK 0x000001FA
#define CONST_CROSSDUNGEONLOCK 0x00D552B4

//{登录游戏}
#define FUNC_LOGIN 0x008A4BF0
#define OFFSET_LOGIN 0x00000048

#define Offset_Item_PHead 0x4;
#define Offset_Item_PEnd 0x8;


//技能的遍历
#define Offset_Skill_Offset1     Offset_ShorCutPanel_Offset1
#define Offset_Skill_Offset2     Offset_ShorCutPanel_Offset2 + Offset_ShorCutPanel_Offset3
#define Offset_Skill_Offset3     Offset_ShorCutPanel_Offset4
#define Offset_Skill_Offset4     Offset_ShorCutPanel_Offset5
#define Offset_Skill_Offset5     Offset_ShorCutPanel_Offset6
#define Offset_Skill_Skill     0x20+ 4+ 4
#define Offset_Skill_ASkill     0x1C+ 4+ 4
#define Offset_Skill_PBSkill     0x28
#define Offset_Skill_PESkill     0x2C
#define Offset_Skill_PBASkill     0x30
#define Offset_Skill_PEASkill     0x34
#define Offset_Skill_Name     0x320
#define Offset_Skill_NameLen     0x334
#define Offset_Skill_Id     0x10
#define Offset_Skill_Type     0x14
#define Offset_Skill_CD     0xC0
#define Offset_Skill_AState     0x30


//任务
#define Offset_Quest_Offset Offset_Item_Offset+ 0X4
#define Offset_Quest_PInfo 0x8
#define Offset_Quest_Step 0x8
#define Offset_Quest_PStep 0xC8
#define Offset_Quest_StepId 0x8
#define Offset_Quest_QuestId 0x8
#define Offset_Quest_NameId 0x18
#define Offset_Quest_StepTagDone1 0x9
#define Offset_Quest_StepTagCount1 0xA
#define Offset_Quest_StepTagDone2 0xB
#define Offset_Quest_StepTagCount2 0xC
#define Offset_Quest_StepTagDone3 0xD
#define Offset_Quest_StepTagCount3 0xE
#define Offset_Quest_StepTagDone4 0xF
#define Offset_Quest_StepTagCount4 0x10