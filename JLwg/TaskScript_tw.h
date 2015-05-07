#pragma once

#include "gamecallEx.h"



#define gcall (*GamecallEx::GetInstance())


class TaskScript
{
public:
    TaskScript(void){};
    ~TaskScript(void){};
    void BeginTask(){};
private:
};