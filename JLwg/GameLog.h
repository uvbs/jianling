// GameLog.h: interface for the GameLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMELOG_H__19788572_D147_4859_9C00_494F1D5A7832__INCLUDED_)
#define AFX_GAMELOG_H__19788572_D147_4859_9C00_494F1D5A7832__INCLUDED_


#include "..\COMMON\logger.h"



class GameLog : public Logger
{
public:
    GameLog();
    virtual ~GameLog();

    DECLARE_SINGLETON(GameLog)
};


#define LOGER   GameLog::GetInstance()->info

#endif // !defined(AFX_GAMELOG_H__19788572_D147_4859_9C00_494F1D5A7832__INCLUDED_)
